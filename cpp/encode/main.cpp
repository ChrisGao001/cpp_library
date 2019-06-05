#include "adler32.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv) {
	const char *d = "liming";
	uint32_t k = adler32(d, strlen(d));
	printf("string=%s, key=%u\n", d, k);
	return 0;
}
