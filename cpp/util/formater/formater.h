#ifndef FORMATER_H
#define FORMATER_H
#include <stdint.h>
#include <iostream>
#include <string>
#include "branchlut.h"

namespace formater {

inline unsigned CountDecimalDigit32(uint32_t n) {
#if defined(__GNUC__)
    static const uint32_t powers_of_10[] = {
        0,
        10,
        100,
        1000,
        10000,
        100000,
        1000000,
        10000000,
        100000000,
        1000000000
    };
    uint32_t t = (32 - __builtin_clz(n | 1)) * 1233 >> 12;
    return t - (n < powers_of_10[t]) + 1;
#else
    // Simple pure C++ implementation
    if (n < 10) return 1;
    if (n < 100) return 2;
    if (n < 1000) return 3;
    if (n < 10000) return 4;
    if (n < 100000) return 5;
    if (n < 1000000) return 6;
    if (n < 10000000) return 7;
    if (n < 100000000) return 8;
    if (n < 1000000000) return 9;
    return 10;
#endif
}

inline unsigned CountDecimalDigit64(uint64_t n) {
#if defined(_MSC_VER) || defined(__GNUC__)
    static const uint64_t powers_of_10[] = {
        0,
        10,
        100,
        1000,
        10000,
        100000,
        1000000,
        10000000,
        100000000,
        1000000000,
        10000000000,
        100000000000,
        1000000000000,
        10000000000000,
        100000000000000,
        1000000000000000,
        10000000000000000,
        100000000000000000,
        1000000000000000000,
        10000000000000000000U
    };
    uint32_t t = (64 - __builtin_clzll(n | 1)) * 1233 >> 12;
    return t - (n < powers_of_10[t]) + 1;
#else
    // Simple pure C++ implementation
    if (n < 10) return 1;
    if (n < 100) return 2;
    if (n < 1000) return 3;
    if (n < 10000) return 4;
    if (n < 100000) return 5;
    if (n < 1000000) return 6;
    if (n < 10000000) return 7;
    if (n < 100000000) return 8;
    if (n < 1000000000) return 9;
    if (n < 10000000000) return 10;
    if (n < 100000000000) return 11;
    if (n < 1000000000000) return 12;
    if (n < 10000000000000) return 13;
    if (n < 100000000000000) return 14;
    if (n < 1000000000000000) return 15;
    if (n < 10000000000000000) return 16;
    if (n < 100000000000000000) return 17;
    if (n < 1000000000000000000) return 18;
    if (n < 10000000000000000000) return 19;
    return 20;
#endif
}

template <typename T>
std::string tostr(const T& v) {
    std::ostringstream oss;
    oss << v;
    return oss.str();
}

template <>
std::string tostr(const int32_t& v) {
    char buf[10];
    i32toa_branchlut(v, buf);
    return std::string(buf);
}

template <>
std::string tostr(const uint32_t& v) {
    char buf[10];
    u32toa_branchlut(v, buf);
    return std::string(buf);    
}

template <>
std::string tostr(const int64_t& v) {
    char buf[20];
    i64toa_branchlut(v, buf);
    return std::string(buf);    
}

template <>
std::string tostr(const uint64_t& v) {
    char buf[20];
    u64toa_branchlut(v, buf);
    return std::string(buf);      
}

}

#endif
