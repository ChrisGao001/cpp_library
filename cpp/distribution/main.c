#include <stdio.h>
#include "distributions.h"

int main(int argc, char **argv) {
	rk_state state;
	rk_seed(1234, &state);
	double r = rk_double(&state);
	double m = rk_beta(&state, 2, 5);
	printf("random %f\n", r);
	printf("beta %f\n", m);
	
	return 0;
}	
