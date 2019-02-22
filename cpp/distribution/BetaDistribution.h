#ifndef BETA_DISTRIBUTION_H
#define BETA_DISTRIBUTION_H

#include "randomkit.h"

class BetaDistribution
{
public:
	BetaDistribution(int seed=0, double a=0.0, double b=0.0);
	void Init(int seed, double a, double b);
	~BetaDistribution() {}
	double Next();
private:
	int seed_;
	double a_;
	double b_;
	rk_state state_;
};
#endif
