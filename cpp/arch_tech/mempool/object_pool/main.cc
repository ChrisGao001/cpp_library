#include <iostream>
#include "object_pool.h"

using namespace std;

#define logger(text) do { \
    cout << "[DEBUG] " << text << "\n"; \
} while (0)

int main(int argc, char** argv) {
    vector<int *> ids;
    for (int i = 0; i < 10; ++i) {
        int *p = butil::get_object<int>();
        *p = i;
        logger("ptr:" << p << ",value:" << *p);
        ids.push_back(p);
    }
    butil::return_object<int>(ids[3]);
	ids[3] = nullptr;
	for (int i=0; i<5; ++i) {
		int *p = butil::get_object<int>();
		*p = 10 + i;
        logger("ptr:" << p << ",value:" << *p);
        ids.push_back(p);
	}
	butil::ObjectPoolInfo meminfo = butil::describe_objects<int>();
	logger(meminfo);
    return 0;
}
