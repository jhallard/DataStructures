
#include "../../../UndirectedGraph/uGraph.h"
#include "../../../../GraphTraveler/uTraveler.hpp"
#include <gtest/gtest.h>
#include <sstream>
#include <chrono>

#include "ReadWords.h"


//////////////////////////////////////
////////    Vertex Testing    ////////
// - These tests involve the inserting and deleting of vertices into our graph data structure.

TEST(VerticesTest, emptyGraphTest) {

    uGraph<std::string> graph;

    ASSERT_EQ(0, graph.getNumVertices());
    ASSERT_FALSE(graph.containsVertex("hello"));
}

TEST(VerticesTest, smallVertexInsert) {

    uGraph<std::string> graph;

    graph.insertVertex("hello");
    graph.insertVertex("goodbye");
    graph.insertVertex("you still there?");

    ASSERT_EQ(3, graph.getNumVertices());
    ASSERT_EQ(true, graph.containsVertex("hello"));
    ASSERT_EQ(true, graph.containsVertex("goodbye"));
    ASSERT_EQ(true, graph.containsVertex("you still there?"));
    ASSERT_FALSE(graph.containsVertex("jaja"));
}

TEST(VerticesTest, largeVertexInsert) {

    uGraph<std::string> graph;

    std::vector<std::string> file = readFile();

    graph.insertVertices(file);

    for(int i = 0; i < file.size(); i++) {
        ASSERT_EQ(true, graph.containsVertex(file[i]));
    }
}


TEST(VerticesTest, largeVertexInsertDelete) {

    uGraph<std::string> graph;

    std::vector<std::string> file = readFile();

    graph.insertVertices(file);

    int count = 0;
    for(int i = 0; i < file.size(); i++) {
        count++;
        // std::cout << file[i] << "\n";
        ASSERT_EQ(true, graph.containsVertex(file[i]));
    }

    for(int i = 0; i < file.size(); i++) {
        ASSERT_EQ(true, graph.deleteVertex(file[i]));
    }

    std::cout << count << "\n\n";
    ASSERT_EQ(0, graph.getNumVertices());
}