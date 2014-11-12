#include "../UndirectedGraph/uGraph.h"
#include <iostream>

void intTest();
void stringTest();

int main()
{

	intTest();

	stringTest();

	return 0;
}

void intTest(){
	uGraph<int> graph;

	graph.insertVertex(2);
	graph.insertVertex(4);
	graph.insertVertex(6);
	graph.insertVertex(8);

	graph.insertEdge(2, 4, 4.0);
	graph.insertEdge(2, 8, 5.0);
	graph.insertEdge(2, 6, 1.0);
	graph.insertEdge(4, 2, 2.0);
	graph.insertEdge(4, 8, 5.6);
	graph.insertEdge(4, 6, 2.1);
	graph.insertEdge(8, 4, 7.0);
	graph.insertEdge(8, 2, 4.0);
	graph.insertEdge(8, 6, 0.1);


	if(graph.getNumVertices() == 4)
		std::cout << "TRUE \n" << std::endl;
	else
		std::cout << graph.getNumVertices() << std::endl;

	if(graph.getNumEdges() == 9)
		std::cout << "TRUE \n" << std::endl;
	else
		std::cout << graph.getNumEdges() << std::endl;

	Edge<int> * testedge = graph.getEdge(2, 4);
	// double test = graph.getWeight(2, 4);
	if(testedge->getWeight() == 4.0)
		std::cout << "TRUE \n" << std::endl;
	else
		std::cout << testedge->getWeight() << std::endl;
}

void stringTest() {
	uGraph<std::string> graph;

	graph.insertVertex("abcd");
	graph.insertVertex("1234");
	graph.insertVertex("tada");
	graph.insertVertex("lala");

	graph.insertEdge("abcd", "1234", 4.0);
	graph.insertEdge("abcd", "lala", 5.0);
	graph.insertEdge("abcd", "tada", 1.0);
	graph.insertEdge("1234", "abcd", 2.0);
	graph.insertEdge("1234", "lala", 5.6);
	graph.insertEdge("1234", "tada", 2.1);
	graph.insertEdge("lala", "1234", 7.0);
	graph.insertEdge("lala", "abcd", 4.0);
	graph.insertEdge("lala", "tada", 0.1);


	if(graph.getNumVertices() == 4)
		std::cout << "TRUE 2 \n" << std::endl;
	else
		std::cout << graph.getNumVertices() << std::endl;

	if(graph.getNumEdges() == 9)
		std::cout << "TRUE 2\n" << std::endl;
	else
		std::cout << graph.getNumEdges() << std::endl;

	Edge<std::string> * testedge = graph.getEdge("abcd", "1234");
	// double test = graph.getWeight(2, 4);
	if(testedge->getWeight() == 4.0)
		std::cout << "TRUE 2 \n" << std::endl;
	else
		std::cout << testedge->getWeight() << std::endl;
}