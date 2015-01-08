/**
*   @Author   - John H Allard Jr.
*   @File     - MainTestSuite.cpp
*   @Data     - 11/19/2014
*   @Purpose  - This file contains all of the main tests for the undirected graph class. The testing framework is provided by Google via their 
*				Google Test suite for C++. Below you will see numerous groupings of different tests. These groupings of tests all test one aspect
*				of the graph in different ways, they are run individually then tallied together to ensure that entire subsystems work correctly.
*				The different sections of uGraph that will be tested are as follows :
*				1.) Vertex Testing    - Tests the insertion, deletion, and lookup of vertices in the graph. 
*				2.) Edge Testing      - Tests the insertion, deletion, and lookup of edges in the graph. 
*				3.) Algorithm/Speed Testing - Tests the various algorithms that come with this graph.
**/


#include "../../UndirectedGraph/uGraph.h"
#include "../../DirectedGraph/dGraph.h"
#include "../../../GraphTraveler/uTraveler.hpp"
#include <gtest/gtest.h>
#include <sstream>
#include <chrono>


double setweight(int & one, int & two) {
    return (one*13.0+two*17.0)/(one+two+2.0)*27.0;
}

//////////////////////////////////////
////////	Vertex Testing    ////////
// - These tests involve the inserting and deleting of vertices into our graph data structure.
TEST(VerticesTest, empty_graph) { 
	uGraph<int> graph;

    ASSERT_EQ(0, graph.getNumVertices());
    ASSERT_EQ(false, graph.deleteVertex(1));
    ASSERT_EQ(false, graph.deleteEdge(1, 2));
}

TEST(VerticesTest, insert_one_by_one) { 
uGraph<int> graph;
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
uGraph<int> graph;
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
	uGraph<int> graph;
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
    int numVertices = rand()%800+200;

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


////////////////////////////////////////////////////
///////////////// ALGORITHM TESTS //////////////////
////////////////////////////////////////////////////

TEST(MinTreeTests, simple_test) {

	uGraph<int> graph;
    graph.insertVertex(1);
    graph.insertVertex(2);
    graph.insertVertex(3);
    graph.insertVertex(4);
    graph.insertVertex(5);
    graph.insertVertex(6);

    graph.insertEdge(1, 2, 0.1);
    graph.insertEdge(1, 3, 0.1);
    graph.insertEdge(1, 4, 0.1);
    graph.insertEdge(1, 5, 0.1);
    graph.insertEdge(1, 6, 0.1);
    graph.insertEdge(2, 3, 0.4);
    graph.insertEdge(2, 4, 0.4);
    graph.insertEdge(2, 5, 0.4);
    graph.insertEdge(2, 6, 0.4);
    graph.insertEdge(3, 4, 2.1);
    graph.insertEdge(3, 5, 3.1);
    graph.insertEdge(3, 6, 1.1);
    graph.insertEdge(4, 5, 3.1);
    graph.insertEdge(4, 6, 3.1);
    graph.insertEdge(5, 6, 0.15);


    uTraveler<int> * trav = new uTraveler<int>();
    ASSERT_EQ(true, graph.minimumSpanningTree(trav));

    ASSERT_EQ(trav->graph.getNumVertices(), 6);
    ASSERT_EQ(trav->graph.getNumEdges(), 5);
    ASSERT_EQ(true, trav->graph.isConnected());
    ASSERT_EQ(5, trav->graph.getIncidentEdges(1).size());
    ASSERT_EQ(1, trav->graph.getIncidentEdges(2).size());
    ASSERT_EQ(1, trav->graph.getIncidentEdges(3).size());
    ASSERT_EQ(1, trav->graph.getIncidentEdges(4).size());
    ASSERT_EQ(1, trav->graph.getIncidentEdges(5).size());
    ASSERT_EQ(1, trav->graph.getIncidentEdges(6).size());

    delete(trav);

}

TEST(MinTreetTests, simple_test2) {

	uGraph<int> graph;
	graph.insertVertex(0);
    graph.insertVertex(1);
    graph.insertVertex(2);
    graph.insertVertex(3);
    graph.insertVertex(4);
    graph.insertVertex(5);

    graph.insertEdge(0, 2, 1);
    graph.insertEdge(0, 3, 6);
    graph.insertEdge(0, 1, 3);
    graph.insertEdge(1, 2, 5);
    graph.insertEdge(1, 4, 3);
    graph.insertEdge(2, 3, 5);
    graph.insertEdge(2, 4, 6);
    graph.insertEdge(2, 5, 4);
    graph.insertEdge(4, 5, 6);
    graph.insertEdge(3, 5, 2);


    uTraveler<int> * trav = new uTraveler<int>();
    ASSERT_EQ(true, graph.minimumSpanningTree(trav));

    ASSERT_EQ(trav->graph.getNumVertices(), 6);
    ASSERT_EQ(trav->graph.getNumEdges(), 5);
    ASSERT_EQ(true, trav->graph.isConnected());
    ASSERT_EQ(2, trav->graph.getIncidentEdges(1).size());
    ASSERT_EQ(2, trav->graph.getIncidentEdges(2).size());
    ASSERT_EQ(1, trav->graph.getIncidentEdges(3).size());
    ASSERT_EQ(1, trav->graph.getIncidentEdges(4).size());
    ASSERT_EQ(2, trav->graph.getIncidentEdges(5).size());
    ASSERT_EQ(2, trav->graph.getIncidentEdges(0).size());


    delete(trav);

}

TEST(MinTreeTests, larger_test) {


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
    		if(!graph.insertEdge(i, j))
                std::cout << "Fail!\n;";
    		count++;
    	}
    }


    uTraveler<int> * trav = new uTraveler<int>();
    ASSERT_EQ(true, graph.minimumSpanningTree(trav));
    ASSERT_EQ(trav->graph.getNumVertices(), numVertices);
    ASSERT_EQ(trav->graph.getNumEdges(), numVertices-1);
    ASSERT_EQ(true, trav->graph.isConnected());

    // trav->graph.printGraph();

    delete(trav);


}

TEST(MinTreeTests, non_connected_error) {

    uGraph<int> graph;
    graph.insertVertex(1);
    graph.insertVertex(2);
    graph.insertVertex(3);
    graph.insertVertex(4);
    graph.insertVertex(5);
    graph.insertVertex(6);
    graph.insertVertex(7);

    graph.insertEdge(1, 2, 0.1);
    graph.insertEdge(1, 3, 0.1);
    graph.insertEdge(1, 4, 0.1);
    graph.insertEdge(1, 5, 0.1);
    graph.insertEdge(2, 3, 0.4);
    graph.insertEdge(2, 4, 0.4);
    graph.insertEdge(2, 5, 0.4);
    graph.insertEdge(3, 4, 2.1);
    graph.insertEdge(3, 5, 3.1);
    graph.insertEdge(4, 5, 3.1);

    ASSERT_FALSE(graph.minimumSpanningTree());
}



TEST(Bipartite, simple_positive_test) {

    uGraph<int> graph;

    for(int i = 1; i < 6; i++)
        graph.insertVertex(i);

    graph.insertEdge(5, 4);
    graph.insertEdge(3, 5);
    graph.insertEdge(4, 1);
    graph.insertEdge(1, 3);
    graph.insertEdge(2, 4);
    graph.insertEdge(3, 2);

    ASSERT_EQ(true, graph.isBipartite());
}

TEST(Bipartite, simple_negative_test) {

    uGraph<int> graph;

    for(int i = 1; i < 6; i++)
        graph.insertVertex(i);

    graph.insertEdge(5, 4);
    graph.insertEdge(3, 5);
    graph.insertEdge(4, 1);
    graph.insertEdge(1, 3);
    graph.insertEdge(2, 4);
    graph.insertEdge(3, 2);
    graph.insertEdge(1, 2);
    graph.insertEdge(3, 4);
    graph.insertEdge(1, 5);
    graph.insertEdge(2, 5);

    ASSERT_FALSE(graph.isBipartite());
}

TEST(Bipartition, simple_positive_test) {

    uGraph<int> graph;

    for(int i = 1; i < 6; i++)
        graph.insertVertex(i);

    graph.insertEdge(5, 4);
    graph.insertEdge(3, 5);
    graph.insertEdge(4, 1);
    graph.insertEdge(1, 3);
    graph.insertEdge(2, 4);
    graph.insertEdge(3, 2);

    std::pair<std::vector<int>, std::vector<int> > * pair = new std::pair<std::vector<int>, std::vector<int> >();

    ASSERT_EQ(true, graph.getBipartition(pair));

    ASSERT_EQ(true, pair->first.size() == 3 || pair->first.size() == 2);
    ASSERT_EQ(true, pair->second.size() == 3 || pair->second.size() == 2);

}


TEST(Dijkstras, dense_graph_test) {

    int num_vertices = 350;
    srand(time(0));

    uGraph<int> graph;

    for(int i = 0; i < num_vertices; i++) {
        graph.insertVertex(i);
    }

    double (*fptr)(int &, int &);
    fptr = setweight;

    graph.makeGraphDense(fptr);

    for(int i = 0; i < num_vertices; i++) {
        int l = rand() % num_vertices;
        int r = rand() % num_vertices;

        if(r == l) {
            i--;
            continue;
        }

        ASSERT_EQ(true, graph.dijkstrasShortestPath(l, r));
    }

    std::cout << "Vert :" << graph.getNumVertices() << "  Edges : " << graph.getNumEdges() << "\n";
}

TEST(Dijkstras, large_test) {
    uGraph<int> graph;

    srand(time(0));
    int numVertices = 1000;
    int minEdges = 70;
    int maxEdges = 125;

    std::vector<int> input_vec;

    for(int i = 1; i <= numVertices; i++)
        input_vec.push_back(i);

    graph.insertVertices(input_vec);


    while(!graph.isConnected()) {
	    for(int i = 1; i < numVertices; i++) {

	        int loop = rand()*rand()*rand() % (maxEdges-minEdges) + minEdges;
	        double weight = (double)(rand() % 477 + 20)/10.0;
	        if(weight <= 0)
	        	weight *= -1;
	        // std::cout << weight << std::endl;
	        for(int j = 0; j < loop; j++) {

	            int r = rand() % numVertices + 1; r++;
                weight += (r*13+i*17)/(i*27+r*10.0);
	            if(r == i) {
	                j--;
	                continue;
	            }

	            if(!graph.insertEdge(i, r, weight))
	                j--;
	        }
	    }
	}	

    bool testval = true;
    int total = 0;
    for(int k = 1; k < numVertices/4; k++) {
    	int r,y; r = rand()%numVertices+1; y = rand()%numVertices+1;
        if(!(graph.containsVertex(r) & graph.containsVertex(y)))
            continue;

        uTraveler<int> * trav = new uTraveler<int>();
        if(!graph.dijkstrasShortestPath(r, y, trav)) {
            std::cout << " [" << k << "/" <<numVertices/4 << "] " << "Path Not Found : " << r << " -> " << y << "\n";
            testval = false;
            total++;
        }
          // else
          //   trav->graph.printGraph();

        delete(trav);
    }

    std::cout << total << "/" << numVertices/4 << " Wrong Paths \n";
    std::cout << "Vert :" << graph.getNumVertices() << "  Edges : " << graph.getNumEdges() << "\n";
    ASSERT_EQ(true, testval);

}




/////////////////////////////////////////////////
//////////////// 	SPEED TESTS /////////////////
/////////////////////////////////////////////////

TEST(SpeedTests, large_bfs_dfs_test) { 

	uGraph<int> graph;

    int numVertices = 2000;
    int minEdges = 80;
    int maxEdges = 300;

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

    auto f = [](int&) -> void { return; };

    int tries = (numVertices < 500)? 20 : 5;

    for(int i = 1; i <= tries; i++) {

    	int r = rand()%(numVertices-1)+1;

	    auto start = std::chrono::high_resolution_clock::now();
	    graph.breadthFirst(r);//, f);
		auto elapsed = std::chrono::high_resolution_clock::now() - start;	
		long long m = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count();

		std::stringstream ss;
		// std::cout << "\n BFS TEST : " << i <<  " : " << m  << "\n" << std::endl;
		ASSERT_EQ(true, m < 400 );

		start = std::chrono::high_resolution_clock::now();
	    graph.depthFirst(r);//, f);
		elapsed = std::chrono::high_resolution_clock::now() - start;	
		m = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count();


		// std::cout << "\n DFS TEST : " << i <<  " : " << m  << "\n" << std::endl;
		ASSERT_EQ(true, m < 400);
	}		

}



 
int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}