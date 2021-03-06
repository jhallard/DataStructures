#include "../../../DirectedGraph/dGraph.h"
#include "../../../../GraphTraveler/dTraveler.hpp"
#include <gtest/gtest.h>
#include <sstream>
#include <chrono>

TEST(EdgeTests, EmptyTest) {
  dGraph<std::string> graph;
  ASSERT_EQ(0, graph.getNumEdges());
  ASSERT_FALSE(graph.containsVertex("hello_there_mate"));
}

TEST(EdgeTests, SmallTest) {
  dGraph<std::string> graph;
  graph.insertVertex("hello");
  graph.insertVertex("Once Again");
  graph.insertVertex("ape");

  graph.insertEdge("hello", "ape", 22.0);
  graph.insertEdge("ape", "Once Again", 12.0);
  graph.insertEdge("ape", "Once Again", 12.0);
  ASSERT_EQ(2, graph.getNumEdges());
  ASSERT_EQ(true, graph.containsEdge("ape", "Once Again"));
  ASSERT_EQ(true, graph.containsEdge("hello", "ape"));
  ASSERT_FALSE(graph.containsEdge("hello", "Once Again"));
  ASSERT_FALSE(graph.containsEdge("Once Again", "ape"));
}

TEST(EdgeTests, LargeTest) {
 std::vector<std::string> file = readFile();
} 
