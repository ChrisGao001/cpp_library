#include <iostream>
#include "class_registry.h"

using namespace std;
using namespace plugin;

#define logger(text) do { \
    std::cout << text << endl; \
} while(0)

class Dict {
  public:
    virtual ~Dict() {}
    Dict() {}
    virtual std::string Name() { return "Base";}
    virtual int Compute(int a, int b) { return (a+b);}
};

class TFDict : public Dict {
  public:
    virtual std::string Name() { return "TFDict";}
    virtual int Compute(int a, int b) { return (a-b);}
};

class TorchDict : public Dict {
  public:
    virtual std::string Name() { return "TorchDict";}
    virtual int Compute(int a, int b) { return (a*b);}
};

KernelRegistry<Dict>* GlobalDictRegistry();

class RegistryHelper {
 public:
    RegistryHelper(const std::string& name,
                   KernelRegistry<Dict>::KernelFactory factory) {
        GlobalDictRegistry()->Register(name, factory);
    }
};

#define REGISTER_PLUGIN_KERNEL(name, factory) \
    REGISTER_PLUGIN_KERNEL_UNIQ_HELPER(name, factory, __COUNTER__)

#define REGISTER_PLUGIN_KERNEL_UNIQ_HELPER(name, factory, ctr) \
    REGISTER_PLUGIN_KERNEL_UNIQ(name, factory, ctr)

#define REGISTER_PLUGIN_KERNEL_UNIQ(name, factory, ctr) \
    static RegistryHelper helper_obj##ctr(name, factory)

#define REGISTER_PLUGIN_KERNEL_SIMPLE(name, type) \
    REGISTER_PLUGIN_KERNEL(name, []() -> type* { return new type(); })
