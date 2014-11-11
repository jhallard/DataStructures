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


	if(graph.getNumVertices() == 4)
		std::cout << "TRUE \n" << std::endl;
	else
		std::cout << graph.getNumVertices() << std::endl;

		if(graph.getNumEdges() == 1)
		std::cout << "TRUE \n" << std::endl;
	else
		std::cout << graph.getNumEdges() << std::endl;
	
	return 0;
}