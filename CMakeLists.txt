cmake_minimum_required(VERSION 3.9)
project(MatrixMul)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS -fopenmp)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "/home/sinigr/CLionProjects/Binaries")

add_subdirectory(fmt)

add_executable(MatrixMul main.cpp matrix/matrix.h matrix/block_matrix.h matrix/multiplier/algorithm/native_algorithm.h matrix/multiplier/algorithm/parallel_inner_algorithm.h matrix/multiplier/matrix_multiplier.h matrix/multiplier/algorithm/parallel_outer_algorithm.h)
target_link_libraries(MatrixMul PRIVATE fmt::fmt-header-only)