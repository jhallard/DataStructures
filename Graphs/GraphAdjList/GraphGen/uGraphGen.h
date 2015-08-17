#include "../UndirectedGraph/uGraph.h"
#include "../../GraphTraveler/uTraveler.hpp"
#include <gtest/gtest.h>
#include <sstream>
#include <chrono>
#include <ncurses.h>


double setweight(int & one, int & two) {
    return (rand()%177+rand()*two+3*one)/((rand()+1)%125+1)*(one*13.0+two*17.0)/(one+two+2.0)*27.0;
}



bool createGraphUnion(int num_vertices, int vert_per_subgraph, int rand_edges, uGraph<int> & final_graph) {
    srand(time(0));
    int minEdges = 40;
    int maxEdges = 100;
    int subGraphs = num_vertices/vert_per_subgraph;
    int iterations = 2;

    std::vector<uGraph<int> > graphs(subGraphs);

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

