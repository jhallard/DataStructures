#include "../../../DirectedGraph/dGraph.h"
#include "../../../GraphGen/dGraphGen.h"
#include "../../../../GraphTraveler/dTraveler.hpp"
#include <gtest/gtest.h>
#include <sstream>
#include <chrono>


void analyzeGraphDijkstras(dGraph<int> * graph, int num_vertices, int iterations) { 

    bool testval = true;
    int total = 0, count = 0;
    double average = 0.0;
    for(int k = 1; k <= iterations; k++) {

        int r,y; r = rand()%num_vertices+1; y = rand()%num_vertices+1;
        dTraveler<int> * trav = new dTraveler<int>();
        auto start = std::chrono::high_resolution_clock::now();
        try {
            if(!graph->dijkstrasShortestPath(r, y, trav)) {
                std::cout <<info << " [" << k << "/" << iterations << "] " << "Path Not Found : " << r << " -> " << y << "\n";
                testval = false;
                total++;
                graph->printGraph();
            }
        } catch (std::exception) {
            std::cout << info << "Exception Caught : \n";
            std::cout << info << " [" << k << "/" << iterations << "] " << "Path Not Found : " << r << " -> " << y << "\n";
        }
        auto elapsed = std::chrono::high_resolution_clock::now() - start;   
        long long m = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count();
        average += m;
        count++;

        delete(trav);
    }

    average = average/(count);
    std::cout << info << "Analysis : ___________________\n";
    std::cout << info << "Graph Description : #Vertices = " << graph->getNumVertices() << "  #Edges = " << graph->getNumEdges() << "\n";
    std::cout << info << "Wrong Paths :" << total << "/" << iterations << "\n";
    std::cout << info << "Average RunTime : " << average << "\n";
    ASSERT_EQ(true, testval);

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

    std::cout << info << "Making " << num_vertices << " vertices dense ..";
    graph.makeGraphDense(fptr);
    std::cout << "...finished \n";

    analyzeGraphDijkstras(&graph, num_vertices, iterations);

}







TEST(Dijkstras, large_test_union_1) {
    int num_vertices = 1600;
    int vert_per_subgraph = 10;
    int rand_edges = 200000;
    int iterations = 20;

    dGraph<int> graph;

    ASSERT_EQ(true, createGraphUnion(num_vertices, vert_per_subgraph, rand_edges, graph));

    analyzeGraphDijkstras(&graph, num_vertices, iterations);
}



TEST(Dijkstras, large_test_union_2) {

    int num_vertices = 4050;
    int vert_per_subgraph = 15;
    int rand_edges = 500000;
    int iterations = 10;

    dGraph<int> graph;

    ASSERT_EQ(true, createGraphUnion(num_vertices, vert_per_subgraph, rand_edges, graph));

    analyzeGraphDijkstras(&graph, num_vertices, iterations);

}



TEST(Dijkstras, large_test_union_3) {

    int num_vertices = 20000;
    int vert_per_subgraph = 5;
    int rand_edges = 500000;
    int iterations = 5;

    dGraph<int> graph;

    ASSERT_EQ(true, createGraphUnion(num_vertices, vert_per_subgraph, rand_edges, graph));

    analyzeGraphDijkstras(&graph, num_vertices, iterations);
}


TEST(Dijkstras, large_test_union_4) {

    int num_vertices = 120000;
    int vert_per_subgraph = 3;
    int rand_edges = 10000000;
    int iterations = 2;

    dGraph<int> graph;

    ASSERT_EQ(true, createGraphUnion(num_vertices, vert_per_subgraph, rand_edges, graph));

    analyzeGraphDijkstras(&graph, num_vertices, iterations);
}
