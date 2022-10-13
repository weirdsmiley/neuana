add_executable(scalar scalar.cpp)
target_link_libraries(scalar LINK_PUBLIC neuana)

add_executable(vector1d vector1d.cpp)
target_link_libraries(vector1d LINK_PUBLIC neuana)

add_executable(vector2d vector2d.cpp)
target_link_libraries(vector2d LINK_PUBLIC neuana)

add_test(NAME scalar COMMAND scalar)
add_test(NAME vector1d COMMAND vector1d)
add_test(NAME vector2d COMMAND vector2d)
