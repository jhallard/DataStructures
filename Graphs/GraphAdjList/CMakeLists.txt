cmake_minimum_required(VERSION 2.6)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11") 

# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
 
# Link runTests with what we want to test and the GTest and pthread library
add_executable(Testing/uGraphTesting/MainTestSuite Testing/uGraphTesting/MainTestSuite.cpp)
target_link_libraries(Testing/uGraphTesting/MainTestSuite ${GTEST_LIBRARIES} pthread)

add_executable(Main/main Main/main.cpp)
