#include "../UndirectedGraph/uGraph.h"
#include <iostream>
#include <ctime>

void intTest1();
void intTest2();
void stringTest();
void visit(std::string&);
void visit1(int&);

int main()
{
    srand(time(0));
    srand(time(0));
    srand(time(0));

    // intTest());
    // intTest2();

    std::cout << "\n\n\n";

    stringTest();

    return 0;
}



void intTest1() {
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


    if(graph.getNumVertices() == 8)
        std::cout << "TRUE \n" << std::endl;
    else
        std::cout << graph.getNumVertices() << std::endl;

    if(graph.getNumEdges() == 18)
        std::cout << "TRUE \n" << std::endl;
    else
        std::cout << graph.getNumEdges() << std::endl;


    if(!graph.deleteVertex(2))
        std::cout << "delete vertex failed\n";


    if(graph.getNumVertices() == 7)
        std::cout << "TRUE, 7 Vertices \n" << std::endl;
    else
        std::cout << graph.getNumVertices() << std::endl;

    if(graph.getNumEdges() == 10)
        std::cout << "TRUE \n" << std::endl;
    else
        std::cout << graph.getNumEdges() << std::endl;


    std::vector< std::pair<int, double> > temp = graph.getAdjVertices(8);

    if(temp.size() == 0)
        std::cout << "EMPTY\n";

    double testedge;
    try
    {
        testedge = graph.getEdgeWeight(4, 9);
        if(testedge == 2.0)
            std::cout << "TRUE WEIGHT\n" << std::endl;
        else
            std::cout << testedge << std::endl;
    }
    catch(std::logic_error e) {
        std::cerr << e.what();
    }

    graph.breadthFirst(8, fptr);

    std::cout << "\n\n\n";

    graph.depthFirst(8, fptr);
    

}




void intTest2() {

    uGraph<int> graph;

    int numVertices = 400;
    int minEdges = 2;
    int maxEdges = 8;

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

    graph.printGraph();

    std::cout << "\n\n Connected : " << ((graph.isConnected())? "YES\n" : "NO\n");

    getchar();



    void (*fptr)(int&);
    fptr = visit1;

    // for(int i = 1; i <=18; i++) {
    //     std::cout << "Breadth First Search, Starting Vertex : " << i << "\n\n";
    //     graph.breadthFirst(i, fptr);
    //     std::cout << "\n";
    //     std::cout << "Depth First Search, Starting Vertex : " << i << "\n\n";
    //     graph.depthFirst(i, fptr);
    //     getchar();
    //     std::cout << "\n\n\n\n\n";

    // }

    // graph.deleteVertex(2);
    // graph.deleteVertex(8);

    // for(int i = 1; i <=18; i++) {
    //     std::cout << "Breadth First Search, Starting Vertex : " << i << "\n\n";
    //     graph.breadthFirst(i, fptr);
    //     std::cout << "\n";
    //     std::cout << "Depth First Search, Starting Vertex : " << i << "\n\n";
    //     graph.depthFirst(i, fptr);
    //     getchar();
    //     std::cout << "\n\n\n\n\n";

    // }
   

}




void stringTest() {
    uGraph<std::string> graph;

    graph.insertVertex("abcd");
    graph.insertVertex("1234");
    graph.insertVertex("tada");
    graph.insertVertex("lala");
    // graph.insertVertex("qwqw");
    // graph.insertVertex("asas");
    // graph.insertVertex("zxzx");
    // graph.insertVertex("nmnm");

    graph.insertEdge("abcd", "1234", 4.0);
    graph.insertEdge("abcd", "lala", 5.0);
    graph.insertEdge("abcd", "tada", 1.0);
    graph.insertEdge("1234", "abcd", 2.0);
    graph.insertEdge("1234", "lala", 5.6);
    graph.insertEdge("1234", "tada", 2.1);
    graph.insertEdge("lala", "1234", 7.0);
    graph.insertEdge("lala", "abcd", 4.0);
    graph.insertEdge("lala", "tada", 0.1);


    graph.printGraph();

    graph.deleteEdge("lala", "abcd");
    // graph.deleteEdge("tada", "1234");

    graph.printGraph();
    void (*fptr)(std::string&);
    fptr = visit;

    // graph.breadthFirst("abcd", fptr);

    // std::cout << "\n\n\n";

    graph.deleteVertex("lala");

    // graph.breadthFirst("abcd", fptr);


    std::cout << "\n\n\n";


}


void visit(std::string &x) {

    std:: cout << x << std::endl;
}

void visit1(int &x) {

    std:: cout << x << ", ";
}