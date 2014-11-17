#include "../UndirectedGraph/uGraph.h"
#include <iostream>

void intTest();
void stringTest();
void visit(std::string&);
void visit1(int&);

int main()
{

    intTest();

    std::cout << "\n\n\n";

    // stringTest();

    return 0;
}

void intTest() {
    uGraph<int> graph;


    graph.insertVertex(2);
    graph.insertVertex(4);
    graph.insertVertex(6);
    graph.insertVertex(8);
    graph.insertVertex(3);
    graph.insertVertex(5);
    graph.insertVertex(7);
    graph.insertVertex(9);

    graph.insertEdge(2, 4, 4.0);
    graph.insertEdge(2, 8, 5.0);
    graph.insertEdge(2, 6, 1.0);
    graph.insertEdge(4, 6, 2.1);
    graph.insertEdge(8, 4, 7.0);
    graph.insertEdge(8, 6, 0.1);
    graph.insertEdge(2, 3, 4.0);
    graph.insertEdge(2, 7, 5.0);
    graph.insertEdge(2, 5, 1.0);
    graph.insertEdge(4, 9, 2.0);
    graph.insertEdge(4, 5, 5.6);
    graph.insertEdge(4, 3, 2.1);
    graph.insertEdge(8, 7, 7.0);
    graph.insertEdge(8, 3, 4.0);
    graph.insertEdge(8, 5, 0.1);


    void (*fptr)(int&);
    fptr = visit1;
    graph.breadthFirst(8, fptr);


    std::cout << "\n\n\n";

    graph.depthFirst(8, fptr);

    // graph.breadthFirst(4, fptr);


    // if(graph.getNumVertices() == 8)
    //     std::cout << "TRUE \n" << std::endl;
    // else
    //     std::cout << graph.getNumVertices() << std::endl;

    // if(graph.getNumEdges() == 18)
    //     std::cout << "TRUE \n" << std::endl;
    // else
    //     std::cout << graph.getNumEdges() << std::endl;


    if(!graph.deleteVertex(2))
        std::cout << "delete vertex failed\n";

        graph.breadthFirst(8, fptr);


    std::cout << "\n\n\n";

    graph.depthFirst(8, fptr);

    // if(graph.getNumVertices() == 7)
    //     std::cout << "TRUE, 7 Vertices \n" << std::endl;
    // else
    //     std::cout << graph.getNumVertices() << std::endl;

    // if(graph.getNumEdges() == 10)
    //     std::cout << "TRUE \n" << std::endl;
    // else
    //     std::cout << graph.getNumEdges() << std::endl;


    std::vector< std::pair<int, double> > temp = graph.getAdjVertices(8);

    if(temp.size() == 0)
        std::cout << "EMPTY\n";

    double testedge;
    try
    {
        testedge = graph.getEdgeWeight(4, 5);
        if(testedge == 4.0)
            std::cout << "TRUE \n" << std::endl;
        else
            std::cout << testedge << std::endl;
    }
    catch(std::logic_error e) {
        std::cerr << e.what();
    }
    

}

void stringTest() {
    uGraph<std::string> graph;

    graph.insertVertex("abcd");
    graph.insertVertex("1234");
    graph.insertVertex("tada");
    graph.insertVertex("lala");
    graph.insertVertex("qwqw");
    graph.insertVertex("asas");
    graph.insertVertex("zxzx");
    graph.insertVertex("nmnm");

    graph.insertEdge("abcd", "1234", 4.0);
    graph.insertEdge("abcd", "lala", 5.0);
    graph.insertEdge("abcd", "tada", 1.0);
    graph.insertEdge("1234", "abcd", 2.0);
    graph.insertEdge("1234", "lala", 5.6);
    graph.insertEdge("1234", "tada", 2.1);
    graph.insertEdge("lala", "1234", 7.0);
    graph.insertEdge("lala", "abcd", 4.0);
    graph.insertEdge("lala", "tada", 0.1);
    graph.insertEdge("qwqw", "1234", 4.0);
    graph.insertEdge("qwqw", "zxzx", 5.0);
    graph.insertEdge("qwqw", "tada", 1.0);
    graph.insertEdge("asas", "qwqw", 2.0);
    graph.insertEdge("asas", "zxzx", 5.6);
    graph.insertEdge("asas", "tada", 2.1);
    graph.insertEdge("zxzx", "asas", 7.0);
    graph.insertEdge("zxzx", "qwqw", 4.0);
    graph.insertEdge("zxzx", "tada", 0.1);
    graph.insertEdge("nmnm", "qwqw", 2.0);
    graph.insertEdge("nmnm", "zxzx", 5.6);
    graph.insertEdge("nmnm", "tada", 2.1);
    graph.insertEdge("nmnm", "asas", 7.0);
    graph.insertEdge("nmnm", "qwqw", 4.0);
    graph.insertEdge("lala", "tada", 0.1);


    void (*fptr)(std::string&);
    fptr = visit;

    graph.breadthFirst("abcd", fptr);

    std::cout << "\n\n\n";

    graph.depthFirst("qwqw", fptr);



    // if(graph.getNumVertices() == 4)
    //     std::cout << "TRUE 2 \n" << std::endl;
    // else
    //     std::cout << graph.getNumVertices() << std::endl;

    // if(graph.getNumEdges() == 9)
    //     std::cout << "TRUE 2\n" << std::endl;
    // else
    //     std::cout << graph.getNumEdges() << std::endl;

    // double weight;
    // try {
    //     weight = graph.getEdgeWeight("abcd", "1234");

    //     if(weight == 4.0)
    //         std::cout << "TRUE 2 \n" << std::endl;
    //     else
    //         std::cout << weight << std::endl;
    // }
    // catch(std::logic_error e) {
    //     std::cerr << e.what();
    // }


    // graph.deleteEdge("abcd", "1234");
    // graph.deleteEdge("abcd", "lala");
    // graph.deleteEdge("abcd", "tada");
    // graph.deleteEdge("1234", "abcd");
    // graph.deleteEdge("1234", "lala");
    // graph.deleteEdge("1234", "tada");
    // graph.deleteEdge("lala", "1234");
    // graph.deleteEdge("lala", "abcd");
    // graph.deleteEdge("lala", "tada");


    // if(graph.getNumVertices() == 4)
    //     std::cout << "TRUE 3 \n" << std::endl;
    // else
    //     std::cout << graph.getNumVertices() << std::endl;

    // if(graph.getNumEdges() == 0)
    //     std::cout << "TRUE 3\n" << std::endl;
    // else
    //     std::cout << graph.getNumEdges() << std::endl;
}


void visit(std::string &x) {

    std:: cout << x << std::endl;
}

void visit1(int &x) {

    std:: cout << x << std::endl;
}