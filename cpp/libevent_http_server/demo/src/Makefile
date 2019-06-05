
all:http_server
http_server:http_handler.cpp main.cc util.cpp http_server.cpp
	g++ $^ -o $@ -I./ -L/usr/local/include -levent -lpthread
