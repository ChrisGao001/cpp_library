//
// Created by 高玉敏 on 18/10/14.
//

#include "MTRandom.h"

/* Magic Mersenne Twister constants */
#define N 624
#define M 397
#define MATRIX_A 0x9908b0dfUL
#define UPPER_MASK 0x80000000UL
#define LOWER_MASK 0x7fffffffUL


MTRandom::MTRandom(uint64_t seed) {
    SetSeed(seed);
}

MTRandom::~MTRandom() {}

void MTRandom::SetSeed(uint64_t seed) {
    seed &= 0xffffffffUL;

    /* Knuth's PRNG as used in the Mersenne Twister reference implementation */
    for (int pos = 0; pos < STATE_LEN; pos++) {
        key_[pos] = seed;
        seed = (1812433253UL * (seed ^ (seed >> 30)) + pos + 1) & 0xffffffffUL;
    }
    pos_ = STATE_LEN;
}

uint64_t MTRandom::Random() {
    uint64_t y;

    if (pos_ ==STATE_LEN) {
        int i;

        for (i = 0; i < N - M; i++) {
            y = (key_[i] & UPPER_MASK) | (key_[i+1] & LOWER_MASK);
            key_[i] = key_[i+M] ^ (y>>1) ^ (-(y & 1) & MATRIX_A);
        }
        for (; i < N - 1; i++) {
            y = (key_[i] & UPPER_MASK) | (key_[i+1] & LOWER_MASK);
            key_[i] = key_[i+(M-N)] ^ (y>>1) ^ (-(y & 1) & MATRIX_A);
        }
        y = (key_[N - 1] & UPPER_MASK) | (key_[0] & LOWER_MASK);
        key_[N - 1] = key_[M - 1] ^ (y >> 1) ^ (-(y & 1) & MATRIX_A);

        pos_ = 0;
    }
    y = key_[pos_++];

    /* Tempering */
    y ^= (y >> 11);
    y ^= (y << 7) & 0x9d2c5680UL;
    y ^= (y << 15) & 0xefc60000UL;
    y ^= (y >> 18);

    return y;
}

uint32_t MTRandom::RandomUint32() {
    return (uint32_t)Random();
}

uint64_t MTRandom::RandomUint64() {
    uint64_t upper = Random();
    uint64_t lower = Random();
    return (upper << 32) | lower;
}

double MTRandom::Uniform() {
    long a = Random() >> 5, b = Random() >> 6;
    return (a * 67108864.0 + b) / 9007199254740992.0;
}

