cmake_minimum_required(VERSION 2.6)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11") 

# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
 
add_executable(Testing/uGraphTesting/IntTesting/uGraphTestInt Testing/uGraphTesting/IntTesting/uGraphTestInt.cpp)

target_link_libraries(Testing/uGraphTesting/IntTesting/uGraphTestInt ${GTEST_LIBRARIES} pthread)

add_executable(Testing/dGraphTesting/IntTesting/dGraphTestInt Testing/dGraphTesting/IntTesting/dGraphTestInt.cpp)

target_link_libraries(Testing/dGraphTesting/IntTesting/dGraphTestInt ${GTEST_LIBRARIES} pthread)

add_executable(Main/main Main/main.cpp)
