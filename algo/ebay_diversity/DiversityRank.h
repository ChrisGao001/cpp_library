#ifndef DIVERSITY_RANK_H
#define DIVERSITY_RANK_H

/*
 * Refer: https://www.ebayinc.com/stories/blogs/tech/diversity-in-search/
*/

#include <stdio.h>
#include <vector>
#include <list>
#include "Constrainter.h"

class DiversityRank
{
public:
    DiversityRank();
    ~DiversityRank();
    int AddConstrainter(const ConstrainterParam &param);
    void Rank(std::vector<merger_rank_api::QueryRsItem> &items, int topN);
    std::vector<merger_rank_api::QueryRsItem*>* GetSolution() { return &_solution;}
    bool IsAvailable() { return (_constrainters.size() > 0);}
    
private:
    std::vector<Constrainter*> _constrainters;
    std::list<merger_rank_api::QueryRsItem*> _rank_items;
    std::vector<merger_rank_api::QueryRsItem*> _solution;
};
#endif
