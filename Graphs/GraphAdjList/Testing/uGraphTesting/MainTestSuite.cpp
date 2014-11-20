/**
*   @Author   - John H Allard Jr.
*   @File     - MainTestSuite.cpp
*   @Data     - 11/19/2014
*   @Purpose  - This file contains all of the main tests for the undirected graph class. The testing framework is provided by Google via their 
*				Google Test suite for C++. Below you will see numerous groupings of different tests. These groupings of tests all test one aspect
*				of the graph in different ways, they are run individually then tallied together to ensure that entire subsystems work correctly.
*				The different sections of uGraph that will be tested are as follows :
*				1.) Vertex Testing    - Tests the insertion, deletion, and lookup of vertices in the graph. 
*				2.) Edge Testing      - Tests the insertion, deletion, and lookup of edges in the graph. This includes making sure so duplicates for
*									    non multi-graphs.
*				3.) Algorithm Testing - Tests the various algorithms that come with this graph.
**/


#include "../../UndirectedGraph/uGraph.h"
#include <gtest/gtest.h>




//////////////////////////////////////
////////	Vertex Testing    ////////
// - These tests involve the inserting and deleting of vertices into our graph data structure.
TEST(VerticesTest, empty_Graph) { 
	uGraph<int> graph;

    ASSERT_EQ(0, graph.getNumVertices());
}

TEST(VerticesTest, insert_one_by_one) { 
uGraph<int> graph;
    int numVertices = rand()%800+2;

    std::vector<int> input_vec;
    for(int i = 1; i <= numVertices; i++)
        graph.insertVertex(i);

    ASSERT_EQ(numVertices, graph.getNumVertices());
}

TEST(VerticesTest, insert_all_at_once) { 
uGraph<int> graph;
    int numVertices = rand()%800+2;

    std::vector<int> input_vec;
    for(int i = 1; i <= numVertices; i++)
        input_vec.push_back(i);

    graph.insertVertices(input_vec);

    ASSERT_EQ(numVertices, graph.getNumVertices());
}

TEST(VerticesTest, test_no_duplicates) { 
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

TEST(VerticesTest, delete_test) { 
uGraph<int> graph;
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




//////////////////////////////////////
////////	Edge Testing    //////////

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
}


TEST(EdgesTest, insert_multiple) { 
	uGraph<int> graph;
	graph.insertVertex(1);
	graph.insertVertex(2);

	ASSERT_FALSE(!graph.insertEdge(1, 2)); // ok
	ASSERT_FALSE(graph.insertEdge(1, 2)); // duplicate

}


TEST(EdgesTest, insert_multiple2) { 
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

	graph.insertEdge(1, 2); // ok
	graph.insertEdge(1, 3); // ok
	graph.insertEdge(2, 3); // ok
	graph.insertEdge(3, 4); // ok
	graph.insertEdge(4, 1); // ok
	graph.insertEdge(6, 2); // ok
	ASSERT_FALSE(!graph.deleteEdge(1, 2)); // ok
	ASSERT_FALSE(!graph.deleteEdge(1, 3)); // ok
	graph.deleteEdge(2, 3); // ok
	graph.deleteEdge(3, 4); // ok
	graph.deleteEdge(4, 1); // ok
	graph.deleteEdge(6, 2); // ok


    // ASSERT_EQ(0, graph.getNumEdges());
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
	ASSERT_FALSE(graph.deleteEdge(2, 3)); // ok
	graph.deleteEdge(4, 1); // ok
	ASSERT_FALSE(graph.deleteEdge(4, 2)); // ok


    ASSERT_EQ(2, graph.getNumEdges());
}


TEST(EdgesTest, large_dense_graph) { 

	uGraph<int> graph;

 	int numVertices = 1000;

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
 
int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}