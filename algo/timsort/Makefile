all : sort_test
sort_test : main.cpp
	g++ -std=c++11 -O2 -o $@ $^ -I./
.Phoney clean:
	@rm -rf sort_test *.o
