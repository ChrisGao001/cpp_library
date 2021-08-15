# brpc object pool and resource pool
资源池和对象池
每个线程threadlocal对于特定类型统一分配资源。
object pool 内存分配原理:
使用场景：多线程固定大小对象
原理：
内存统一在ObjectPool管理，每个线程维护自己的LocalPool（thread local),每个LocalPool会维护属于
每个线程的free_list及cur_block
分配流程：
1.查看localpool freelist中是否满足
2.从ObjectPool获取freelist
3.查看localpool cur_block中是否满足
4.从ObjectPool申请new block，修改cur_block

资源池会对每块分配的内存赋予一个ID
资源ID：
255       | 65535      | 255
num_group | num_block  | num_item
通过资源ID可以快速定位内存

备注：
释放资源时如果对象类型内使用STL或其他动态分配内存成员需要显式调用析构函数否则会有内存泄漏风险。切记切记
