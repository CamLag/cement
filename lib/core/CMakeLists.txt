add_subdirectory(src)

file(GLOB_RECURSE HEADER *.h)
file(GLOB_RECURSE SRC src/*.cpp)

add_library(cement ${HEADER} ${SRC})
target_include_directories(cement PUBLIC ${CMAKE_SOURCE_DIR})