#include <stdio.h>
#include <iostream>
#include "resource_pool.h"
#define logger(fmt, ...) fprintf(stdout, fmt"\n", ##__VA_ARGS__)
using namespace butil;
using namespace std;
int main(int argc, char** argv) {
	std::vector<ResourceId<int>> ids;
	for (int i=0; i<10;++i) {
	    ResourceId<int> id;
		id.value = 0;
	    int* p = get_resource<int>(&id);
		*p = i*2;
	    logger("id=%llu, res=%p, value=%d", (id.value), p, (*p));
		ids.emplace_back(id);
	}
	return_resource<int>(ids[3]);
	for (int i=0; i<10;++i) {
	    ResourceId<int> id;
		id.value = 0;
	    int* p = get_resource<int>(&id);
		*p = i*2;
	    logger("id=%llu, res=%p, value=%d", (id.value), p, (*p));
		ids.emplace_back(id);
	}
	butil::ResourcePoolInfo res_info = describe_resources<int>();
	cout << res_info << endl;

	return 0;
}
