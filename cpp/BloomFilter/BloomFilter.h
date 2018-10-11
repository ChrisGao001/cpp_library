//
// Created by YuminGao on 18/10/11.
//

#ifndef BLOOMFILTER_BLOOMFILTER_H
#define BLOOMFILTER_BLOOMFILTER_H

#include <string>

class BloomFilter {
public:
    BloomFilter(int n, float false_positive_prob);
    ~BloomFilter();
    void Add(std::string &key);
    bool Check(std::string &key);
    int GetM() {return m_;}
    float GetFP() {return false_positive_prob_;}
    int GetK() {return k_;}
    int GetSize() { return size_;}
private:
    int GetSize(int n, float fp);
    int GetHashCount(int m, int n);

private:
    char *data_;
    int size_;
    int n_;
    int m_;
    int k_;
    float false_positive_prob_;
};


#endif //BLOOMFILTER_BLOOMFILTER_H
