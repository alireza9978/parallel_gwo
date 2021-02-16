cmake_minimum_required(VERSION 3.17)
project(parallel_gwo)

set(CMAKE_CXX_STANDARD 14)

add_executable(parallel_gwo main.cpp gray_wolf_optimizer.cpp gray_wolf_optimizer.h solution.cpp solution.h)