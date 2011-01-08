cmake_minimum_required (VERSION 2.8)
project (LLBoy)

set (LLBoy_VERSION_MAJOR 0)
set (LLBoy_VERSION_MINOR 1)
set (LLBoy_VERSION_MICRO 0)

# Pull in LLVM functionality
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules")
find_package(LLVM REQUIRED)
include_directories(${LLVM_INCLUDE_DIRS})
link_directories(${LLVM_LIBRARY_DIRS})
add_definitions(${LLVM_DEFINITIONS})

# Core system library
add_subdirectory (sys)

add_executable (LLBoy main.cpp)
target_link_libraries (LLBoy ${LLVM_LIBRARIES})