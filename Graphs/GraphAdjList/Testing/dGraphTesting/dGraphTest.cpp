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
}

TEST(VerticesTest, insert_all_at_once) { 
dGraph<int> graph;
    int numVertices = rand()%800+2;

    std::vector<int> input_vec;
    for(int i = 1; i <= numVertices; i++)
        input_vec.push_back(i);

    graph.insertVertices(input_vec);

    ASSERT_EQ(numVertices, graph.getNumVertices());
}



TEST(VerticesTest, large_insert_delete) {
    dGraph<int> graph;
    std::vector<int> vec;
    std::unordered_map<int, bool> m;

    for(int i = 0; i < 4000; i++) {
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




//////////////////////////////////////
////////    Edge Testing    //////////

// - These tests involve the inserting and deleting of edges into our graph data structure.
TEST(EdgesTest, empty_graph) { 
    dGraph<int> graph;

    ASSERT_EQ(0, graph.getNumEdges());
}


TEST(EdgesTest, insert_few) { 
    dGraph<int> graph;

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
    dGraph<int> graph;
    graph.insertVertex(1);
    graph.insertVertex(2);

    ASSERT_FALSE(!graph.insertEdge(1, 2)); // ok
    ASSERT_FALSE(graph.insertEdge(1, 2)); // duplicate

}


TEST(EdgesTest, insert_multiple2) { 
    dGraph<int> graph;

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
    dGraph<int> graph;

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
    dGraph<int> graph;

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

    dGraph<int> graph;

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
dGraph<int> graph;

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
    for(int i = 0; i < graph.getNumVertices(); i++) {

        std::vector< std::pair<int, double> > edges = graph.getAdjVertices(i);
        std::unordered_map<int, bool> themap;

        for(int j = 0; j < edges.size(); j++) {
            ASSERT_FALSE(themap.find(j) != themap.end());
            themap.insert(std::pair<int, bool>(j, true));
        }
    }
}


TEST(EdgesTest, adj_vertices) { 
    dGraph<int> graph;

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
    graph.insertEdge(1, 5); // ok

    std::vector< std::pair<int, double> > edges = graph.getAdjVertices(1);

    ASSERT_EQ(3, edges.size());
    // Make sure the correct 3 edges are in this adj list
    ASSERT_EQ(true, (edges[0].first == 2 || edges[0].first == 3 || edges[0].first == 5));
    ASSERT_EQ(true, (edges[1].first == 2 || edges[1].first == 3 || edges[1].first == 5));
    ASSERT_EQ(true, (edges[2].first == 2 || edges[2].first == 3 || edges[2].first == 5));

}


TEST(EdgesTest, vertex_and_edge_deletion) { 
    dGraph<int> graph;

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

    dGraph<int> graph;
    graph.insertVertex(1);
    graph.insertVertex(2);
    graph.insertVertex(3);
    graph.insertVertex(4);
    graph.insertVertex(5);
    graph.insertVertex(6);

    graph.insertEdge(1, 2, 1.1);
    graph.insertEdge(1, 3, 1.1);
    graph.insertEdge(1, 4, 1.1);
    graph.insertEdge(1, 5, 1.1);
    graph.insertEdge(1, 6, 1.1);
    graph.insertEdge(2, 3, 2.4);
    graph.insertEdge(2, 1, 2.4);
    graph.insertEdge(2, 5, 2.4);
    graph.insertEdge(2, 6, 2.4);
    graph.insertEdge(3, 4, 2.1);
    graph.insertEdge(3, 2, 3.1);
    graph.insertEdge(3, 6, 5.1);
    graph.insertEdge(4, 5, 5.1);
    graph.insertEdge(4, 2, 5.1);
    graph.insertEdge(5, 6, 5.15);
    graph.insertEdge(5, 1, 5.15);
    graph.insertEdge(6, 1, 6.15);
    graph.insertEdge(6, 2, 6.15);
    graph.insertEdge(4, 1, 6.15);
    graph.insertEdge(4, 3, 6.15);
    graph.insertEdge(5, 3, 6.15);
    graph.insertEdge(3, 1, 0.15);


    ASSERT_EQ(true, graph.isConnected());

    dGraph<int> * newGraph = graph.minimumSpanningTree();


    // newGraph->printGraph();


    delete(newGraph);
}

TEST(MinTreeTests, simple_test2) {

    dGraph<int> graph;
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
    graph.insertEdge(5, 1, 5);
    graph.insertEdge(5, 2, 6);
    graph.insertEdge(5, 3, 4);
    graph.insertEdge(4, 1, 6);
    graph.insertEdge(4, 3, 2);
    graph.insertEdge(4, 0, 4);
    graph.insertEdge(1, 0, 6);
    graph.insertEdge(3, 0, 2);
    graph.insertEdge(5, 0, 4);
    graph.insertEdge(0, 4, 6);
    graph.insertEdge(1, 5, 2);

    graph.printGraph();



    dGraph<int> * newGraph = graph.minimumSpanningTree();


    // // newGraph->printGraph();

    // ASSERT_EQ(newGraph->getNumVertices(), 6);
    // ASSERT_EQ(newGraph->getNumEdges(), 5);
    // ASSERT_EQ(true, newGraph->isConnected());
    // ASSERT_EQ(1, newGraph->getAdjVertices(1).size());
    // ASSERT_EQ(2, newGraph->getAdjVertices(2).size());
    // ASSERT_EQ(0, newGraph->getAdjVertices(3).size());
    // ASSERT_EQ(0, newGraph->getAdjVertices(4).size());
    // ASSERT_EQ(0, newGraph->getAdjVertices(5).size());
    // ASSERT_EQ(2, newGraph->getAdjVertices(0).size());


    delete(newGraph);
}



TEST(MinTreeTests, larger_test) {


    dGraph<int> graph;

    int numVertices = 400;

    std::vector<int> input_vec;

    for(int i = 1; i <= numVertices; i++) {
        input_vec.push_back(i);
    }

    graph.insertVertices(input_vec);
    graph.makeGraphDense();


    ASSERT_EQ(true, graph.isConnected());
    dGraph<int> * newGraph = graph.minimumSpanningTree();

    ASSERT_EQ(newGraph->getNumVertices(), numVertices);
    ASSERT_EQ(newGraph->getNumEdges(), numVertices-1);
    

    // newGraph->printGraph();

    delete(newGraph);
}



TEST(MinTreeTests, non_connected_error) {

    dGraph<int> graph;
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

    bool shouldBeFalse = true;
    try {
        dGraph<int> * newGraph = graph.minimumSpanningTree();
        delete(newGraph);
    } 
    catch(std::logic_error e) {
        shouldBeFalse = false;
    }

    ASSERT_FALSE(shouldBeFalse);

}

TEST(Dijkstras, simple_test2) {

    dGraph<int> graph;
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
    graph.insertEdge(5, 3, 2);

    std::pair<std::vector<int>,double> the_pair = graph.dijkstrasComputePath(0, 4);
    auto temp = the_pair.first;
    auto dis = the_pair.second;
    bool testval = true;
    // std::cout << "# Edges : " << graph.getNumEdges() << "\n";
    if(!temp.size()) {
        // std::cout << "Path Not Found : " << r << " -> " << y << "\n";
        // std::cout << "Iteration : " << k << "/" <<numVertices/10 <<"\n\n";
        testval = false;
    }
    else {
        ASSERT_EQ(true, temp.size() > 0);
        ASSERT_EQ(0, temp[0]);
        ASSERT_EQ(4, temp[temp.size()-1]);
    }

    the_pair = graph.dijkstrasComputePath(4, 3);
    temp = the_pair.first;
    dis = the_pair.second;
    testval = true;
    if(!temp.size()) {
        testval = false;
    }
    else {
        ASSERT_EQ(true, temp.size() > 0);
        ASSERT_EQ(4, temp[0]);
        ASSERT_EQ(3, temp[temp.size()-1]);
    }

    ASSERT_EQ(true, testval);
}

TEST(Dijkstras, simple_test) {
    dGraph<int> graph;

    srand(time(0));
    int numVertices = 40;
    int minEdges = 30;
    int maxEdges = 33;

    std::vector<int> input_vec;

    for(int i = 1; i <= numVertices; i++)
        input_vec.push_back(i);

    graph.insertVertices(input_vec);

    while(!graph.isConnected()) {

        for(int i = 1; i <= numVertices; i++) {
            graph.deleteVertex(i);
            graph.insertVertex(i);
        }

        for(int i = 1; i <= numVertices; i++) {
            int loop = rand()*rand()*rand() % (maxEdges-minEdges) + minEdges;
            double weight = (double)(rand() % 477 + 20)/100;
            if(weight <= 0)
                weight *= -1;
            // std::cout << weight << std::endl;
            for(int j = 0; j < loop; j++) {

                int r = rand() % numVertices + 1;
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
    for(int k = 1; k < numVertices/2; k++) {
        
        int r,y; r = rand()%numVertices+1; y = rand()%numVertices+1;
        std::pair<std::vector<int>,double> the_pair = graph.dijkstrasComputePath(r, y);
        auto temp = the_pair.first;
        auto dis = the_pair.second;

        // std::cout << "# Edges : " << graph.getNumEdges() << "\n";
        if(!temp.size()) {
            std::cout << "Path Not Found : " << r << " -> " << y << "\n";
            // std::cout << "Iteration : " << k << "/" <<numVertices/10 <<"\n\n";
            testval = false;
        }
        else {
            ASSERT_EQ(true, temp.size() > 0);
            ASSERT_EQ(r, temp[0]);
            ASSERT_EQ(y, temp[temp.size()-1]);
        }
    }

    ASSERT_EQ(true, testval);

}


/////////////////////////////////////////////////
////////////////    SPEED TESTS /////////////////
/////////////////////////////////////////////////

TEST(SpeedTests, large_bfs_dfs_test) { 

    dGraph<int> graph;

    int numVertices = 2000;
    int minEdges = 40;
    int maxEdges = 200;

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
        graph.breadthFirst(r, f);
        auto elapsed = std::chrono::high_resolution_clock::now() - start;   
        long long m = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count();

        std::stringstream ss;
        // std::cout << "\n BFS TEST : " << i <<  " : " << m  << "\n" << std::endl;
        ASSERT_EQ(true, m < 200 );

        start = std::chrono::high_resolution_clock::now();
        graph.depthFirst(r, f);
        elapsed = std::chrono::high_resolution_clock::now() - start;    
        m = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count();


        // std::cout << "\n DFS TEST : " << i <<  " : " << m  << "\n" << std::endl;
        ASSERT_EQ(true, m < 200);
    }       

}



 
int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}