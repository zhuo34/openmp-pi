cmake_minimum_required(VERSION 3.14)
project(openmp_pi)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-Xpreprocessor -fopenmp -lomp")

add_executable(openmp_pi main.cpp pi.cpp pi.h)
target_link_libraries(openmp_pi gmpxx gmp)
