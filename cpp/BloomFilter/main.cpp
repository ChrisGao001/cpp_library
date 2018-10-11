#include <iostream>
#include "BloomFilter.h"

using std::string;
using std::cout;
using std::endl;

int main() {
    BloomFilter filter(26, 0.01);
    cout << "m:" << filter.GetM() << " k:" << filter.GetK()
         << " fp:" << filter.GetFP() << " size:" << filter.GetSize() << endl;

    const char *word_present[] = {"abound","abounds","abundance","abundant","accessable",
            "bloom","blossom","bolster","bonny","bonus","bonuses", "bloom1","blossom2","bolster3","bonny4","bonus5","bonuses6",
            "coherent","cohesive","colorful","comely","comfort",
            "gems","generosity","generous","generously","genial"};
    for (size_t i=0; i<sizeof(word_present)/sizeof(const char *); ++i) {
        string key = word_present[i];
        filter.Add(key);
    }
    const char *word_absent[] = {"bluff","cheater","hate","war","humanity",
            "racism","hurt","nuke","gloomy","facebook",
            "geeksforgeeks","twitter"};
    int num_word = sizeof(word_absent)/sizeof(const char *);
    int num_fail = 0;
    for (size_t i=0; i<sizeof(word_absent)/sizeof(const char *); ++i) {
        string key = word_absent[i];
        bool rc = filter.Check(key);
        if (rc) ++num_fail;
        std::cout <<  "key:" << key << " rc:" << rc << std::endl;
    }
    std::cout << "fp:" << 1.0 * num_fail / num_word << std::endl;
    return 0;
}