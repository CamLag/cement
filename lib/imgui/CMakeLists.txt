file(GLOB_RECURSE HEADER *.h)
file(GLOB_RECURSE SRC src/*.cpp)

include(${CMAKE_SOURCE_DIR}/conan/conanbuildinfo_multi.cmake)

add_executable(cement_imgui
    ${SRC}
    ${HEADER}
    bindings/imgui_impl_sdl.cpp
    bindings/imgui_impl_opengl2.cpp
    bindings/imgui_impl_sdl.h
    bindings/imgui_impl_opengl2.h
)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

target_include_directories(cement_imgui PUBLIC ${CMAKE_SOURCE_DIR} ${SDL2_INCLUDE_DIRS})

target_link_libraries(cement_imgui ${CONAN_PKG_LIBS_IMGUI} GL ${SDL2_LIBRARIES} cement)
