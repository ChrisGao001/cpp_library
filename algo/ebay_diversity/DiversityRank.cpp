#include "DiversityRank.h"

using std::vector;
using std::list;
using merger_rank_api::QueryRsItem;


DiversityRank::DiversityRank()
{}

DiversityRank::~DiversityRank()
{
    for (size_t i=0; i<_constrainters.size(); ++i) {
        if (_constrainters[i] != NULL) {
            delete _constrainters[i];
        }
    }
    _constrainters.clear();
}

int DiversityRank::AddConstrainter(const ConstrainterParam &param)
{
    Constrainter *item = NULL;
    if (param.ratio > 0 && param.ratio < 1) {
        if (param.type == CONSTRAINTER_TYPE_NEW) {
            item = new(std::nothrow) Constrainter(param);
        } else if (param.type == CONSTRAINTER_TYPE_BRAND || param.type == CONSTRAINTER_TYPE_SHOP) {
            item = new(std::nothrow) AnyConstrainter(param);
        }
        if (item != NULL) {
            _constrainters.push_back(item);
        }
    }

    if (param.max_adjacent_cnt >= 2 && param.max_adjacent_cnt <= 4 && param.adjacent_pental_score > 0) {
        item = new(std::nothrow) AdjacentConstrainter(param);
        if (item != NULL) {
            _constrainters.push_back(item);
        }
    }
    
    return 0;
}

void DiversityRank::Rank(std::vector<QueryRsItem> &items, int topN)
{
    _rank_items.clear();
    _solution.clear();
    
    for (size_t i=0; i<items.size(); ++i) {
        _rank_items.push_back(&(items[i]));
    }

    for (size_t i=0; i<_constrainters.size(); ++i) {
        _constrainters[i]->Init(&_rank_items);
    }

    vector<Constrainter*> candidates;
    std::list<QueryRsItem*>::iterator iter;
    QueryRsItem *item = NULL;

    int num = 0;
    float unhappy_score = 0.0;
    while (!_rank_items.empty() && num<topN) {
        ++num;
        candidates.clear();
        iter = _rank_items.begin();
        item = *iter;

        if (num == 1) {
            _solution.push_back(item);
            for (size_t i=0; i<_constrainters.size(); ++i) {
                _constrainters[i]->UpdateParam(iter);
            }
            _rank_items.erase(iter); 
            continue;
        }
        
        for (size_t i=0; i<_constrainters.size(); ++i) {
            unhappy_score = (_constrainters[i])->Unhappiness(iter); 
            if (unhappy_score > 0) {
                candidates.push_back(_constrainters[i]);
                logger("conditon %lu not happy, score=%0.3f", i, unhappy_score);
            }
        }

        if (candidates.empty()) {
            _solution.push_back(item);
            for (size_t i=0; i<_constrainters.size(); ++i) {
                _constrainters[i]->UpdateParam(iter);
            }
    
            logger("candidate push id=%lu", (*iter)->pid);
            _rank_items.erase(iter);
            continue;
        } 

        Constrainter *max_constrainter = candidates[0];
        for (size_t i=1; i<candidates.size(); ++i) {
            if (max_constrainter->GetUnhappinessScore() < candidates[i]->GetUnhappinessScore()) {
                max_constrainter = candidates[i];
            }
        }

        iter = max_constrainter->ProposeItem();
        item = *iter;
        _solution.push_back(item);
        for (size_t i=0; i<_constrainters.size(); ++i) {
            _constrainters[i]->UpdateParam(iter);
        }

        logger("propose id=%lu", (*iter)->pid);
        _rank_items.erase(iter);
        
    }
}

