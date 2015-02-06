#include "../../../UndirectedGraph/uGraph.h"
#include "../../../../GraphTraveler/uTraveler.hpp"
#include <gtest/gtest.h>
#include "ReadWords.h"
#include <sstream>
#include <chrono>

TEST(EdgeTests, EmptyTest) {
  uGraph<std::string> graph;
  ASSERT_EQ(0, graph.getNumEdges());
  ASSERT_FALSE(graph.containsVertex("hello_there_mate"));
}

TEST(EdgeTests, SmallTest) {
  uGraph<std::string> graph;
  graph.insertVertex("hello");
  graph.insertVertex("Once Again");
  graph.insertVertex("ape");

  graph.insertEdge("hello", "ape", 22.0);
  graph.insertEdge("ape", "Once Again", 12.0); 
  ASSERT_EQ(2, graph.getNumEdges());
  ASSERT_EQ(true, graph.containsEdge("ape", "Once Again"));
  ASSERT_EQ(true, graph.containsEdge("hello", "ape"));
  ASSERT_FALSE(graph.containsEdge("OnOncegain", "ape"));
}

TEST(EdgeTests, LargeTest) {
  std::vector<std::string> file = readFile();
}

