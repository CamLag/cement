file(GLOB_RECURSE HEADER *.h)
file(GLOB_RECURSE SRC src/*.cpp)

find_package(imgui)

add_executable(cement_imgui ${HEADER} ${SRC})
target_include_directories(cement_imgui PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(cement_imgui imgui::imgui)
