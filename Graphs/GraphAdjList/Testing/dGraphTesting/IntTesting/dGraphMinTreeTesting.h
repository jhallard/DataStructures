#include "../../../DirectedGraph/dGraph.h"
#include "../../../../GraphTraveler/dTraveler.hpp"
#include <gtest/gtest.h>
#include <sstream>
#include <chrono>


double setweight1(int & one, int & two) {
    return (rand()%177)/((rand()+1)%125+1)*(one*13.0+two*17.0)/(one+two+2.0)*27.0;
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

    //graph.makeGraphDense(3.1);

    graph.insertEdge(0, 2, 1.1);
    graph.insertEdge(0, 3, 6.25);
    graph.insertEdge(0, 1, 3.15);
    graph.insertEdge(1, 2, 5.241);
    graph.insertEdge(1, 4, 3.122);
    graph.insertEdge(2, 3, 5.4432);
    graph.insertEdge(2, 4, 6.2322);
    graph.insertEdge(2, 5, 4.2312);
    graph.insertEdge(4, 5, 6.12);
    graph.insertEdge(3, 5, 2.456);
    graph.insertEdge(5, 1, 5.753);
    graph.insertEdge(5, 2, 6.862);
    graph.insertEdge(5, 3, 4.35);
    graph.insertEdge(4, 1, 6.091);
    graph.insertEdge(4, 3, 2.0375);
    graph.insertEdge(4, 0, 4.0289);
    graph.insertEdge(1, 0, 6.9878);
    graph.insertEdge(3, 0, 2.88);
    graph.insertEdge(5, 0, 4.99);
    graph.insertEdge(0, 4, 6.01);
    graph.insertEdge(1, 5, 2.1011);

    graph.insertEdge(1, 3, 4.1289);
    graph.insertEdge(2, 0, 6.9478);
    graph.insertEdge(3, 1, 2.818);
    graph.insertEdge(3, 2, 4.919);
    graph.insertEdge(5, 4, 6.101);
    graph.insertEdge(4, 2, 2.10111);


    ASSERT_EQ(true, graph.minimumSpanningTree());

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
    fptr = setweight1;
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