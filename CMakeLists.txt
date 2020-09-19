cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

project(lightpad CXX)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Build type" FORCE)
endif()

# template template parameter using 'typename' is a C++17 extension
# see rbtree.h class rbtree_base LoL
set(CMAKE_CXX_STANDARD 17)

include(CMakeParseArguments)
include(CheckIncludeFiles)
include(cmake/macro.cmake)
include(cmake/options.cmake)
include_platform(flags)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_BINARY_DIR}/bin")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/bin")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_BINARY_DIR}/bin")

include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${CMAKE_CURRENT_BINARY_DIR}/include)

add_subdirectory(src)

if (LP_ENABLE_TESTS)
    add_subdirectory(tests)
endif()
