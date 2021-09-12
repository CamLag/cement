cmake_minimum_required(VERSION 3.0.0)
project(Cement VERSION 0.1.0)

add_subdirectory(test)
add_subdirectory(lib)

set(LIB_DIR = ${CMAKE_SOURCE_DIR}/lib)
set(TEST_DIR = ${CMAKE_SOURCE_DIR}/test)
