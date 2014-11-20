
#include "../UndirectedGraph/uGraph.h"
#include <gtest/gtest.h>
 
TEST(VerticesTest, InsertVertices) { 
uGraph<int> graph;
    int numVertices = rand()%800+2;

    std::vector<int> input_vec;
    for(int i = 1; i <= numVertices; i++)
        graph.insertVertex(i);

    ASSERT_EQ(numVertices, graph.getNumVertices());
}

TEST(VerticesTest, InsertVertices2) { 
uGraph<int> graph;
    int numVertices = rand()%800+2;

    std::vector<int> input_vec;
    for(int i = 1; i <= numVertices; i++)
        input_vec.push_back(i);

    graph.insertVertices(input_vec);

    ASSERT_EQ(numVertices, graph.getNumVertices());
}

TEST(VerticesTest, InsertVertices3) { 
uGraph<int> graph;
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
 
int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}