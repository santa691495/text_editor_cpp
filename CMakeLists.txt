# TODO : link gtest to executable of gapbuffer unittest.
cmake_minimum_required(VERSION 3.10)
project(text_editor)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(gtest)
add_subdirectory(src)
add_subdirectory(tests)

include(gtest)
gtest_discover_tests(gapbuffer_tests)
