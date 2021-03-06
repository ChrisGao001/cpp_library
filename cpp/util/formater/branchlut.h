#ifndef BRANCHLUT_H
#define BRANCHLUT_H
#include <stdint.h>

void u32toa_branchlut(uint32_t value, char* buffer);
void i32toa_branchlut(int32_t value, char* buffer);
void u64toa_branchlut(uint64_t value, char* buffer);
void i64toa_branchlut(int64_t value, char* buffer);
#endif
