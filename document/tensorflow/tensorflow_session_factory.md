# Tensorflow Session Factory源码解析



# 1.session factory

tensorflow支持两种session factory，direct session以及grpc session，采用哪种session，由传入的session option来决定。

------

## 1.1 API



```cpp
virtual Session* NewSession(const SessionOptions& options) = 0;

virtual bool AcceptsOptions(const SessionOptions& options) = 0;

virtual Status Reset(const SessionOptions& options, const std::vector<string>& containers) { return errors::Unimplemented("Reset()"); }

virtual ~SessionFactory() {} static void Register(const string& runtime_type, SessionFactory* factory); static Status GetFactory(const SessionOptions& options, SessionFactory** out_factory);
```

## 1.2 factory注册

------

tensorflow提供factory注册机制，不同模块可以注册自己的factory



```cpp
void SessionFactory::Register(const string& runtime_type,
                              SessionFactory* factory) {
  mutex_lock l(*get_session_factory_lock());
  if (!session_factories()->insert({runtime_type, factory}).second) {
    LOG(ERROR) << "Two session factories are being registered "
               << "under" << runtime_type;
  }
}
```

session_factories为unordered_map类型，注册factory相当于向其中插入一个表项，如果插入成功，返回值的成员变量second为true。



```cpp
typedef std::unordered_map<string, SessionFactory*> SessionFactories;
SessionFactories* session_factories() {
  static SessionFactories* factories = new SessionFactories;
  return factories;
}
```

direct session注册factory的代码如下所示：



```css
class DirectSessionRegistrar {
 public:
  DirectSessionRegistrar() {
    SessionFactory::Register("DIRECT_SESSION", new DirectSessionFactory());
  }
};
static DirectSessionRegistrar registrar;
```

## 1.3 session 创建

------

tensorflow通过factory调用NewSession函数创建session，NewSession函数在session.cc中进行调用，源码路径为：
tensorflow/core/common_runtime/session.cc

### 1.3.1 API

NewSession存在两种不同的接口，一种通过传入SessionOptions，创建Session之后返回指针，如下所示：



```dart
Session* NewSession(const SessionOptions& options)
{
   SessionFactory* factory;
   const Status s = SessionFactory::GetFactory(options, &factory);

   if (!s.ok()){
        LOG(ERROR) << s; return nullptr;
   }
   return factory->NewSession(options);
}
```

另一种将创建的session指针作为参数传入，返回值为Status，标志是否创建成功。



```php
Status NewSession(const SessionOptions& options, Session** out_session) {
  SessionFactory* factory;
  const Status s = SessionFactory::GetFactory(options, &factory);
  if (!s.ok()) {
    *out_session = nullptr;
    LOG(ERROR) << s;
    return s;
  }
  *out_session = factory->NewSession(options);
  if (!*out_session) {
    return errors::Internal("Failed to create session.");
  }
  return Status::OK();
}
```

备注：LoadSavedModel调用后一种方式完成session的初始化,后续会有章节详细介绍该流程



```cpp
Status LoadMetaGraphIntoSession(const MetaGraphDef& meta_graph_def,
                                const SessionOptions& session_options,
                                std::unique_ptr<Session>* session) {
  Session* session_p = nullptr;
  TF_RETURN_IF_ERROR(NewSession(session_options, &session_p));
  session->reset(session_p);
  return (*session)->Create(meta_graph_def.graph_def());
}
```

不同的factory完成NewSession的实现，Direct Session的实现参考《Tensorflow线程池分析》。

### 1.3.2 GetFactory

创建session前需要先调用GetFactory函数，根据传入的SessionOption决定使用哪种factory，代码路径为：
tensorflow/core/common_runtime/session_factory.cc
去掉注释及报错信息等，主体代码如下：



```cpp
Status SessionFactory::GetFactory(const SessionOptions& options,
                                  SessionFactory** out_factory) {
  mutex_lock l(*get_session_factory_lock());  // could use reader lock

  std::vector<std::pair<string, SessionFactory*>> candidate_factories;
  for (const auto& session_factory : *session_factories()) {
    if (session_factory.second->AcceptsOptions(options)) {
      candidate_factories.push_back(session_factory);
    } 
  }
  if (candidate_factories.size() == 1) {
    *out_factory = candidate_factories[0].second;
    return Status::OK();
  } else if (candidate_factories.size() > 1) {
    std::vector<string> factory_types;
    factory_types.reserve(candidate_factories.size());
    for (const auto& candidate_factory : candidate_factories) {
      factory_types.push_back(candidate_factory.first);
    } 
```

遍历session_factories中注册的factory，通过调用各个factory的AcceptOptions函数，进行判断选择候选factory并返回。
direct session的AceptOptions函数实现如下，若SessionOptions中没有指定target，默认使用tensorflow local runtime implementation：



```csharp
bool AcceptsOptions(const SessionOptions& options) override {
    return options.target.empty();
  }
```

### 1.3.3 SessionOptions

------

SessionOptions在session_options.h中定义，代码路径为：
tensorflow/core/public/session_options.h
去掉注释之后，主体结构如下所示：



```cpp
struct SessionOptions {
  Env* env;
  string target;
  ConfigProto config;
  std::shared_ptr<SessionResource> sessionResource;
  CustomKernelCreator customKernelCreator;
  SessionOptions();
};
```

### 1.3.4 ConfigProto

session中主要配置信息通过ConfigProto进行设置，ConfigProto在config.proto中定义，代码路径为：
tensorflow/core/protobuf/config.proto
具体代码如下：



```go
// Session configuration parameters.
// The system picks appropriate values for fields that are not set.
message ConfigProto {
  // Map from device type name (e.g., "CPU" or "GPU" ) to maximum
  // number of devices of that type to use.  If a particular device
  // type is not found in the map, the system picks an appropriate
  // number.
  map<string, int32> device_count = 1;

  // The execution of an individual op (for some op types) can be
  // parallelized on a pool of intra_op_parallelism_threads.
  // 0 means the system picks an appropriate number.
  int32 intra_op_parallelism_threads = 2;

  // Nodes that perform blocking operations are enqueued on a pool of
  // inter_op_parallelism_threads available in each process.
  //
  // 0 means the system picks an appropriate number.
  //
  // Note that the first Session created in the process sets the
  // number of threads for all future sessions unless use_per_session_threads is
  // true or session_inter_op_thread_pool is configured.
  int32 inter_op_parallelism_threads = 5;

  // If true, use a new set of threads for this session rather than the global
  // pool of threads. Only supported by direct sessions.
  //
  // If false, use the global threads created by the first session, or the
  // per-session thread pools configured by session_inter_op_thread_pool.
  //
  // This option is deprecated. The same effect can be achieved by setting
  // session_inter_op_thread_pool to have one element, whose num_threads equals
  // inter_op_parallelism_threads.
  bool use_per_session_threads = 9;

  // This option is experimental - it may be replaced with a different mechanism
  // in the future.
  //
  // Configures session thread pools. If this is configured, then RunOptions for
  // a Run call can select the thread pool to use.
  //
  // The intended use is for when some session invocations need to run in a
  // background pool limited to a small number of threads:
  // - For example, a session may be configured to have one large pool (for
  // regular compute) and one small pool (for periodic, low priority work);
  // using the small pool is currently the mechanism for limiting the inter-op
  // parallelism of the low priority work.  Note that it does not limit the
  // parallelism of work spawned by a single op kernel implementation.
  // - Using this setting is normally not needed in training, but may help some
  // serving use cases.
  // - It is also generally recommended to set the global_name field of this
  // proto, to avoid creating multiple large pools. It is typically better to
  // run the non-low-priority work, even across sessions, in a single large
  // pool.
  repeated ThreadPoolOptionProto session_inter_op_thread_pool = 12;

  // Assignment of Nodes to Devices is recomputed every placement_period
  // steps until the system warms up (at which point the recomputation
  // typically slows down automatically).
  int32 placement_period = 3;

  // When any filters are present sessions will ignore all devices which do not
  // match the filters. Each filter can be partially specified, e.g. "/job:ps"
  // "/job:worker/replica:3", etc.
  repeated string device_filters = 4;

  // Options that apply to all GPUs.
  GPUOptions gpu_options = 6;

  // Whether soft placement is allowed. If allow_soft_placement is true,
  // an op will be placed on CPU if
  //   1. there's no GPU implementation for the OP
  // or
  //   2. no GPU devices are known or registered
  // or
  //   3. need to co-locate with reftype input(s) which are from CPU.
  bool allow_soft_placement = 7;

  // Whether device placements should be logged.
  bool log_device_placement = 8;

  // Options that apply to all graphs.
  GraphOptions graph_options = 10;

  // Global timeout for all blocking operations in this session.  If non-zero,
  // and not overridden on a per-operation basis, this value will be used as the
  // deadline for all blocking operations.
  int64 operation_timeout_in_ms = 11;

  // Options that apply when this session uses the distributed runtime.
  RPCOptions rpc_options = 13;

  // Optional list of all workers to use in this session.
  ClusterDef cluster_def = 14;

  // If true, any resources such as Variables used in the session will not be
  // shared with other sessions.
  bool isolate_session_state = 15;

  // Next: 16
  // NOTE(yuanman.ym) Specify session handle in client side
  string session_handle = 200;

  // Whether tensor fuse is used in distributed running mode.
  bool tensor_fuse = 201;

  // Some expensive io operations in an op (like MergeV2Checkpoints) can be
  // paralledized on an pool of global_io_parallelism_threads
  // 0 means the system picks an appropriate number.
  int32 global_io_parallelism_threads = 202;

  bool run_graph_mode = 203;
  // Next: 204
};
```

config中主要对执行中的线程池进行了相关配置，供session创建时进行不同的线程池创建，主要包括：

- global thread pool：多个会话共享线程池，注意由于线程池共享，多个会话间执行时需要排队
- session thread pool：多个会话多个线程池，每个session可以有自己的线程池，根据use_per_session_threads配置使能。
- 单个会话设置多个线程池：跟据sessionoptions的配置，读取多个线程池的配置，生成多个线程池的vector