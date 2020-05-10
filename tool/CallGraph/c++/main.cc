#include <cstdio>

int add(int a, int b) { return a+b;}


int main(int argc, char** argv) {
	int a = 3;
	int b = 4;
	int c = add(a, b);
	printf("sum=%d\n", c);
	return 0;
}
