
#include "../../DirectedGraph/dGraph.h"
#include "../../../GraphTraveler/dTraveler.hpp"
#include <gtest/gtest.h>
#include <sstream>
#include <chrono>


//////////////////////////////////////
////////    Vertex Testing    ////////
// - These tests involve the inserting and deleting of vertices into our graph data structure.
TEST(VerticesTest, empty_Graph) { 
    dGraph<int> graph;

    ASSERT_EQ(0, graph.getNumVertices());
}

TEST(VerticesTest, insert_one_by_one) { 
    dGraph<int> graph;
    int numVertices = rand()%800+2;

    std::vector<int> input_vec;
    for(int i = 1; i <= numVertices; i++)
        graph.insertVertex(i);

    ASSERT_EQ(numVertices, graph.getNumVertices());
    ASSERT_EQ(true, graph.containsVertex(23));
    ASSERT_EQ(true, graph.containsVertex(125));
    ASSERT_EQ(true, graph.containsVertex(76));

    ASSERT_FALSE(graph.containsVertex(802));
    ASSERT_FALSE(graph.containsVertex(-1));
    ASSERT_FALSE(graph.containsVertex(10512));

}

TEST(VerticesTest, insert_all_at_once) { 
dGraph<int> graph;
    int numVertices = rand()%800+2;

    std::vector<int> input_vec;
    for(int i = 1; i <= numVertices; i++)
        input_vec.push_back(i);

    graph.insertVertices(input_vec);

    ASSERT_EQ(numVertices, graph.getNumVertices());
    ASSERT_EQ(true, graph.containsVertex(23));
    ASSERT_EQ(true, graph.containsVertex(125));
    ASSERT_EQ(true, graph.containsVertex(76));

    ASSERT_FALSE(graph.containsVertex(802));
    ASSERT_FALSE(graph.containsVertex(-1));
    ASSERT_FALSE(graph.containsVertex(10512));
}



TEST(VerticesTest, large_insert_delete) {
    dGraph<int> graph;
    std::vector<int> vec;
    std::unordered_map<int, bool> m;

    for(int i = 0; i < 8000; i++) {
        int temp = rand()%1367532+200;
        if(m.find(temp) != m.end()) {
            i--;
            continue;
        }
        m.insert(std::pair<int,bool>(temp, true));
        vec.push_back(temp);
        graph.insertVertex(temp);
    }

    for(int i = 0; i < vec.size(); i++) {
        ASSERT_EQ(true, graph.deleteVertex(vec[i]));
    }

    ASSERT_EQ(0, graph.getNumVertices());
}


TEST(VerticesTest, test_no_duplicates) { 
dGraph<int> graph;
    int numVertices = rand()%800+2;

    std::vector<int> input_vec;

    for(int i = 1, j = 0; i <= numVertices; i++) {
        if(j == numVertices/2)
            j = 1;
        input_vec.push_back(j++);
    }

    graph.insertVertices(input_vec);

    ASSERT_EQ(numVertices/2, graph.getNumVertices());
}

TEST(VerticesTest, delete_test) { 
dGraph<int> graph;
    int numVertices = rand()%800+2;

    std::vector<int> input_vec;

    for(int i = 1; i <= numVertices; i++) {
        input_vec.push_back(i);
    }

    graph.insertVertices(input_vec);

    int numRemove = rand()%(numVertices+1)-1;
    for(int i = 1; i <= numRemove; i++)
        graph.deleteVertex(i);

    ASSERT_EQ((int)(numVertices-numRemove), graph.getNumVertices());
}



