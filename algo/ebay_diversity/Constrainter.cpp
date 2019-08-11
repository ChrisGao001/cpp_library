#include "Constrainter.h"
#include "base/DocRankInfo.h"
#include "base/RankDef.h"
#include "libutil/include/global_def.h"

using std::list;
using std::map;
using std::vector;
using std::make_pair;
using merger_rank_api::QueryRsItem;
using merger_rank::DocRankInfo;
using merger_rank::RankDef;

Constrainter::Constrainter(const ConstrainterParam &param)
{
    _type = param.type;
    _ratio = param.ratio;
    _option = param.option;
    _alpha = param.alpha;
    _max_adjacent_cnt = param.max_adjacent_cnt;
    _adjacent_pental_score = param.adjacent_pental_score;
    _is_GBDTScore_valid = param.is_GBDTScore_valid;
    _n = 0;
    _k = 0;
    _unhappiness_score = -1;
    _items = NULL;
}


void Constrainter::Init(std::list<QueryRsItem*> *items) 
{
    _items = items;
    _iter = _items->begin();
    _n = 0;
    _k = 0;
}


int Constrainter::GetLabel(QueryRsItem *item) 
{
    int ret = 0;
    if (_type == CONSTRAINTER_TYPE_NEW) {
        if (mycast((*item))->productext & PRODUCT_EXT_IS_FZXP) {
            ret = 1;
        }
    } else if (_type == CONSTRAINTER_TYPE_BRAND) {
        ret = mycast((*item))->brand_id;
    } else if (_type == CONSTRAINTER_TYPE_SHOP) {
        ret = mycast((*item))->shop_id;
    } else if (_type == CONSTRAINTER_TYPE_CID3) {
        ret = item->cid3;
    }

    return ret;
}

bool Constrainter::Check(item_iterator item)
{
    int ret = false;
    int label = GetLabel(*item);
    // 密度最小情况取符合条件，密度最大情况取不符合条件
    if (_option == 0 && label == 1) {
        ret = true;
    } else if (_option == 1 && label == 0) {
        ret = true;
    }

    return ret;
}

bool Constrainter::IsRelevence(merger_rank_api::QueryRsItem *item) {
    bool rc = false;
    bool is_cheat_penalty = mycast((*item))->flags & RankDef::DRIF_IS_CHEAT_PENALTY;//是否作弊
    bool is_instock = (mycast((*item))->flags) & RankDef::DRIF_IS_STOCK_AVAIL; //是否有货
    bool is_deliveryable = item->flags & QR_IS_DELIVERYABLE;  //是否可配送
    bool is_high_rel = (item->flags) & RankDef::DRIF_IS_HC;
    int text_weight = mycast((*item))->text_weight;
    float predict_score = mycast((*item))->predict_score;
    bool is_relevance = _is_GBDTScore_valid ? (predict_score > 0.6) : (text_weight >= 10);

    if ( is_cheat_penalty || !is_instock || !is_deliveryable ||
        !is_high_rel || !is_relevance) {
        rc = true;
    }

    return rc;
}
void Constrainter::UpdateParam(item_iterator item)
{
    ++_n;
    int label = GetLabel(*item);
    logger("update label=%d",label);
    
    if (label == 1) {
        ++_k;
    }

    if (item == _iter) {
        ++_iter;
    }
}

float Constrainter::Unhappiness(item_iterator item)
{
    float deviance = 0;
    _unhappiness_score = -1;
    
    if (_iter == _items->end()) {
        return _unhappiness_score;
    }
    
    if (_option == 0) {
        deviance = (_n + 2) * _ratio - _k - 1;
    } else {
        int n = (_n < 10) ? 10 : _n;
        deviance = _k + 1 - (n + 2) * _ratio;
    }

    deviance = (deviance > 0) ? deviance : 0;

    if (deviance > 0) {
        while (_iter != _items->end()) {
            if (Check(_iter) && IsRelevence(*_iter)) {
                break;
            }
            ++_iter;
        }
        // 没有满足条件的item，不再参与条件限制
        if (_iter == _items->end()) {
            return _unhappiness_score;
        }

        // 计算损失
        float penality = (*item)->weight - (*_iter)->weight;
        _unhappiness_score = deviance - _alpha * penality;
    }
    
    return _unhappiness_score;
}

void AnyConstrainter::Init(std::list<QueryRsItem*> *items)
{
    Constrainter::Init(items);
    _id2stage.clear();    
}

void AnyConstrainter::UpdateParam(item_iterator item)
{
    ++_n;
    int id = GetLabel(*item);   
    if (_id2stage.find(id) == _id2stage.end()) {
        rank_stage_param param(0, item, -1);
        _id2stage.insert(make_pair(id, param));
    }
    
    map<int, rank_stage_param>::iterator iter = _id2stage.begin();
    while (iter != _id2stage.end()) {
        if (iter->first == id) {
            (iter->second).num += 1;
        }
        
        item_iterator &stage_iter = (iter->second).stage_iterator;
        if (stage_iter == item) {
            ++stage_iter;
        }
        ++iter;
    }


}

float AnyConstrainter::Unhappiness(item_iterator item)
{
    _unhappiness_score = -1;
    map<int, rank_stage_param>::iterator iter = _id2stage.begin();
    int cur_id = GetLabel(*item);

    // 当_n很小时对于最大密度的情况会出现任何一个元素放入都不满足条件
    int n = (_n < 10) ? 10 : _n;
    
    while (iter != _id2stage.end()) {
        int id = iter->first;
        rank_stage_param &stage_param = iter->second;
        float deviance = (stage_param.num + 1.0) - (n + 2) * _ratio;
        logger("cur_id=%d,id=%d,num=%d,n=%d,deviance=%f", cur_id, id,stage_param.num, _n, deviance);

        if (cur_id != id) {
            stage_param.stage_iterator = item;
        }
        
        item_iterator &stage_iter = stage_param.stage_iterator;
        if (deviance > 0) {            
            while (stage_iter != _items->end()) {
                if (id != GetLabel(*stage_iter) && IsRelevence(*stage_iter)) {
                    break;
                }
                ++stage_iter;
            }
            // 没有满足条件的item，不再参与条件限制
            if (stage_iter == _items->end()) {
                stage_param.score = -1;
            } else {
                // 计算损失
                float penality = (*item)->weight - (*stage_iter)->weight;
                stage_param.score = deviance - _alpha * penality;                    

                // 设置最大损失及propose item
                if (stage_param.score > 0 && _unhappiness_score < stage_param.score) {
                    _unhappiness_score = stage_param.score;
                    _iter = stage_param.stage_iterator;
                }
            }
        }

        ++iter;
    }

    // 如果输入item对应的属性不在map _id2stage中需要加入
    if (_id2stage.find(cur_id) == _id2stage.end()) {
        rank_stage_param param(0, item, -1);
        _id2stage.insert(make_pair(cur_id, param));
    }
    
    return _unhappiness_score;
}

AdjacentConstrainter::AdjacentConstrainter(const ConstrainterParam &param):Constrainter(param)
{
    is_enable = false;
    if (_max_adjacent_cnt >= 2 && _max_adjacent_cnt <= 4 && _adjacent_pental_score > 0) {
        is_enable = true;
        _adjacent_item_id.reserve(_max_adjacent_cnt);        
    }  
}

void AdjacentConstrainter::Init(std::list<merger_rank_api::QueryRsItem*> *items)
{
    Constrainter::Init(items);
    _adjacent_item_id.clear();
}

void AdjacentConstrainter::UpdateParam(item_iterator item)
{
    if (!is_enable) {
        return;
    }

    int label = GetLabel(*item);
    int last_label = -1; // -1为无效值

    if (_adjacent_item_id.empty()) {
        _adjacent_item_id.push_back(label);
    } else {
        last_label = _adjacent_item_id.back();
        if (last_label == label) {
             if (_adjacent_item_id.size() < (size_t)_max_adjacent_cnt) {
                 _adjacent_item_id.push_back(label); 
             }
        } else {
            _adjacent_item_id.clear();
            _adjacent_item_id.push_back(label);            
        }
    }
    
}

// 如果是强制规则建议设置_alpha为0
float AdjacentConstrainter::Unhappiness(item_iterator item)
{
    logger("AdjacentConstrainter, sku=%lu, id=%d,size=%ld", (*item)->pid, GetLabel(*item), _adjacent_item_id.size());
    // 限制条件不满足，happy just return
    if (!is_enable || _adjacent_item_id.size() < (size_t)_max_adjacent_cnt) {
        return -1;
    }

    int last_label = _adjacent_item_id.back();
    _iter = item;
    while (_iter != _items->end()) {
        int label = GetLabel(*_iter);
        if (label != last_label && IsRelevence(*_iter)) {
            break;
        }
        ++_iter;
    }

    // 找不到符合条件Item，该条件失效
    if (_iter == _items->end()) {
        return -1;
    }

    float penality = (*item)->weight - (*_iter)->weight;
    float _unhappiness_score = _adjacent_pental_score - _alpha * penality;

    return _unhappiness_score;     
}


