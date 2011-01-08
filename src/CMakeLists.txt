cmake_minimum_required (VERSION 2.8)
project (LLBoy)

set (LLBoy_VERSION_MAJOR 0)
set (LLBoy_VERSION_MINOR 1)
set (LLBoy_VERSION_MICRO 0)

add_subdirectory (sys)
add_executable (LLBoy main.cpp)