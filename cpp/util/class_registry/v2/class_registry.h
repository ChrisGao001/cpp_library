#pragma once

#include <string>
#include <vector>
#include <map>
#include <functional>

namespace plugin {

template <typename KernelType>
class KernelRegistry {
 public:
    using KernelFactory = std::function<KernelType*(void)>;

 public:
    void Register(const std::string& name, KernelFactory factory) {
        factory_map_[name] = factory;
    }

    KernelType* Create(const std::string& name) const {
        auto it = factory_map_.find(name);
        return it != factory_map_.end() ? it->second() : nullptr;
    }

    std::vector<std::string> ListKernels() const {
        std::vector<std::string> names;
        for (auto& item : factory_map_) {
            names.emplace_back(item.first);
        }
        return names;
    }

 private:
    std::map<std::string, KernelFactory> factory_map_;
};

}  // namespace plugin


