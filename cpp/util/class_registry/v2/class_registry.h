#pragma once

#include <string>
#include <vector>
#include <map>
#include <functional>

namespace plugin {

template <typename T>
class Registry {
 public:
    using Factory = std::function<T*(void)>;

 public:
    void Register(const std::string& name, Factory factory) {
        factory_map_[name] = factory;
    }

    T* Create(const std::string& name) const {
        auto it = factory_map_.find(name);
        return it != factory_map_.end() ? it->second() : nullptr;
    }

    std::vector<std::string> ListFactory() const {
        std::vector<std::string> names;
        for (auto& item : factory_map_) {
            names.emplace_back(item.first);
        }
        return names;
    }

 private:
    std::map<std::string, Factory> factory_map_;
};

}  // namespace plugin


