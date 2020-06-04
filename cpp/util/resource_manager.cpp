#include <string>
#include <iostream>
#include <memory>
#include <utility>
#include <mutex>

using namespace std;
#define logger(text) do { \
  cout << text << endl;  \
} while (0) 

class A {
 public:
   A(int k=-1):n_(k) {
     logger("construct ptr:" << this);
   }
   ~A() {
    cout << "destruct ptr " << this << endl;
  }
  int Get() { return n_;}
  void Set(int k) { n_ = k;}
 private:
  int n_;
};

template <typename T>
class ResourceManager {
 public:
    using SharedPtr = shared_ptr<T>;
    ResourceManager(T* p):obj_(p) {}
    SharedPtr Get() { 
      std::lock_guard<std::mutex> lock(mutex_);
      return obj_;
    }
    void Update(T* p) {
        std::lock_guard<std::mutex> lock(mutex_);
        obj_.reset(p);
    }
 private:
    SharedPtr obj_;
    std::mutex mutex_;
};

int main(int argc, char** argv) {
  A *m0 = new A(3);
  logger("value:" << m0->Get());
  ResourceManager<A> dict(m0);
  auto p0 = dict.Get();
  logger("use_count:" << p0.use_count() << ",value:" << p0->Get());
  auto m1 = new A(300); 
  dict.Update(m1);
  {
    auto p1 = dict.Get();
    logger("new use_count:" << p1.use_count() << ",value:" << p1->Get());
  }
  auto m2 = new A(400); 
  dict.Update(m2);
  logger("old use_count:" << p0.use_count() << ",value:" << p0->Get());
  
  logger("finished");
  
  return 0;
}
