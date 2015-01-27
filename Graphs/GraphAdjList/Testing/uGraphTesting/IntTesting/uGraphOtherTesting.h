#include "../../../UndirectedGraph/uGraph.h"
#include "../../../DirectedGraph/dGraph.h"
#include "../../../../GraphTraveler/uTraveler.hpp"
#include <gtest/gtest.h>
#include <sstream>
#include <chrono>
#include <ncurses.h>


TEST(UnionTests, simple_test) {
    uGraph<int> graph;
    graph.insertVertex(1);
    graph.insertVertex(2);
    graph.insertVertex(3);
    graph.insertVertex(4);
    graph.insertVertex(5);
    graph.insertVertex(6);

    uGraph<int> graph2;
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

////////////////////////////////////////////////////
///////////////// ALGORITHM TESTS //////////////////
////////////////////////////////////////////////////




/////////////////////////////////////////////////
////////////////    SPEED TESTS /////////////////
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
