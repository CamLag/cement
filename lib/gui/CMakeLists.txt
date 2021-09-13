add_subdirectory(src)

file(GLOB_RECURSE HEADER *.h)
file(GLOB_RECURSE SRC src/*.cpp)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

add_library(cement_gui ${HEADER} ${SRC})
target_include_directories(cement_gui PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(cement_gui PUBLIC cement Qt5::Widgets)