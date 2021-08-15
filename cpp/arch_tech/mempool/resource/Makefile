all : resource_pool 
resource_pool : main.cc thread_local.cpp
	g++ -std=c++11 -o $@ $^ -I./ -lpthread
.Phoney clean:
	rm -rf *.o resource_pool
