#include <sys/time.h>
#include <iostream>
#include <vector>
#include <cstdlib>
#include "gfx/timsort.hpp"

#define logger(text)  do {\
    cout << text << endl; \
    } while(0)

using namespace std;

size_t GetTime() {
    struct timeval now;
        gettimeofday(&now, NULL);
    return (now.tv_sec * 1000 + now.tv_usec / 1000);
}

int main(int argc, char** argv) {
    vector<int> items;
    srand(0);
    for (int i=0; i<10000; ++i) {
	    items.emplace_back(rand() % 1000000);
	} 
    std::stable_sort(items.begin(), items.end(), [](const int &a, const int &b) { return a < b;});
    vector<vector<int>> items_a;
    vector<vector<int>> items_b;
    for (size_t i=0; i<100; ++i) {
		items_a.push_back(items);
		items_b.push_back(items);
	}
	#if 0
	for (auto& item : items) {
		cout << item << " ";
	}
	cout << endl;
	#endif
    size_t start = GetTime();
    for (auto& item : items_a) {
    	gfx::timsort(item.begin(), item.end(), [](const int &a, const int &b) { return a > b;});
	}
    size_t end = GetTime();
    logger("timsort cost:" << (end - start) << " ms");
    start = GetTime();
    for (auto& item : items_b) {
    	std:stable_sort(item.begin(), item.end(), [](const int &a, const int &b) { return a > b;});
	}
    end = GetTime();
    logger("stable_sort cost:" << (end - start) << " ms");
	#if 0
    cout << "after sort" << endl;
	for (auto& item : items) {
		cout << item << " ";
	}
	cout << endl;
	#endif


    return 0;
}
