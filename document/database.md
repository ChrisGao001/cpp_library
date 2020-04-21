



### module database

### Function

维护正排，倒排，业务字典三类数据



### APIS

```mermaid
classDiagram

QueryTerm <-- Database
PostingList <-- Database
Status <-- Database
PositionList <-- PostingList
Database --> DBSession

class Database {
+Open()
+GetSession()
+Update()
+Statistics()
+GetNumericValue(docid doc, int32_t field_id, int8_t* value,const ReadOption& option)
+GetBytes()
+GetDict()
+Synchronize()
+RegisterPostingSource()
+GetFieldDescription()
+GetPartitions()
+GetPostingList(int32_t part, const QueryTerm& term) 
+GetProfileExtraInfo()
}

class QueryTerm {
    +uint64_t termid;
    + std::string field;        // 指定域召回使用，默认为""
    + DocType pl_type;           // 区分全量，优质增量，普通增量
    + ExtendInfo extend_info;
}
class PostingList {
// 倒排链
+ Next()
+SkipTo(docid did)
+Reset()
+GetPositionList()
+IsDefaultField()
+DocCount()
}

class Status {
+ int code_
+ Type type_
+ Msg()
+Ok()
}
```

### partition

```mermaid
classDiagram
Profile <-- Partition
Invert <-- Partition
DictManager <-- Partition
Partition <-- InvertPostingSource
PostingSource <|-- InvertPostingSource
InvertPostingList <-- InvertPostingSource
PostingList <|-- InvertPostingList
class Partition {
+GetProfile()
+GetAuxProfile()
+GetInvert()
+GetNumericValues()
+GetStringValue()
+DocIsDeleted()
+GetPostingList(QueryTerm&)
+GetDict()
+Statistics()
+DelDoc()
+AddDoc()
+SetDoc()
+Synchronize()
+Recover()

+std::string name_;
+int32_t id_;
+profile::Profile profile_;
+profile::Profile aux_profile_;
+db::invert::Invert invert_;
+dict::DictManager dict_mgr_;
+std::string full_data_version_;
+std::string sensi_full_data_version_;
+std::string full_timestamp_;
+std::string sensi_full_timestamp_;
+std::string full_remote_source_;
}

class InvertPostingSource {
+GetPostingList()
+AddPartition()
+GetPartition()
+GetAllPartition()
+map<int32_t, const Partition*> parts_
}
```

```mermaid
classDiagram
Database <|-- DatabaseLocal
Database <|-- DatabaseOnline
DatabaseLocal --> Partition
DatabaseLocal --> DictManager
DatabaseLocal --> Update
DatabaseLocal --> Scheduler
DatabaseLocal --> InvertPostingSource

class DatabaseLocal {
    bool cloned_ = false;
    FieldsMap* fields_desp_ = nullptr;
    FieldsMap* aux_fields_desp_ = nullptr;
    PostingSourceMap* other_posting_sources_;
    InvertPostingSource* ivt_posting_source_ = nullptr;
    PartitionNameIdMap* part_id_;
    std::vector<Partition*> all_parts_;
    int32_t parts_size_ = 0;
    std::string dict_full_version_;
    std::string key_field_;
    DictTypeMap *dict_type_ = nullptr;
    dict::DictManager *global_dict_mgr_ = nullptr;
    PartitonDictMap *par_dict_mgr_ = nullptr;
    db::Update* update_ = nullptr;
    Scheduler* update_scheduler_ = nullptr;
    std::map<std::string, int64_t> load_time_;
    std::string fulldata_update_time_;
}

```
###  Profile

正排表设计理念：

WareidManager维护（全量&增量）wareid->docid映射关系及删除docid位图

ProfieTable：维护正排数据表

表设计理念：

+ 字段类型包括普通定长字段，变长string及多值

+ 多文件存储每个文件记录条数不超过kDocNumPerSegment（1<<20)

+ 两种文件存储：

  main.idx.[0-9]:定长字段及变长字段header

  ext.idx.[0-9]]: 变长数据

  优点：main.idx中每条记录定长便于访问。将变长转换为定长
  
  ```c++
  // string header
  #pragma pack(1)
  struct ProfileStringHeader {
      uint8_t flag : 1;   // 0表示存的字符串原值; 1表示字符串偏移量
      uint16_t len : 15;  // 字符串长度
  };
  union ProfileStringOffset {
      int64_t int_value : 48;
      char str_value[6];  // 存储实际字符串(长度不超过6)
  };
  
  #pragma pack()
  struct ProfileString {
      ProfileStringHeader header;
      ProfileStringOffset offset;
  };
  // multivalue header
  #pragma pack(1)
  struct ProfileMultiInfo{
      uint8_t num;    // 多值个数, 如果num为0，代表空值
      int64_t pos : 56;  // 多值偏移
  };
  ```
  
  



```mermaid
classDiagram
ProfileConfig <-- ProfileTable
ProfileFile <-- ProfileTable
ProfileTable <-- ProfileIndexer
ProfileIndexer <-- Profile
WareidManager <-- Profile
WareidManagerImpl <-- WareidManager
ProfileTable <-- IncTable
ProfileTable <-- SpuTable
ProfileTable <-- CommonTable
ProfileTable <-- MixTable

class ProfileConfig {
+Init()
+GetFieldId()
+GetField()
+GetFieldNum()
}

class ProfileIndexer {
    std::string data_path_;
    std::string config_file_;
    std::unique_ptr<ProfileConfig> config_;
    static const int kMaxTableNum = 32;
    std::array<std::unique_ptr<ProfileTable>, kMaxTableNum> tables_;
    bool has_full_ = true;
    bool use_inc_table_ = true;
    int main_doc_num_;
    int main_table_num_;
    std::vector<char> docid_tableid_;
    std::map<std::string, int> table_idx_;
    // snapshot
    using Snapshot = std::vector<SnapshotTable>;
    std::unordered_map<SnapshotKey, std::unique_ptr<Snapshot>> snapshots_;
    std::queue<SnapshotKey> snapshot_keys_;
    pthread_spinlock_t snapshot_lock_;
}

class Profile {
    std::string name_;
    bool valid_ = false;
    std::unique_ptr<ProfileIndexer> indexer_;
    WareidManager wareid_manager_;
    ProfileExtraInfo extra_info_;
    WareidMgrSnapshot *wareid_mgr_snapshot_;
}

class WareidManager {
    int32_t Create(int nodesize, int max_ware);
    int32_t Dump(const std::string &path);
    int32_t Load(const std::string& file_path);
    int32_t Add(int64_t wareid, int32_t docid, bool good_ware);
    int32_t Get(int64_t wareid) const;
    int32_t GetFromFull(int64_t wareid) const;
    int32_t GetFromInc(int64_t wareid, bool* is_good) const;
    int32_t DelDoc(int32_t docid);
    int32_t UndelDoc(int32_t docid);
    bool IsDelDoc(int32_t docid) const;
    int32_t DelWare(int64_t wareid);
    void SetIncSize(int32_t inc_size);
}

class WareidManagerImpl {
    bool has_inc_ = false;
    Hashmap* full_dict_ = nullptr;
    Hashmap* inc_dict_ = nullptr;
    char* delmap_ = nullptr;
    int32_t delmap_size_ = 0;
    int32_t inc_item_size_ = 0;
    pthread_spinlock_t* bitmap_locker_ = nullptr;
}
```



```mermaid
classDiagram
ProfileTable <-- IncTable
ProfileTable <-- SpuTable
ProfileTable <-- CommonTable
ProfileTable <-- MixTable

```

invert index structure

```mermaid
classDiagram

class IndexElement {
    uint64_t key;         // 1级索引id
    uint64_t index2_pos;  // 2级索引的文件偏移
    uint64_t index3_pos;  // 3级索引的文件偏移
    uint32_t doc_count;   // doc的数量
    bool is_compress;     // 2级索引是否整体做压缩
    bool is_unique;       // 3级索引是否整体做unique(去重)
    uint8_t index3_id;    // 3级索引所在文件编号
}

class Position {
+ int field
+ int pos
}
```

三级索引结构

一级索引：

TermInvertIndexDict （InlineHashMap)

存放termid -->IndexElement 二三级索引信息及doc个数

二级索引：

| int32      | ...  | int32       |
| ---------- | ---- | ----------- |
| docid list |      | offset list |

三级索引：(多个文件）

count| Position list 

```mermaid
classDiagram
InvertConfig <-- FullInvertIndex
InvertIndex <|-- FullInvertIndex
IndexTermPostingList <-- FullInvertIndex
InvertData <-- FullInvertIndex
PostingList <|-- IndexTermPostingList
RawPLIterator <--  IndexTermPostingList
PLIterator <|-- RawPLIterator

class RawPLIterator {
 + Next()
 + Docid SkipTo(Docid did)
 + void Reset()
 + bool Init(const PLIterator::Option &option)
 + PositionList GetPositionList()
 + int32_t DocCount()
}

class IndexTermPostingList {
+ docid Next()  
+ docid SkipTo(docid did)  
+void Reset()  
+std::string Name()    
+PositionList GetPositionList()    
+bool IsDefaultField()    
+int32_t DocCount()    
}

class InvertConfig {
+ IndexField* GetIndexField(const std::string &field)
+GetAllIndexFields()
+Init()
}

class FullInvertIndex {
+Init()
+GetPostingList(const QueryTerm &op)
+ IndexField* GetIndexField(const std::string &field)
- vector<InvertData> postings_
- InvertConfig invert_config_
}

class InvertData {
+std::unique_ptr<TermInvertIndexDict> index_;     // 一级索引字典，查找指定term的各级倒排索引偏移
+std::unique_ptr<char[]> document_;                 // 二级索引信息的首地址
+std::vector<std::unique_ptr<char[]>> position_;    // 三级索引信息的首地址
}
```



