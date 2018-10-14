//
// Created by YuminGao on 18/10/11.
//

#include "BloomFilter.h"
#include <cmath>
#include <cstdlib>
#include <cstring>

using std::string;

uint32_t Hash(const char* data, size_t n, uint32_t seed) {
    // Similar to murmur hash
    const uint32_t m = 0xc6a4a793;
    const uint32_t r = 24;
    const char* limit = data + n;
    uint32_t h = seed ^ (n * m);

    // Pick up four bytes at a time
    while (data + 4 <= limit) {
        uint32_t w = 0;
        memcpy(&w, data, sizeof(uint32_t));
        data += 4;
        h += w;
        h *= m;
        h ^= (h >> 16);
    }

    // Pick up remaining bytes
    for (int i=0; i<(limit - data); ++i) {
        h += data[i] << (8 * i);
    }

    h *= m;
    h ^= (h >> r);

    return h;
}

BloomFilter::BloomFilter(int n, float false_positive_prob) {
    n_ = n;
    false_positive_prob_ = false_positive_prob;
    m_ = GetSize(n_, false_positive_prob_);
    k_ = GetHashCount(m_, n_);
    size_ = (m_ + 7) / 8;
    data_ = (char *)malloc(size_);
    memset(data_, 0, size_);
}

BloomFilter::~BloomFilter() {
    if (data_) {
        free(data_);
        data_ = NULL;
    }
}
/*
 *  Return the size of bit array(m) to used using
 *  following formula
 *  m = -(n * lg(p)) / (lg(2)^2)
 *  @param n : number of items expected to be stored in filter
 *  @param:p : False Positive probability in decimal
 */
int BloomFilter::GetSize(int n, float fp) {
    int m = -1 * (n * log(fp)) / (pow(log(2), 2));
    return m;
}

/*
 *  Return the hash function(k) to be used using
 *  following formula
 *      k = (m/n) * lg(2)
 *  @param m : size of bit array
 *  @param n : number of items expected to be stored in filter
 *
 */

int BloomFilter::GetHashCount(int m, int n) {
    int k = (1.0 * m / n) * log(2);
    return k;
}

void BloomFilter::Add(string &key) {
    uint32_t h = Hash((const char *)key.c_str(), key.size(), 0xbc9f1d34);
    const uint32_t delta = (h >> 17) | (h << 15);  // Rotate right 17 bits
    for (size_t j = 0; j < k_; j++) {
        const uint32_t bitpos = h % (m_);
        data_[bitpos/8] |= (1 << (bitpos % 8));
        h += delta;
    }
}

bool BloomFilter::Check(string &key) {
    uint32_t h = Hash((const char *)key.c_str(), key.size(), 0xbc9f1d34);
    const uint32_t delta = (h >> 17) | (h << 15);  // Rotate right 17 bits
    for (size_t j = 0; j < k_; j++) {
        const uint32_t bitpos = h % (m_);
        if ((data_[bitpos/8] & (1<< (bitpos%8))) == 0) {
            return false;
        }
        h += delta;
    }

    return true;
}
