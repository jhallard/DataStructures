#include "../../UndirectedGraph/uGraph.h"
#include "../../DirectedGraph/dGraph.h"
#include "../../../GraphTraveler/uTraveler.hpp"
#include <gtest/gtest.h>
#include <sstream>
#include <chrono>
#include <ncurses.h>

//////////////////////////////////////
////////    Edge Testing    //////////

// - These tests involve the inserting and deleting of edges into our graph data structure.
TEST(EdgesTest, empty_graph) { 
    uGraph<int> graph;

    ASSERT_EQ(0, graph.getNumEdges());
}


TEST(EdgesTest, insert_few) { 
    uGraph<int> graph;

    graph.insertVertex(1);
    graph.insertVertex(2);
    graph.insertVertex(3);
    graph.insertVertex(4);
    graph.insertVertex(5);
    graph.insertVertex(6);

    graph.insertEdge(1, 2);
    graph.insertEdge(1, 3);
    graph.insertEdge(2, 3);
    graph.insertEdge(3, 4);
    graph.insertEdge(4, 1);
    graph.insertEdge(6, 2);

    ASSERT_EQ(6, graph.getNumEdges());
    ASSERT_EQ(true, graph.containsEdge(1, 2));
    ASSERT_EQ(true, graph.containsEdge(2, 1));
    ASSERT_EQ(true, graph.containsEdge(3, 4));
    ASSERT_EQ(true, graph.containsEdge(4, 3));
    ASSERT_EQ(false, graph.containsEdge(6, 3));
}


TEST(EdgesTest, insert_multiple) { 
    uGraph<int> graph;
    graph.insertVertex(1);
    graph.insertVertex(2);

    ASSERT_FALSE(!graph.insertEdge(1, 2)); // ok
    ASSERT_FALSE(graph.insertEdge(1, 2)); // duplicate
    ASSERT_FALSE(graph.insertEdge(2, 1)); // duplicate

}


TEST(EdgesTest, insert_multiple_larger) { 
    uGraph<int> graph;

    graph.insertVertex(1);
    graph.insertVertex(2);
    graph.insertVertex(3);
    graph.insertVertex(4);
    graph.insertVertex(5);
    graph.insertVertex(6);
    ASSERT_EQ(0, graph.getNumEdges());

    graph.insertEdge(1, 2); // ok
    graph.insertEdge(1, 3); // ok
    graph.insertEdge(2, 3); // ok
    graph.insertEdge(3, 4); // ok
    graph.insertEdge(4, 1); // ok
    graph.insertEdge(6, 2); // ok
    graph.insertEdge(1, 2); // duplicate
    graph.insertEdge(1, 3); // duplicate
    graph.insertEdge(2, 3); // duplicate
    graph.insertEdge(3, 4); // duplicate
    graph.insertEdge(4, 1); // duplicate
    graph.insertEdge(6, 2); // duplicate
    graph.insertEdge(6, 1); // ok

    ASSERT_EQ(7, graph.getNumEdges());
}

TEST(EdgesTest, edge_deletion) { 
    uGraph<int> graph;

    graph.insertVertex(1);
    graph.insertVertex(2);
    graph.insertVertex(3);
    graph.insertVertex(4);
    graph.insertVertex(5);
    graph.insertVertex(6);

    ASSERT_EQ(0, graph.getNumEdges());

    graph.insertEdge(1, 2); 
    graph.insertEdge(1, 3); 
    graph.insertEdge(2, 3); 
    graph.insertEdge(3, 4); 
    graph.insertEdge(4, 1); 
    graph.insertEdge(6, 2); 

    graph.deleteEdge(1, 2); 
    graph.deleteEdge(1, 3); 
    graph.deleteEdge(2, 3); 
    graph.deleteEdge(3, 4); 
    graph.deleteEdge(4, 1); 
    graph.deleteEdge(6, 2); 


    ASSERT_EQ(0, graph.getNumEdges());
}

TEST(EdgesTest, edge_deletion2) { 
    uGraph<int> graph;

    graph.insertVertex(1);
    graph.insertVertex(2);
    graph.insertVertex(3);
    graph.insertVertex(4);
    graph.insertVertex(5);
    graph.insertVertex(6);
    ASSERT_EQ(0, graph.getNumEdges());

    graph.insertEdge(1, 2); // ok
    graph.insertEdge(1, 3); // ok
    graph.insertEdge(2, 3); // ok
    graph.insertEdge(3, 4); // ok
    graph.insertEdge(4, 1); // ok
    graph.insertEdge(6, 2); // ok
    graph.deleteEdge(1, 2); // ok
    graph.deleteEdge(1, 3); // ok
    graph.deleteEdge(2, 3); // ok
    ASSERT_FALSE(graph.deleteEdge(2, 3)); // This edge shouldn't exist anymore
    graph.deleteEdge(4, 1); // ok
    ASSERT_FALSE(graph.deleteEdge(4, 2)); // This edge shouldn't exist anymore


    ASSERT_EQ(2, graph.getNumEdges());
}

 
TEST(EdgesTest, large_dense_graph) { 

    uGraph<int> graph;
    int numVertices = 400;
    std::vector<int> input_vec;

    for(int i = 1; i <= numVertices; i++) {
        input_vec.push_back(i);
    }

    graph.insertVertices(input_vec);
    int count = 0;
    for(int i = 1; i <= numVertices/2; i++) {
        for(int j = i+1; j <= numVertices; j++) {
            graph.insertEdge(i, j);
            count++;
        }
    }

    ASSERT_EQ(count, graph.getNumEdges());
}


TEST(EdgesTest, no_duplicates)  {
uGraph<int> graph;

    int numVertices = 400;
    int minEdges = 2;
    int maxEdges = 20;

    std::vector<int> input_vec;

    for(int i = 1; i <= numVertices; i++)
        input_vec.push_back(i);

    graph.insertVertices(input_vec);


    for(int i = 1; i < numVertices; i++) {

        int loop = rand() % (maxEdges-minEdges) + minEdges;

        for(int j = 0; j < loop; j++) {

            int r = rand() % numVertices + 1; r++;
            if(r == i) {
                j--;
                continue;
            }

            if(!graph.insertEdge(i, r))
                j--;
        }
    }

    // Go through every adjacency list and make sure no two edges point to the same vertex.
    for(int i = 1; i < graph.getNumVertices(); i++) {

        auto edges = graph.getIncidentEdges(i);
        std::unordered_map<int, bool> themap;

        for(int j = 0; j < edges.size(); j++) {
            ASSERT_FALSE(themap.find(j) != themap.end());
            themap.insert(std::pair<int, bool>(j, true));
        }
    }
}

TEST(EdgesTest, adj_vertices) { 
    uGraph<int> graph;

    graph.insertVertex(1);
    graph.insertVertex(2);
    graph.insertVertex(3);
    graph.insertVertex(4);
    graph.insertVertex(5);
    graph.insertVertex(6);
    ASSERT_EQ(0, graph.getNumEdges());

    graph.insertEdge(1, 2); // ok
    graph.insertEdge(1, 3); // ok
    graph.insertEdge(2, 3); // ok
    graph.insertEdge(3, 4); // ok
    graph.insertEdge(4, 1); // ok
    graph.insertEdge(6, 2); // ok
    graph.deleteEdge(1, 5); // ok

    auto edges = graph.getIncidentEdges(1);

    // Make sure the correct 3 edges are in this adj list
    ASSERT_EQ(true, (edges[0].getTarget()->getData() == 2 || edges[0].getTarget()->getData() == 3 || edges[0].getTarget()->getData() == 4));
    ASSERT_EQ(true, (edges[1].getTarget()->getData() == 2 || edges[1].getTarget()->getData() == 3 || edges[1].getTarget()->getData() == 4));
    ASSERT_EQ(true, (edges[2].getTarget()->getData() == 2 || edges[2].getTarget()->getData() == 3 || edges[2].getTarget()->getData() == 4));

}

TEST(EdgesTest, vertex_and_edge_deletion) { 
    uGraph<int> graph;

    graph.insertVertex(1);
    graph.insertVertex(2);
    graph.insertVertex(3);
    graph.insertVertex(4);
    graph.insertVertex(5);
    graph.insertVertex(6);
    ASSERT_EQ(0, graph.getNumEdges());

    graph.insertEdge(1, 2);
    graph.insertEdge(1, 3);
    graph.insertEdge(1, 4);
    graph.insertEdge(1, 5);
    graph.insertEdge(1, 6);
    graph.insertEdge(2, 3);
    graph.insertEdge(2, 4);
    graph.insertEdge(2, 5);
    graph.insertEdge(2, 6);
    graph.insertEdge(3, 4);
    graph.insertEdge(3, 5);
    graph.insertEdge(3, 6);
    graph.insertEdge(4, 5);
    graph.insertEdge(4, 6);
    graph.insertEdge(5, 6);

    ASSERT_EQ(6, graph.getNumVertices());
    ASSERT_EQ(15, graph.getNumEdges());

    graph.deleteVertex(2);

    ASSERT_EQ(5, graph.getNumVertices());
    ASSERT_EQ(10, graph.getNumEdges());

    graph.deleteVertex(1);

    ASSERT_EQ(4, graph.getNumVertices());
    ASSERT_EQ(6, graph.getNumEdges());

    graph.deleteVertex(3);

    ASSERT_EQ(3, graph.getNumVertices());
    ASSERT_EQ(3, graph.getNumEdges());

    graph.deleteVertex(4);

    ASSERT_EQ(2, graph.getNumVertices());
    ASSERT_EQ(1, graph.getNumEdges());

    graph.deleteVertex(5);

    ASSERT_EQ(1, graph.getNumVertices());
    ASSERT_EQ(0, graph.getNumEdges());

    graph.deleteVertex(6);

    ASSERT_EQ(0, graph.getNumVertices());
    ASSERT_EQ(0, graph.getNumEdges());

}
