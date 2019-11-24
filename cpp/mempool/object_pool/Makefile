all : object_pool 
object_pool : main.cc thread_local.cpp
	g++ -std=c++11 -o $@ $^ -I./ -lpthread
.Phoney clean:
	rm -rf *.o object_pool
