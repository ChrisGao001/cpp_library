cmake_minimum_required(VERSION 3.6.0)
project(BloomFilter)

set(CMAKE_CXX_STANDARD 11)

add_executable(BloomFilter main.cpp BloomFilter.cpp BloomFilter.h)
