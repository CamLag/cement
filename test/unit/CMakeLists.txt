enable_testing()

add_executable(core_unit core_unit.cpp)

target_include_directories(core_unit PUBLIC ${CONAN_INCLUDE_DIRS_GTEST})
target_link_libraries(core_unit gtestd gtest_maind) 
#CONAN_LIBS_GTEST