cmake_minimum_required(VERSION 2.6)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11") 
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")

# Locate GTest
find_package(GTest REQUIRED)
find_package(Curses REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS}${CURSES_INCLUDE_DIR})

# Int Testing for graphs
add_executable(Testing/uGraphTesting/IntTesting/uGraphTestInt Testing/uGraphTesting/IntTesting/uGraphTestInt.cpp)
target_link_libraries(Testing/uGraphTesting/IntTesting/uGraphTestInt ${GTEST_LIBRARIES} ${CURSES_LIBRARIES} pthread)

add_executable(Testing/dGraphTesting/IntTesting/dGraphTestInt Testing/dGraphTesting/IntTesting/dGraphTestInt.cpp)
target_link_libraries(Testing/dGraphTesting/IntTesting/dGraphTestInt ${GTEST_LIBRARIES} ${CURSES_LIBRARIES} pthread)

# String Testing for Graphs
add_executable(Testing/dGraphTesting/StringTesting/dGraphTestString Testing/dGraphTesting/StringTesting/dGraphTestString.cpp)
target_link_libraries(Testing/dGraphTesting/StringTesting/dGraphTestString ${GTEST_LIBRARIES} ${CURSES_LIBRARIES} pthread)

add_executable(Testing/uGraphTesting/StringTesting/uGraphTestString Testing/uGraphTesting/StringTesting/uGraphTestString.cpp)
target_link_libraries(Testing/uGraphTesting/StringTesting/uGraphTestString ${GTEST_LIBRARIES} ${CURSES_LIBRARIES} pthread)

add_executable(Main/main Main/main.cpp)
