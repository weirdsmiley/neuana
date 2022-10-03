# ErrorAnalysis library - A tooling library for calculating errors on-the-fly.

add_library(neuana Analysis.cpp)

target_include_directories(neuana PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
