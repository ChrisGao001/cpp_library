#ifndef ADLER32_H
#define ADLER32_H
/* 
    where data is the location of the data in physical memory and 
    len is the length of the data in bytes 
*/
#include <stdint.h>
#include <stddef.h>

uint32_t adler32(const char *data, size_t len);

#endif
