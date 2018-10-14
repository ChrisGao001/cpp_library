//
// Created by 高玉敏 on 18/10/14.
//

#ifndef MTRANDOM_MTRANDOM_H
#define MTRANDOM_MTRANDOM_H

#include <cstdint>
#define STATE_LEN 624

class MTRandom {
public:
    MTRandom(uint64_t seed = 0);
    ~MTRandom();
    void SetSeed(uint64_t seed);
    uint64_t Random();
    uint32_t RandomUint32();
    uint64_t RandomUint64();
    double Uniform();

private:
    uint64_t key_[STATE_LEN];
    int pos_;
};


#endif //MTRANDOM_MTRANDOM_H
