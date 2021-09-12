add_executable(cement_test Main.cpp)

target_include_directories(cement_test PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(cement_test cement)