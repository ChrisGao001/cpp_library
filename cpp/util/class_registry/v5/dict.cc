#include "dict.h"
#include <iostream>
using namespace std;
class GBDTDict : public Dict {
public:
    GBDTDict() {}
    virtual ~GBDTDict() {}
    virtual std::string name() { return "gbdt";}	
};

class TFDict : public Dict {
public:
    TFDict() {}
    virtual ~TFDict() {}
    virtual std::string name() { return "tf";}	
};

REGISTER_DICT(gbdt, GBDTDict);
REGISTER_DICT(tf, TFDict);
REGISTER_DICT(base, Dict);

std::string ShowName(std::string name) {
  Dict* a = DictRegistry::Get()->Create(name);
  if (a == nullptr) return "none";
  return a->name();
}
int main(int argc, char** argv) {
  std::cout << ShowName("tf") << std::endl;
  std::cout << ShowName("gbdt") << std::endl;
  std::cout << ShowName("base") << std::endl;
  std::cout << ShowName("torch") << std::endl;

  return 0;
}

