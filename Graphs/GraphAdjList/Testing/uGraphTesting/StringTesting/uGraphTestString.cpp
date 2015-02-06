/**
*   @Author   - John H Allard Jr.
*   @File     - MainTestSuite.cpp
*   @Data     - 1/19/2015
*   @Purpose  - This file contains all of the main tests for the undirected graph class. The testing framework is provided by Google via their 
*               Google Test suite for C++. 
**/


#include "../../../UndirectedGraph/uGraph.h"
#include "../../../../GraphTraveler/uTraveler.hpp"
#include "uGraphVertexTest.h"
#include <gtest/gtest.h>
#include <sstream>
#include <chrono>


 
int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
