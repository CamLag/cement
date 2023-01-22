cmake_minimum_required(VERSION 3.0.0)
project(Cement VERSION 0.1.0)

include(conan/conanbuildinfo.cmake)
conan_basic_setup()

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 17)

add_subdirectory(test)
add_subdirectory(lib)
