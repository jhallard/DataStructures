/**
*   @Author   - John H Allard Jr.
*   @File     - MainTestSuite.cpp
*   @Data     - 11/19/2014
*   @Purpose  - This file contains all of the main tests for the undirected graph class. The testing framework is provided by Google via their 
*               Google Test suite for C++. Below you will see numerous groupings of different tests. These groupings of tests all test one aspect
*               of the graph in different ways, they are run individually then tallied together to ensure that entire subsystems work correctly.
*               The different sections of dGraph that will be tested are as follows :
*               1.) Vertex Testing    - Tests the insertion, deletion, and lookup of vertices in the graph. 
*               2.) Edge Testing      - Tests the insertion, deletion, and lookup of edges in the graph. This includes making sure so duplicates for
*                                       non multi-graphs.
*               3.) Algorithm/Speed Testing - Tests the various algorithms that come with this graph.
**/


#include "../../DirectedGraph/dGraph.h"
#include "../../../GraphTraveler/dTraveler.hpp"
//#include "dGraphVertexTesting.h"
//#include "dGraphEdgeTesting.h"
//#include "dGraphOtherTesting.h"
#include "dGraphDijkstraTesting.h"
//#include "dGraphMinTreeTesting.h"
#include <gtest/gtest.h>
#include <sstream>
#include <chrono>


 
int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}