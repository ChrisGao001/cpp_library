#include <stdlib.h>
#include <sys/time.h>
#include <iostream>
#include <sstream>
#include <utility>
#include <vector>
#include "formater.h"

size_t GetTime() {
    struct timeval now;
        gettimeofday(&now, NULL);
    return (now.tv_sec * 1000 + now.tv_usec / 1000);
}

#define logger(text) do { \
	std::ostringstream oss; \
	oss << text << "\n"; \
	std::cout << oss.str(); \
} while (0)

std::string to_int(const int &n) {
	char buf[10];
	snprintf(buf, 10, "%d", n);
	return std::string(buf);
}

int main(int argc, char** argv) {
	const int n = 1000000;
	logger("begin to work!");
	std::vector<int> items;
	items.reserve(n);
	for (int i=0; i<n; ++i) {
		int v = rand();
		items.push_back(v);
		// std::string k = formater::tostr(v);
		// logger("k=" << v << ", str=" << k);
	}

	size_t start = GetTime();
	for (const auto& item : items) {
		std::string k = formater::tostr(item);
	}
	size_t end = GetTime();
	logger("special cost " << (end - start) << " ms");

	start = GetTime();
	for (const auto& item : items) {
		// std::string k = std::to_string(item);
		std::string k = to_int(item);
	}
	end = GetTime();
	logger("std cost " << (end - start) << " ms");
	double l = 3.14;
	logger("k=" << formater::tostr(l));
	
	return 0;
}

