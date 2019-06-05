#include <stdio.h>
#include <algorithm>
#include <vector>
#include "distributions.h"
#include "BetaDistribution.h"

using namespace std;
struct mab_feature {
	int id;
	double a;
	double b;
	double prob;
	mab_feature(int _id=0, double _a=0, double _b=0, double _prob=0) { id = _id;a = _a; b = _b; prob=0;}
	bool operator <(const mab_feature &a) const { return prob > a.prob;}
};

int main(int argc, char **argv) {
	rk_state state;
	rk_seed(123, &state);
        BetaDistribution beta; 
	vector<mab_feature> features;
	for (size_t i=0; i<10; ++i) {
		mab_feature feature(i);
		feature.a = rk_random(&state) % 100;
		feature.b = rk_random(&state) % 100;
		beta.Init(1234, feature.a, feature.b);
		feature.prob = beta.Next();
		features.push_back(feature);
        	printf("id:%d, %f, %f, %f\n", feature.id, feature.a, feature.b, feature.prob); 
	}
	std::stable_sort(features.begin(), features.end());
	for (size_t i=0; i<features.size(); ++i) {
		mab_feature &feature = features[i];
		double ratio = feature.a / (feature.a + feature.b);
        	printf("[sort] id:%d, %f, %f,%f, %f\n", feature.id, feature.a, feature.b, ratio, feature.prob); 
	}
    
	return 0;
}	
