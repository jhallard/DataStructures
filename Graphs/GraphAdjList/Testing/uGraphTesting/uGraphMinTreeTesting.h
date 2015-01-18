#include "../../UndirectedGraph/uGraph.h"
#include "../../DirectedGraph/dGraph.h"
#include "../../../GraphTraveler/uTraveler.hpp"
#include <gtest/gtest.h>
#include <sstream>
#include <chrono>
#include <ncurses.h>


double setweight1(int & one, int & two) {
    return 2.0;//(rand()%177)/((rand()+2)%125+1)*(one*13.0+two*17.0)/(one+two+2.0)*27.0;
}

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

    int numVertices = 2000;

    std::vector<int> input_vec;

    for(int i = 1; i <= numVertices; i++) {
        input_vec.push_back(i);
    }

    graph.insertVertices(input_vec);

    double (*fptr)(int &, int &);
    fptr = setweight1;
    graph.makeGraphDense(fptr);


    uTraveler<int> * trav = new uTraveler<int>();

    auto start = std::chrono::high_resolution_clock::now();
    ASSERT_EQ(true, graph.minimumSpanningTree(trav));
    auto elapsed = std::chrono::high_resolution_clock::now() - start;   
    long long m = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count();
    std::cout << "MinSpanTree Time : " << m << "\n";
    std::cout << "Vertices : " << graph.getNumVertices() << " -- Edges : " << graph.getNumEdges() << "\n";

    ASSERT_EQ(trav->graph.getNumVertices(), numVertices);
    ASSERT_EQ(trav->graph.getNumEdges(), numVertices-1);
    ASSERT_EQ(true, trav->graph.isConnected());

    std::cout << "Min Tree Vertices : " << trav->graph.getNumVertices() << " -- Min Tree Edges : " << trav->graph.getNumEdges() << "\n";


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