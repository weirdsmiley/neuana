# add_executable(concrete concrete.cpp)
# target_link_libraries(concrete LINK_PUBLIC ErrorAnalysis)

# add_test(NAME check-concrete
#   COMMAND concrete)

# add_executable(vector vector.cpp)
# target_link_libraries(vector LINK_PUBLIC ErrorAnalysis)

# add_test(NAME check-vector
#   COMMAND vector)

# add_executable(vectorxvector vectorxvector.cpp)
# target_link_libraries(vectorxvector LINK_PUBLIC ErrorAnalysis)

# add_test(NAME check-vectorxvector
#   COMMAND vectorxvector)

add_executable(test1 test1.cpp)
target_link_libraries(test1 LINK_PUBLIC neuana)

