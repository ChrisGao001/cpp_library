# brpc object pool and resource pool
资源池和对象池
每个线程threadlocal对于特定类型统一分配资源。
备注：
释放资源时如果对象类型内使用STL或其他动态分配内存成员需要显式调用析构函数否则会有内存泄漏风险。切记切记
