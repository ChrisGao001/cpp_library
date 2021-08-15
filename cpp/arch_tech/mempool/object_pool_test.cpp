#include <vector>
#include <mutex>

template <typename T>
class ObjectPool {
 public:
  static ObjectPool<T>* Instance() {
      static ObjectPool<T> instance(500);
      return &instance;
  }
  ObjectPool(size_t capacity = 0) {
    for (size_t i = 0; i < capacity; ++i) {
      T* d = new T();
      objects_.push_back(d);
    }
  }
  virtual ~ObjectPool() {
    typename std::vector<T*>::iterator iter = objects_.begin();
    for (; iter != objects_.end(); ++iter) {
      if (*iter) delete *iter;
    }
  }
  /// Acquire one object
  virtual T* Acquire() {
    std::unique_lock<std::mutex> lck(mutex_);
    if (objects_.empty()) return  new T();
    T* object = objects_.back();
    objects_.pop_back();
    return object;
  }
  /// Release one object
  virtual void Release(T* object) {
    std::unique_lock<std::mutex> lck(mutex_);
    if (objects_.size() > max_capacity_) {
        delete object;
    } else {
        objects_.push_back(object);
    }
  }
  /// Release the objects vector
  virtual void Release(const std::vector<T*>& objects) {
    std::unique_lock<std::mutex> lck(mutex_);
    typename std::vector<T*>::const_iterator iter = objects.begin();
    for (; iter != objects.end(); ++iter) {
      objects_.push_back(*iter);
    }
  }
  /// Return size of current available objects
  size_t Size() {
    std::unique_lock<std::mutex> lck(mutex_);
    return objects_.size();
  }

 protected:
  std::vector<T*> objects_;
  std::mutex mutex_;
  size_t capacity_;
  const size_t max_capacity_ = 1024;
};

#if TEST
#include <iostream>
using namespace std;

int main(int argc, char**argv) {
	ObjectPool<int>* int_obj = ObjectPool<int>::Instance();
        vector<int*> ptrs;
        for (int i=0; i<13; ++i) {
		auto p = int_obj->Acquire();
                cout << "get " << p << endl;
                ptrs.push_back(p);
                // int_obj->Release(p);
	} 	
        for (auto& p : ptrs) {
	    int_obj->Release(p);
        }

	return 0;
}
#endif
