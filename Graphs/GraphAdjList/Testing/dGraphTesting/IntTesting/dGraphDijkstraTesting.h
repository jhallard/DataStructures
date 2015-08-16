#include "../../../DirectedGraph/dGraph.h"
#include "../../../../GraphTraveler/dTraveler.hpp"
#include <gtest/gtest.h>
#include <sstream>
#include <chrono>


double setweight(int & one, int & two) {
    return (rand()%177+rand()*two+3*one)/((rand()+1)%125+1)*(one*13.0+two*17.0)/(one+two+2.0)*27.0;
}


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
                std::cout << " [" << k << "/" << iterations << "] " << "Path Not Found : " << r << " -> " << y << "\n";
                testval = false;
                total++;
                graph->printGraph();
            }
        } catch (std::exception) {
            std::cout << "Exception Caught : \n";
            std::cout << " [" << k << "/" << iterations << "] " << "Path Not Found : " << r << " -> " << y << "\n";
        }
        auto elapsed = std::chrono::high_resolution_clock::now() - start;   
        long long m = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count();
        average += m;
        count++;

        delete(trav);
    }

    average = average/(count);
    std::cout << "\n\nAnalysis : ___________________\n";
    std::cout << "Graph Description : #Vertices = " << graph->getNumVertices() << "  #Edges = " << graph->getNumEdges() << "\n";
    std::cout << "Wrong Paths :" << total << "/" << iterations << " \n";
    std::cout << "Average RunTime : " << average << "\n\n\n";
    ASSERT_EQ(true, testval);

}

bool createGraphUnion(int num_vertices, int vert_per_subgraph, int rand_edges, dGraph<int> & final_graph) {
    srand(time(0));
    int minEdges = 40;
    int maxEdges = 100;
    int subGraphs = num_vertices/vert_per_subgraph;

    std::vector<dGraph<int> > graphs(subGraphs);

    std::vector<int> subgraph_center;

    std::cout << "Creating " << subGraphs << " Subgraphs with " << vert_per_subgraph << " vertices each...  \n";
    for(int i = 0; i < subGraphs; i++) {
        for(int j = i*vert_per_subgraph+1; j <= (i+1)*vert_per_subgraph; j++) {
            graphs[i].insertVertex(j);
        }
        subgraph_center.push_back(i*vert_per_subgraph+1);
    }
    std::cout << "Finished \n";

    double (*fptr)(int &, int &);
    fptr = setweight;

    std::cout << "Concatinating " << subGraphs << " Subgraphs...  \n"; int count = 0;
    for(auto graph : graphs) {
        graph.makeGraphDense(fptr);
        final_graph.getUnion(graph);
    }
    std::cout << "Finished \n";


    std::cout << "Connecting subGraph Centers...  \n";
    for(int i = 0; i < subGraphs-1; i++) {
        double weight = (double)(rand() % 477 + 2)/100.0;
        weight += (rand()%27*i)/3.534;
        final_graph.insertEdge(subgraph_center[i], subgraph_center[i+1], weight*((rand()%100+i)/50.0));
        final_graph.insertEdge(subgraph_center[i+1], subgraph_center[i], weight*((rand()%100+i)/50.0));
    }
    std::cout << "Finished \n";


    final_graph.insertEdge(subgraph_center[0], subgraph_center[subGraphs-1], 0.45);
    final_graph.insertEdge(subgraph_center[subGraphs-1], subgraph_center[0], 2.467);

    std::cout << "Adding Random Edges...  \n";
    for(int i = 0; i < rand_edges; i++) {
        int l = (rand()*i+17) % (num_vertices + 1);
        int r = (rand()*i*2+i*13) % (num_vertices + 1);
        double weight = (double)(rand()+i % 477 + 2*i)/100.0;

        if(r == l) {
            i--;
            continue;
        }

        final_graph.insertEdge(l, r, weight);

        final_graph.insertEdge(r, l, 2*weight);

    } 
    std::cout << "Finished \n";

    std::cout << "Checking for Connectivity...\n";
    if(!final_graph.isConnected()) {
        std::cout << "non-connected error!\n";
        return false;
    }
    std::cout << "Confirmed\n";

    return true;
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
    int iterations = 10;

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
