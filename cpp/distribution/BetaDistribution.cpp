
#include "BetaDistribution.h"
#include "distributions.h"

BetaDistribution::BetaDistribution(int seed, double a, double b) {
	Init(seed, a, b);
}

void BetaDistribution::Init(int seed, double a, double b) {
	a_ = a;
	b_ = b;
	seed_ = seed;
	rk_seed(seed, &state_);
}

double BetaDistribution::Next() {
	double m = rk_beta(&state_, a_, b_);
	return m;
}

