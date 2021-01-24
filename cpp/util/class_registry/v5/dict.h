#pragma once
#include <string>
#include <functional>
#include <unordered_map>

class Dict {
public:
    Dict() {}
    virtual ~Dict() {}
    virtual std::string name() { return "base"; }
};

class DictRegistry {
public:
    using Factory = std::function<Dict*()>;
    static DictRegistry* Get() {
        static DictRegistry instance;
        return &instance;
    }

    bool Registry(std::string name, Factory factory) {
        if (factory_.find(name) == factory_.end()) {
            factory_.emplace(name, factory);
        }
        return true;
    }
    
    Dict* Create(const std::string& name) {
        auto iter = factory_.find(name);
        if (iter == factory_.end()) return nullptr;
        Dict* result = (iter->second)();
        return result;
    }
private:
    std::unordered_map<std::string, Factory> factory_;
};

class DictRegistryHelper {
public:
    DictRegistryHelper(std::string name, DictRegistry::Factory factory) {
        DictRegistry::Get()->Registry(name, factory);
    }
};

#define REGISTER_DICT(name,type)  \
    REGISTER_DICT_UNIQ_HELPER(__COUNTER__, name, type)
#define REGISTER_DICT_UNIQ_HELPER(ctr, name, type) \
    REGISTER_DICT_UNIQ(ctr, name, type)
#define REGISTER_DICT_UNIQ(ctr, name, type) \
    static DictRegistryHelper __register_dict##ctr(#name, []()->Dict* { return new type();})
