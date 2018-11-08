#include "adler32.h"

uint32_t adler32(const char *data, size_t len) 
{
    const uint32_t MOD_ADLER = 65521;
    uint32_t a = 1, b = 0;
    size_t index;
    
    // Process each byte of the data in order
    for (index = 0; index < len; ++index)
    {
        a = (a + (unsigned char)data[index]) % MOD_ADLER;
        b = (b + a) % MOD_ADLER;
    }
    
    return (b << 16) | a;
}

