add_subdirectory(src)

file(GLOB_RECURSE HEADER *.h)
file(GLOB_RECURSE SRC src/*.cpp)

add_library(cement_gui ${HEADER} ${SRC})
target_include_directories(cement_gui PUBLIC ${CMAKE_SOURCE_DIR})