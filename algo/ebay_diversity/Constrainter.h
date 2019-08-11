#ifndef CONSTRAINTER_H
#define CONSTRAINTER_H

#include<list>
#include<map>
#include<vector>

#include "rank_interface/merger/data_types.h"

#ifdef DIVERSITY_RANK
#define logger(fmt, ...) fprintf(stdout, fmt" \n", ##__VA_ARGS__)
#else
#define logger(fmt, ...) 
#endif

enum constrainer_type {
    CONSTRAINTER_TYPE_NEW = 0,
    CONSTRAINTER_TYPE_POP,
    CONSTRAINTER_TYPE_BRAND,
    CONSTRAINTER_TYPE_SHOP,
    CONSTRAINTER_TYPE_CID3
};


// 限制条件类参数
struct ConstrainterParam {
    int type;                // 条件类型
    float ratio;             // 密度
    int   option;            // 密度类型，0：最小满足， 1：最大不超过
    float alpha;             // weight损失权重因子
    int   max_adjacent_cnt;  // 相同类型sku连着出现的最大个数 
    float adjacent_pental_score; // 相同类型sku不满足最小位置差情况下的惩罚分
    bool is_GBDTScore_valid;
    ConstrainterParam(float _ratio=0, int _option=0, 
        float _alpha=0.03, int _diff =0, float _pental_score=10.0, bool _is_GBDTScore_valid=false):
        ratio(_ratio), option(_option), alpha(_alpha),
        max_adjacent_cnt(_diff),adjacent_pental_score(_pental_score), is_GBDTScore_valid(_is_GBDTScore_valid) {}
};

class Constrainter
{
public:
    typedef std::list<merger_rank_api::QueryRsItem*>::iterator item_iterator;
    typedef std::list<merger_rank_api::QueryRsItem*> rank_item;
    Constrainter(const ConstrainterParam &param);
    Constrainter() {};
    virtual ~Constrainter() {};
    int GetLabel(merger_rank_api::QueryRsItem *item);
    bool IsRelevence(merger_rank_api::QueryRsItem *item);
    virtual void Init(std::list<merger_rank_api::QueryRsItem*> *items);
    virtual bool Check(item_iterator item);
    virtual void UpdateParam(item_iterator item);
    virtual float Unhappiness(item_iterator item);
    item_iterator ProposeItem() {return _iter;}
    float GetUnhappinessScore() { return _unhappiness_score;}
    
protected:
    rank_item *_items;          // 候选集
    item_iterator _iter; // 条件选择器的迭代位置
    int   _type;  // 条件field
    float _ratio; // 限制条件密度占比
    int _option;  // 限制条件类型，0：最小，1：最大
    float _alpha; // 惩罚函数项权重因子
    int _n;       // 当前已选择的item个数
    int _k;       // 当前已选择item中满足条件的个数
    int _max_adjacent_cnt;
    float _adjacent_pental_score; 
    float _unhappiness_score; // 损失分
    bool _is_GBDTScore_valid;
};

// 属性种类比较多事前不能确定的限制，比如品牌，店铺
// 此类限制只支持某一类型不超过ratio即option=1
class AnyConstrainter: public Constrainter
{
public:
    struct rank_stage_param {
        int num;
        item_iterator stage_iterator;
        float score;
        rank_stage_param(int _num, item_iterator _stage_iter, float _score):
            num(_num),stage_iterator(_stage_iter),score(_score) {}
    };
public:
    AnyConstrainter(const ConstrainterParam &param):Constrainter(param) {};
    virtual void Init(std::list<merger_rank_api::QueryRsItem*> *items);
    virtual void UpdateParam(item_iterator item);
    virtual float Unhappiness(item_iterator item);
    
private:
    
    std::map<int, rank_stage_param> _id2stage;
};

class AdjacentConstrainter:public Constrainter 
{
public:
    AdjacentConstrainter(const ConstrainterParam &param);
    virtual void UpdateParam(item_iterator item);
    virtual float Unhappiness(item_iterator item);
    virtual void Init(std::list<merger_rank_api::QueryRsItem*> *items);
private:
    std::vector<int> _adjacent_item_id;
    bool is_enable;
};

#endif
