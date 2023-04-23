cmake_minimum_required(VERSION 3.20)
project(coffee VERSION 0.2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Pull in project local cmake
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules)

# list( APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake/Modules)

# Version number
set(coffee_VERSION_MAJOR 0)
set(coffee_VERSION_MINOR 1)

# Compiler flags: need different builds
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

# FIXME: target scope
add_compile_options(
  -Wall -Werror -Wshadow -Wuninitialized
  $<$<CONFIG:RELEASE>:-O3>
  $<$<CONFIG:DEBUG>:-O0>
  $<$<CONFIG:DEBUG>:-fno-inline>
  $<$<CONFIG:DEBUG>:-ggdb3>
)
add_compile_definitions(
  $<$<CONFIG:RELEASE>:NDEBUG>
)

# set(CMAKE_INCLUDE_SYSTEM_FLAG "-isystemX")
# set(CMAKE_INCLUDE_SYSTEM_FLAG_CXX "-isystemX")
file(TO_CMAKE_PATH "${PROJECT_BINARY_DIR}/CMakeLists.txt" LOC_PATH)

if(EXISTS "${LOC_PATH}")
  message(FATAL_ERROR "You cannot build in the source directory (or any with a CMakeLists.txt)")
endif()

# Spdlog
find_package(fmt REQUIRED)
find_package(spdlog REQUIRED)
add_compile_definitions(SPDLOG_FMT_EXTERNAL)

# add_compile_definitions(
# $<$<CONFIG:DEBUG>:SPDLOG_ACTIVE_LEVEL=SPDLOG_LEVEL_DEBUG>)

# SLD2
find_package(SDL2 REQUIRED)

# Eigen for vector math
find_package(Eigen3 3.4 REQUIRED NO_MODULE)

# ####   Project Modules ######

# Add the coffee library
add_subdirectory(src)

# googletest
# add_subdirectory( googletest )
option(COFFEE_TESTS "Build the tests" ON)

if(COFFEE_TESTS)
  enable_testing()
  include(GoogleTest)
  include(CTest)
  add_subdirectory("extern/googletest")
  add_subdirectory(tests)
endif()

# # TODO: testing is always built?

# google benchmark TODO: possible to remove these options from cmake entirely and set these as defaults
option(COFFEE_BENCHMARKS "Enable benchmark testing of libraries (Google Benchmark)." ON)

if(COFFEE_BENCHMARKS)
  set(BENCHMARK_ENABLE_GTEST_TESTS 0)
  set(BENCHMARK_ENABLE_TESTING 0)
  set(BENCHMARK_ENABLE_INSTALL 0)
  add_subdirectory("extern/benchmark")

  # add_subdirectory(benchmarks)
endif()

add_subdirectory(apps)

# TODO: install