#include <stdio.h>
#include "distributions.h"

int main(int argc, char **argv) {
	rk_state state;
	rk_seed(134, &state);
	double arr[100];
	for (int i=0; i<100;++i) {
		arr[i] = rk_double(&state)*2;
	}

	for (int i=0; i<100;++i) {
		if (i % 10 == 0) {
			printf("\n%f", arr[i]);
		} else {
			printf(",%f", arr[i]);
		}
	}
	printf("\n");
	
	return 0;
}	
