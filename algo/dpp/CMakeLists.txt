PROJECT(DPPRank) 
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
aux_source_directory(src DIR_SRCS)
add_executable(../DPPRank ${DIR_SRCS})
add_executable(../gen_data ./gen_data.cpp ./util/matrix.h)

