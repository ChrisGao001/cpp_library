



## rpc_feature_server

### Introduction

+ bazel 编译
+ brpc通信
+ ini配置文件
+ glog日志
+ jsf服务管理


```mermaid
 classDiagram
ADServer --> RPCFeatureService
RPCFeatureService --> SKUService
RPCFeatureService --> JSFService
RPCFeatureService --> MonitorService
RPCFeatureService --> UserService


```

### SKU Info design

```sequence
FeatueServer->AdSkuRedisLruCache: Get
AdSkuRedisLruCache -> AdSkuRedisLruCache:GetSkuCacheInfoFromCache
AdSkuRedisLruCache -> SKUService:GetSKUInfo

```
AdSkuRedisLruCache数据结构设计:
LRU cache -> ShardedMRUCache-> butil::HashingMRUCache
ShardedMRUCache是为了减少锁的并发访问开销

### Dict Resource

```mermaid
 classDiagram
   
    DictKey *-- DictResource
    DictValue *-- DictResource
    DictResource ..|> IDictResource
    DictResourceMap ..|> DictResource
    IDictResource : +Find()
    IDictResource : +LoadFromFile()
    class DictResource {
      +ReloadFromConfig()
      +GetMd5AndModifyTime()
      +Find(string&)
      +Find(int64_t&)
      +LoadFromFile(std::string&)
      - std::unordered_map<IDictKeyPtr, IDictValuePtr
    , DictHash, DictCompare> DictMap
    -IDictValuePtr default_value_
    -int key_type_
    - Md5AndModifyTime md5_info_
    }
    class DictKey {
    	+ GetHash()
    	+Compare()
    	- int dtype_;
      - int64_t int64_val_;
      - std::string str_val_;
    }
```

DictResource::LoadFromFile

格式：

 int64 or string\n

 dict_key\n + pb size + PB string + dict_key\n + pb size + PB string 



DictResourceMap：

+ 管理多个dict

+ ReloadDictResource  重新reload

### feature extraction

  

  ```mermaid
classDiagram
FeatureCollectorForPb --> FeatureCollector
FeatureCollectorForText --> FeatureCollector
FeatureCollectorForMapPB --> FeatureCollector
FeatureCollectorMgrForText --> FeatureCollectorForText
FeatureCollectorMgrForPb --> FeatureCollectorForPb
FeatureCollectorMgrForMapPb --> FeatureCollectorForMapPB
FeatureExtractor --> FeatureCollectorMgr
FeatureGenerator <-- FeatureExtractor
RedisDataAccessor  <-- FeatureExtractor
FeatureCollectorMgr <|-- FeatureCollectorMgrForMapPb
FeatureCollectorMgr <|-- FeatureCollectorMgrForText
FeatureCollectorMgr <|-- FeatureCollectorMgrForPb

class FeatureExtractor {
+ ParallelAdExtractFeatures()
}
class FeatureGenerator {
+GenerateCommonFeatures()

}
  ```

```sequence
FeatureServerService ->FeatureServerService:RpcService
FeatureServerService ->FeatureServerService:ProcessRequest
FeatureServerService ->MonitorHandler:AddQueryStat
FeatureServerService ->FeatureServerReq:cfg().model_id()
FeatureServerService ->FeatureServerConfig:GetFeatureList(model_id)
FeatureServerService ->FeatureServerConfig:GetSkuInfoType(model_id)
FeatureServerService ->FeatureServerConfig:GetMaterialInfoType(model_id)
FeatureServerService ->FeatureServerConfig:GetUserInfoType(model_id,user_info_set)
FeatureServerService ->FeatureServerConfig:GetFeatureGeneratorParam
FeatureServerService ->SkuInfoRequestCache:Init
FeatureServerService ->FeatureServerService:ParsingUserData
FeatureServerService ->QPredictor:GetPrediction
FeatureServerService ->MonitorHandler:FillAdMonitorData




```

### redis cache

```mermaid
classDiagram
OnlineRedisAccessor --> SkuInfoRequestCache
SkuInfoRequestCache --> AdSkuRedisLruCache : expired time
AdSkuRedisLruCache --> ShardedMRUCache::shard
ShardedMRUCache --> ThreadSafetyMruCache::mutex
ThreadSafetyMruCache --> HashingMRUCache::butil
class AdSkuRedisLruCache {
+ GetSkuInfoBySkuService()
+ParallelReqeuestSkuService()
}

```





