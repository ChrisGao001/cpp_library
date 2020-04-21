本文档对RunOptions的参数定义及使用进行说明，tensorflow版本为1.12。

# 1.RunOptions参数

RunOptions提供配置参数，供SessionRun调用时使用，包括：

- TraceLevel：
- timeout_in_ms: op超时等待时间，单位为ms
- inter_op_thread_pool: 创建session时如果配置了session_inter_op_thread_pool参数，当前参数指定需要使用的线程池。**注释中有说明，如果配置为-1，使用调用者的线程，适用于比较简单的图执行，避免线程切换的开销，注意此处存在版本差异，tf1.10之前的版本，如果配置为-1会报InvalidArgument的错。**
- output_partition_graphs：布尔型变量，标记当前子图执行结果是否需要输出至MetaData。
- debug_options ： debug相关参数。
- report_tensor_allocations_upon_oom：当allocator发生OOM时，Error信息中包含tensor allocation的信息，使能后会导致Session::Run执行变慢。
- experimental: 相关参数不稳定，不同版本使用时需要注意兼容性问题。RunOptions中两个实验参数至tensorflow 2.1依然有效。**其中use_run_handler_pool推荐在CPU负载较大的场景比如inference中使用，达到session间线程池集中调度、降低延时的作用。**



```go
message RunOptions {
  enum TraceLevel {
    NO_TRACE = 0;
    SOFTWARE_TRACE = 1;
    HARDWARE_TRACE = 2;
    FULL_TRACE = 3;
  }
  TraceLevel trace_level = 1;

  int64 timeout_in_ms = 2;

  int32 inter_op_thread_pool = 3;

  bool output_partition_graphs = 5;

  DebugOptions debug_options = 6;

  bool report_tensor_allocations_upon_oom = 7;

  message Experimental {
    int64 collective_graph_key = 1;
    bool use_run_handler_pool = 2;
  };
  Experimental experimental = 8;

  reserved 4;
}
```

# 2. RunMetaData参数

RunMetaData与RunOptions中参数一样，定义在config.proto中。通常，配合RunOptions相关配置收集执行过程中的跟踪信息，包括延时、内存开销等。



```undefined
message RunMetadata {
  StepStats step_stats = 1;
  CostGraphDef cost_graph = 2;
  repeated GraphDef partition_graphs = 3;
}
```

# 3. 源码解析

session.h中定义了session.Run（）的API，其中支持RunOptions作为参数输入的API如下所示：



```cpp
 virtual Status Run(const RunOptions& run_options,
                     const std::vector<std::pair<string, Tensor> >& inputs,
                     const std::vector<string>& output_tensor_names,
                     const std::vector<string>& target_node_names,
                     std::vector<Tensor>* outputs, RunMetadata* run_metadata);
```

本节主要关注inter_op_thread_pool 及use_run_handler_pool 两个参数相关的源码：

## 3.1 inter_op_thread_pool参数

在前序介绍NewSession流程的文档中，了解到创建的thread_pool保存在了vector thread_pools_中。



```cpp
  std::vector<std::pair<thread::ThreadPool*, bool>> thread_pools_;
```

在调用Session::Run时，会先进行参数检查，inter_op_thread_pool应该小于thread_pools_.size()，否则会报错。



```cpp
if (run_options.inter_op_thread_pool() < -1 ||
      run_options.inter_op_thread_pool() >=
          static_cast<int32>(thread_pools_.size())) {
    run_state.executors_done.Notify();
    delete barrier;
    return errors::InvalidArgument("Invalid inter_op_thread_pool: ",
                                   run_options.inter_op_thread_pool());
  }
```

对于合法参数，tensorflow采用指定的线程池完成后续的计算。
 tensorflow1.12中开始允许inter_op_thread_pool=-1,此时采用主线程完成计算。



```cpp
thread::ThreadPool* pool =
      run_options.inter_op_thread_pool() >= 0
          ? thread_pools_[run_options.inter_op_thread_pool()].first
          : nullptr;
  if (pool == nullptr) {
    if (executors_and_keys->items.size() > 1) {
      pool = thread_pools_[0].first;
    } else {
      VLOG(1) << "Executing Session::Run() synchronously!";
    }
  }
```

## 3.2 use_run_handler_pool

当使用GlobalThreadPool时，该配置参数有效。
 **备注：GlobalThreadPool相关介绍可参见：https://www.jianshu.com/p/e9fd4f0d6bd1**



```cpp
std::unique_ptr<RunHandler> handler;
  if (ShouldUseRunHandlerPool() &&
      run_options.experimental().use_run_handler_pool()) {
    handler = GetOrCreateRunHandlerPool(options_)->Get();
  }
  auto* handler_ptr = handler.get();
```

主要影响Session::Run(）时使用的RunHandler,该类的定义位于：
 tensorflow/core/framework/run_handler.h。



```cpp
class RunHandler {
 public:
  void ScheduleInterOpClosure(std::function<void()> fn);
  ~RunHandler();
 private:
  class Impl;
  friend class RunHandlerPool::Impl;
  explicit RunHandler(Impl* impl);
  Impl* impl_;  // NOT OWNED.
};
```

当配置use_run_handler_pool时，通过GetOrCreateRunHandlerPool获取RunHandler。通过维护一个全局的RunHandlerPool，达到提升性能的目的。



```cpp
static RunHandlerPool* GetOrCreateRunHandlerPool(
    const SessionOptions& options) {
  static RunHandlerPool* pool =
      new RunHandlerPool(NumInterOpThreadsFromSessionOptions(options));
  return pool;
}
```

# 4.使用示例

## 4.1 timeline

可将运行时trace信息通过chrome:://tracing打开保存的json文件进行分析：



```jsx
import tensorflow as tf
from tensorflow.python.client import timeline

a = tf.random_normal([1, 100])
b = tf.random_normal([1, 100])
res = tf.add(a, b)

with tf.Session() as sess:
    options = tf.RunOptions(trace_level=tf.RunOptions.FULL_TRACE)
    run_metadata = tf.RunMetadata()
    sess.run(res, options=options, run_metadata=run_metadata)
    timeline = timeline.Timeline(run_metadata.step_stats)
    trace = timeline.generate_chrome_trace_format()
    with open('timeline.json', 'w') as f:
        f.write(chrome_trace)
```

如果需要合并多次session.run的trace，可使用如下TimeLiner类实现，每次调用session.run将trace存为json格式后，可调用TimeLiner的update_timeline函数进行更新，最后调用save函数将timeline写入json文件：



```python
import json

class TimeLiner:
   _timeline_dict = None   
   def update_timeline(self, chrome_trace):
       chrome_trace_dict = json.loads(chrome_trace)
       if self._timeline_dict is None:
          self._timeline_dict = chrome_trace_dict
       else:
          for event in chrome_trace_dict['traceEvents']:
              if 'ts' in event:
                  self._timeline_dict['traceEvents'].append(event)
   def save(self,f_name):
       print (f_name)
       with open(f_name,'w') as f:
          json.dump(self._timeline_dict,f)
```



作者：MoChiJiang
链接：https://www.jianshu.com/p/66a1b2068cfc
来源：简书
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。