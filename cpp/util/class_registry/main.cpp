#include <iostream>
#include "class_registry.h"

using namespace std;

#define logger(text) do { \
    std::cout << text << endl; \
} while(0)

class Dict {
  public:
    virtual ~Dict() {}    
    Dict() {}
    virtual std::string Name() { return "Base";}
};

class TFDict : public Dict {
  public:
    virtual std::string Name() { return "TFDict";}
};

class TorchDict : public Dict {
  public:
    virtual std::string Name() { return "TorchDict";}
};

TOFT_CLASS_REGISTRY_DEFINE(DictRegistry, Dict);

#define REGISTER_DICT(class_name) \
  TOFT_CLASS_REGISTRY_REGISTER_CLASS(DictRegistry, Dict, \
      #class_name, class_name)

#define CREATE_DICT(dict_name) \
  TOFT_CLASS_REGISTRY_CREATE_OBJECT(DictRegistry, dict_name)

#define DICT_CLASS_COUNT \
  TOFT_CLASS_REGISTRY_CLASS_COUNT(DictRegistry)

#define DICT_CLASS_NAME(i) \
  TOFT_CLASS_REGISTRY_CLASS_NAME(DictRegistry, i)

REGISTER_DICT(TFDict);
REGISTER_DICT(TorchDict);

int main(int argc, char** argv) {
    logger("hello world");
    std::string class_name = "TFDict";
    Dict *dict = CREATE_DICT(class_name);
    logger((dict->Name()));
    dict = CREATE_DICT("TorchDict");
    logger((dict->Name()));
    return 0;
}
