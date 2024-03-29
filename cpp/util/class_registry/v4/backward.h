/* Copyright (C) 2016-2018 Alibaba Group Holding Limited

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/

#ifndef PS_MODEL_SERVER_BACKWARD_H_
#define PS_MODEL_SERVER_BACKWARD_H_

#include "ps-plus/common/status.h"
#include "ps-plus/common/tensor.h"
#include "ps-plus/common/plugin.h"
#include "ps-plus/common/string_utils.h"

#include <vector>
#include <string>
#include <unordered_map>

namespace ps {
namespace modelserver {

class BackwardCache {
 public:
  using Callback = std::function<void(Status)>;
  using BackwardRun = std::function<void(Tensor, Tensor, Callback)>;
  virtual Status Init(BackwardRun factory, const std::unordered_map<std::string, std::string>& map) = 0;
  virtual void Calc(Tensor ids, Tensor grads, Callback cb) = 0;
  virtual Status Flush() = 0;
  static Status Get(BackwardRun backward, const std::string& spec, std::unique_ptr<BackwardCache>* cache);
};

class BackwardRegistry {
 public:
  virtual BackwardCache* Create() = 0;
  virtual ~BackwardRegistry() {}
};

template<typename T>
class BackwardRegistryImpl : public BackwardRegistry {
 public:
  virtual BackwardCache* Create() {
    return new T;
  }
};

}
}

#define BACKWARD_REGISTER(TYPE, NAME) \
  PLUGIN_REGISTER(ps::modelserver::BackwardRegistry, NAME, ps::modelserver::BackwardRegistryImpl<TYPE>)

#endif

