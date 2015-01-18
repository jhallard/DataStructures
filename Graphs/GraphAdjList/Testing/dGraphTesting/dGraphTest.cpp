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
#include <gtest/gtest.h>
#include <sstream>
#include <chrono>


double setweight(int & one, int & two) {
    return (rand()%177)/((rand()+1)%125+1)*(one*13.0+two*17.0)/(one+two+2.0)*27.0;
}


void analyzeGraphDijkstras(dGraph<int> * graph, int num_vertices, int iterations) { 

    bool testval = true;
    int total = 0, count1 = 0;
    double average = 0.0;
    for(int k = 1; k < iterations; k++) {

        int r,y; r = rand()%num_vertices+1; y = rand()%num_vertices+1;
        dTraveler<int> * trav = new dTraveler<int>();
        auto start = std::chrono::high_resolution_clock::now();
        if(!graph->dijkstrasShortestPath(r, y, trav)) {
            std::cout << " [" << k << "/" << iterations << "] " << "Path Not Found : " << r << " -> " << y << "\n";
            testval = false;
            total++;
            graph->printGraph();
        }
        auto elapsed = std::chrono::high_resolution_clock::now() - start;   
        long long m = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count();
        average += m;
        count1++;

        delete(trav);
    }

    average = average/(count1);
    std::cout << "\n\nAnalysis : ___________________\n";
    std::cout << "Graph Description : #Vertices = " << graph->getNumVertices() << "  #Edges = " << graph->getNumEdges() << "\n";
    std::cout << "Wrong Paths :" << total << "/" << iterations << " \n";
    std::cout << "Average RunTime : " << average << "\n\n\n";
    ASSERT_EQ(true, testval);

}


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


TEST(EdgesTest, insert_multiple_larger) { 
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

    auto edges = graph.getIncidentEdges(1);

    ASSERT_EQ(3, edges.size());
    // Make sure the correct 3 edges are in this adj list
    ASSERT_EQ(true, (edges[0].getTarget()->getData() == 2 || edges[0].getTarget()->getData() == 3 || edges[0].getTarget()->getData() == 5));
    ASSERT_EQ(true, (edges[1].getTarget()->getData() == 2 || edges[1].getTarget()->getData() == 3 || edges[1].getTarget()->getData() == 5));
    ASSERT_EQ(true, (edges[2].getTarget()->getData() == 2 || edges[2].getTarget()->getData() == 3 || edges[2].getTarget()->getData() == 5));

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

TEST(UnionTests, simple_test) {
    dGraph<int> graph;
    graph.insertVertex(1);
    graph.insertVertex(2);
    graph.insertVertex(3);
    graph.insertVertex(4);
    graph.insertVertex(5);
    graph.insertVertex(6);

    dGraph<int> graph2;
    graph2.insertVertex(10);
    graph2.insertVertex(20);
    graph2.insertVertex(30);
    graph2.insertVertex(40);
    graph2.insertVertex(50);
    graph2.insertVertex(60);

    graph.getUnion(graph2);

    ASSERT_EQ(12, graph.getNumVertices());
    ASSERT_EQ(0, graph.getNumEdges());

}

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


    ASSERT_EQ(true, graph.minimumSpanningTree());

    // newGraph->printGraph();


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

    // graph.printGraph();



    ASSERT_EQ(true, graph.minimumSpanningTree());


    // // newGraph->printGraph();

    // ASSERT_EQ(newGraph->getNumVertices(), 6);
    // ASSERT_EQ(newGraph->getNumEdges(), 5);
    // ASSERT_EQ(true, newGraph->isConnected());
    // ASSERT_EQ(1, newGraph->getIncidentEdges(1).size());
    // ASSERT_EQ(2, newGraph->getIncidentEdges(2).size());
    // ASSERT_EQ(0, newGraph->getIncidentEdges(3).size());
    // ASSERT_EQ(0, newGraph->getIncidentEdges(4).size());
    // ASSERT_EQ(0, newGraph->getIncidentEdges(5).size());
    // ASSERT_EQ(2, newGraph->getIncidentEdges(0).size());

}



TEST(MinTreeTests, larger_test) {


    dGraph<int> graph;

    int numVertices = 1500;

    std::vector<int> input_vec;

    for(int i = 1; i <= numVertices; i++) {
        input_vec.push_back(i);
    }

    graph.insertVertices(input_vec);
    double (*fptr)(int &, int &);
    fptr = setweight;
    graph.makeGraphDense(fptr);


    ASSERT_EQ(true, graph.isConnected());

    dTraveler<int> * trav = new dTraveler<int>();

    auto start = std::chrono::high_resolution_clock::now();
    ASSERT_EQ(true, graph.minimumSpanningTree(trav));
    auto elapsed = std::chrono::high_resolution_clock::now() - start;   
    long long m = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count();
    std::cout << "MinSpanTree Time : " << m << "\n";
    std::cout << "Vertices : " << graph.getNumVertices() << " -- Edges : " << graph.getNumEdges() << "\n";

    ASSERT_EQ(trav->graph.getNumVertices(), numVertices);
    ASSERT_EQ(trav->graph.getNumEdges(), numVertices-1);

    std::cout << "Min Tree Vertices : " << trav->graph.getNumVertices() << " -- Min Tree Edges : " << trav->graph.getNumEdges() << "\n";

    
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


    ASSERT_FALSE(graph.minimumSpanningTree());

}

TEST(Bipartite, simple_positive_test) {

    dGraph<int> graph;

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

    dGraph<int> graph;

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
    graph.insertEdge(1, 4);
    graph.insertEdge(2, 5);

    ASSERT_FALSE(graph.isBipartite());

}

TEST(Bipartition, simple_positive_test) {

    dGraph<int> graph;

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

TEST(Dijkstras, MinTreeSearch) {
    
    dGraph<int> * graph = new dGraph<int>();
    srand(time(0));
    int num_vertices = 1000;
    double (*fptr)(int &, int &);
    fptr = setweight;
    int iterations = num_vertices;

    std::vector<int> input_vec;

    for(int i = 1; i <= num_vertices; i++)
        input_vec.push_back(i);

    graph->insertVertices(input_vec);

    graph->makeGraphDense(fptr);

    dTraveler<int> * trav = new dTraveler<int>();
    graph->minimumSpanningTree(trav);


    *graph = trav->graph;

    trav->graph.reverse();

    graph->getUnion(trav->graph);

    analyzeGraphDijkstras(graph, num_vertices, iterations);

}







TEST(Dijkstras, dense_graph_test) {
    int num_vertices = 2500;
    srand(time(0));
    int iterations = 5;

    dGraph<int> graph;

    for(int i = 0; i < num_vertices; i++) {
        graph.insertVertex(i);
    }

    double (*fptr)(int &, int &);
    fptr = setweight;

    std::cout << "Making " << num_vertices << " vertices dense ..\n";
    graph.makeGraphDense(fptr);
    std::cout << "...finished \n";

    analyzeGraphDijkstras(&graph, num_vertices, iterations);

}










TEST(Dijkstras, large_test_union) {

    srand(time(0));
    int num_vertices = 1600;
    int vertices_per_subgraph = 10;
    int subGraphs = num_vertices/vertices_per_subgraph;
    int rand_edges = 10000;
    int iterations = 20;

    std::vector<dGraph<int> > graphs(subGraphs);

    std::vector<int> subgraph_center;

    std::cout << "Creating " << subGraphs << " Subgraphs with " << vertices_per_subgraph << " vertices each...  \n";
    for(int i = 0; i < subGraphs; i++) {
        for(int j = i*vertices_per_subgraph+1; j <= (i+1)*vertices_per_subgraph; j++) {
            graphs[i].insertVertex(j);
        }
        subgraph_center.push_back(i*vertices_per_subgraph+1);
    }
    std::cout << "Finished \n";


    dGraph<int> final_graph;
    double (*fptr)(int &, int &);
    fptr = setweight;

    std::cout << "Concatinating " << subGraphs << " Subgraphs...  "; int count = 0;
    for(auto graph : graphs) {
        // std::cout << "Making Dense \n";
        graph.makeGraphDense(fptr);
        // std::cout << "Getting the Union " << count++ << " \n";
        final_graph.getUnion(graph);
    }
    std::cout << "Finished \n";


    std::cout << "Connecting subGraph Centers...  \n";
    for(int i = 0; i < subGraphs-1; i++) {
        double weight = (double)(rand() % 477 + 2)/100.0;
        weight += (rand()%27*i)/3.534;
        final_graph.insertEdge(subgraph_center[i], subgraph_center[i+1], weight*((rand()%100)/50.0));
        final_graph.insertEdge(subgraph_center[i+1], subgraph_center[i], weight*((rand()%100)/50.0));
    }
    std::cout << "Finished \n";


    final_graph.insertEdge(subgraph_center[0], subgraph_center[subGraphs-1], 0.45);
    final_graph.insertEdge(subgraph_center[subGraphs-1], subgraph_center[0], 2.467);

    std::cout << "Adding Random Edges...  \n";
    for(int i = 0; i < rand_edges; i++) {
        int l = (rand() % num_vertices + 1);
        int r = (rand() % num_vertices + 1);
        double weight = (double)(rand() % 477 + 20)/100.0;

        if(r == l) {
            i--;
            continue;
        }

        final_graph.insertEdge(l, r, weight);

        if(rand() % 4) {
            final_graph.insertEdge(r, l, 2*weight+1.34);
        }

    } 
    std::cout << "Finished \n";


    if(!final_graph.isConnected()) {
        std::cout << "non-connected error!\n";
        return;
    }

    analyzeGraphDijkstras(&final_graph, num_vertices, iterations);

}






TEST(Dijkstras, large_test) {

    srand(time(0));
    int num_vertices = 4000;
    int minEdges = 40;
    int maxEdges = 100;
    int vertices_per_subgraph = 15;
    int subGraphs = num_vertices/vertices_per_subgraph;
    int rand_edges = 50000;
    int iterations = 10;

    std::vector<dGraph<int> > graphs(subGraphs);

    std::vector<int> subgraph_center;

    std::cout << "Creating " << subGraphs << " Subgraphs with " << vertices_per_subgraph << " vertices each...  \n";
    for(int i = 0; i < subGraphs; i++) {
        for(int j = i*vertices_per_subgraph+1; j <= (i+1)*vertices_per_subgraph; j++) {
            graphs[i].insertVertex(j);
        }
        subgraph_center.push_back(i*vertices_per_subgraph+1);
    }
    std::cout << "Finished \n";

    dGraph<int> final_graph;
    double (*fptr)(int &, int &);
    fptr = setweight;

    std::cout << "Concatinating " << subGraphs << " Subgraphs...  \n"; int count = 0;
    for(auto graph : graphs) {
        // std::cout << "Making Dense \n";
        graph.makeGraphDense(fptr);
        // std::cout << "Getting the Union " << count++ << " \n";
        final_graph.getUnion(graph);
    }
    std::cout << "Finished \n";


    std::cout << "Connecting subGraph Centers...  \n";
    for(int i = 0; i < subGraphs-1; i++) {
        double weight = (double)(rand() % 477 + 2)/100.0;
        weight += (rand()%27*i)/3.534;
        final_graph.insertEdge(subgraph_center[i], subgraph_center[i+1], weight*((rand()%100)/50.0));
        final_graph.insertEdge(subgraph_center[i+1], subgraph_center[i], weight*((rand()%100)/50.0));
    }
    std::cout << "Finished \n";


    final_graph.insertEdge(subgraph_center[0], subgraph_center[subGraphs-1], 0.45);
    final_graph.insertEdge(subgraph_center[subGraphs-1], subgraph_center[0], 2.467);

    std::cout << "Adding Random Edges...  \n";
    for(int i = 0; i < rand_edges; i++) {
        int l = (rand() % num_vertices + 1);
        int r = (rand() % num_vertices + 1);
        double weight = (double)(rand() % 477 + 20)/100.0;

        if(r == l) {
            i--;
            continue;
        }

        final_graph.insertEdge(l, r, weight);

        if(rand() % 4) {
            final_graph.insertEdge(r, l, 2*weight);
        }

    } 
    std::cout << "Finished \n";


    if(!final_graph.isConnected()) {
        std::cout << "non-connected error!\n";
        return;
    }

    analyzeGraphDijkstras(&final_graph, num_vertices, iterations);

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
        graph.breadthFirst(r);//, f);
        auto elapsed = std::chrono::high_resolution_clock::now() - start;   
        long long m = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count();

        std::stringstream ss;
        // std::cout << "\n BFS TEST : " << i <<  " : " << m  << "\n" << std::endl;
        ASSERT_EQ(true, m < 200 );

        start = std::chrono::high_resolution_clock::now();
        graph.depthFirst(r);//, f);
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