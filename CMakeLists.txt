cmake_minimum_required(VERSION 3.23)
project(neuana VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_BUILD_TYPE Debug)

# set(GCC_COVERAGE_COMPILE_FLAGS "-g -O0 -coverage -fprofile-arcs -ftest-coverage")
# set(GCC_COVERAGE_LINK_FLAGS    "-coverage -lgcov")
# set( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}" )
# set( CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}" )

include(CTest)

option(ENABLE_TESTING "Enable testing neuana library.")
if (ENABLE_TESTING)
  message("-- Test cases are enabled")
  add_subdirectory(tests)
else ()
  message("-- Test cases are disabled")
endif()

add_subdirectory(lib)
include_directories(include)
