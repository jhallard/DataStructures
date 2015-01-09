/**
*   @Author   - John H Allard Jr.
*   @File     - MainTestSuite.cpp
*   @Data     - 11/19/2014
*   @Purpose  - This file contains all of the main tests for the undirected graph class. The testing framework is provided by Google via their 
*               Google Test suite for C++. Below you will see numerous groupings of different tests. These groupings of tests all test one aspect
*               of the graph in different ways, they are run individually then tallied together to ensure that entire subsystems work correctly.
*               The different sections of uGraph that will be tested are as follows :
*               1.) Vertex Testing    - Tests the insertion, deletion, and lookup of vertices in the graph. 
*               2.) Edge Testing      - Tests the insertion, deletion, and lookup of edges in the graph. 
*               3.) Algorithm/Speed Testing - Tests the various algorithms that come with this graph.
**/


#include "../UndirectedGraph/uGraph.h"
#include "../DirectedGraph/dGraph.h"
#include "../../GraphTraveler/uTraveler.hpp"
#include <gtest/gtest.h>
#include <sstream>
#include <chrono>
#include <ncurses.h>

double setweight(int & one, int & two) {
    return (rand()%177)/((rand()+1)%125+1)*(one*13.0+two*17.0)/(one+two+2.0)*27.0;
}

void analyzeGraphDijkstras(uGraph<int> * graph, int num_vertices, int iterations) { 

    bool testval = true;
    int total = 0, count1 = 0;
    double average = 0.0;
    for(int k = 1; k < iterations; k++) {

        int r,y; r = rand()%num_vertices+1; y = rand()%num_vertices+1;
        uTraveler<int> * trav = new uTraveler<int>();
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


TEST(Dijkstras, MinTreeSearch) {
    
    uGraph<int> * graph = new uGraph<int>();
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

    uTraveler<int> * trav = new uTraveler<int>();
    graph->minimumSpanningTree(trav);

    graph = &trav->graph;

    analyzeGraphDijkstras(graph, num_vertices, iterations);

}







TEST(Dijkstras, dense_graph_test) {
    int num_vertices = 2500;
    srand(time(0));
    int iterations = 5;

    uGraph<int> graph;

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

    std::vector<uGraph<int> > graphs(subGraphs);

    std::vector<int> subgraph_center;

    std::cout << "Creating " << subGraphs << " Subgraphs with " << vertices_per_subgraph << " vertices each...  \n";
    for(int i = 0; i < subGraphs; i++) {
        for(int j = i*vertices_per_subgraph+1; j <= (i+1)*vertices_per_subgraph; j++) {
            graphs[i].insertVertex(j);
        }
        subgraph_center.push_back(i*vertices_per_subgraph+1);
    }
    std::cout << "Finished \n";


    uGraph<int> final_graph;
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

    std::vector<uGraph<int> > graphs(subGraphs);

    std::vector<int> subgraph_center;

    std::cout << "Creating " << subGraphs << " Subgraphs with " << vertices_per_subgraph << " vertices each...  \n";
    for(int i = 0; i < subGraphs; i++) {
        for(int j = i*vertices_per_subgraph+1; j <= (i+1)*vertices_per_subgraph; j++) {
            graphs[i].insertVertex(j);
        }
        subgraph_center.push_back(i*vertices_per_subgraph+1);
    }
    std::cout << "Finished \n";

    uGraph<int> final_graph;
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





 
int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}