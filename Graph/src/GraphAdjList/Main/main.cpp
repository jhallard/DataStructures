#include "../UndirectedGraph/uGraph.h"
#include <iostream>

int main()
{
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


	
	return 0;
}