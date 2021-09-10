cmake_minimum_required(VERSION 3.0.0)
project(Cement VERSION 0.1.0)

add_subdirectory(src)

file(GLOB_RECURSE HEADER *.h)
file(GLOB_RECURSE SRC src/*.cpp)

add_executable(Cement ${HEADER} ${SRC})
