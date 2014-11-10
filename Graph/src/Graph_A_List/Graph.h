/**
*	@Author   - John H Allard Jr.
*	@File     - Graph.h
*	@Data     - 11/11/2014
*	@Purpose  - This is my implementation of a graph data structure using an adjascency list, as apposed to an adjascency matrix. I will also implement a graph
*				using an adjascency matrix in the future, and it can be found in ../Graph_A_Mat/. This graph is templated to allow the user to choose what type 
*				of values to store in the vertices. 
*
*	@TODO     - Decide on if the graph is going to be weighted or not, if it is, what type of values are going to be the weights? Will it be templated?
*			  - Is this going to be a directed or undirected graph? Undirected would certainly be easier.
*
**/

#ifndef GRAPH_A_LIST_H
#define GRAPH_A_LIST_H

#include <vector>
#include <string>

#include "../GraphInterface/GraphInterface.h"
#include "../Vertex/Vertex.h"


template <class VertexType>
class Graph : public GraphInterface <VertexType>
{

public:

	// @func - Coonstructor#1
	// @args - None
	// @info - Initializes everything to empty
	Graph(bool directed);

	// @func  - Coonstructor#2
	// @args  - #1 String that contains the filename from which to load a graph
	// @error - Can throw IO error if invalid filename or file structure to build graph 
	Graph(bool directed, std::string fn);

	// @func   - insertNode
	// @args   - #1 The value of the node to be inserted
	// @return - Boolean indicating succes 
	bool insertNode(VertexType);

	// @func   - deleteNode
	// @args   - none
	// @return - Boolean indicating succes 
	bool deleteNode();

	// @func   - insertEdge
	// @args   - #1 The "From" Node, the "To" Node, the weight for this new edge 
	// @return - Boolean indicating succes 
	bool insertEdge(VertexType v1, VertexType v2, int weight);

	// @func   - deleteEdge
	// @args   - #1 The "From" Node, the "To" Node. #Note These two vertices define the edge
	// @return - Boolean indicating succes 
	bool deleteEdge(VertexType v1, VertexType v2);


	// @func   - getWeight
	// @args   - #1 From node, #2 "To" Node
	// @return - Boolean indicating succes 
	int getWeight(NodeType, NodeType) const;

	// @func   - numVertices
	// @args   - None
	// @return - The number of vertices currently in the graph.
	int numVertices() const;

	// @func   - numEdges
	// @args   - None
	// @return - The number of edges currently in the graph.
	int numEdges() const;

	// @func   - depthFirst
	// @args   - None
	// @return - nothing
	// @info   - Performs a depth first traversal, calling the visit() function on each item
	void depthFirst(NodeType, void visit(NodeType&));

	// @func   - breadthFirst
	// @args   - None
	// @return - nothing
	// @info   - Performs a breadth first traversal, calling the visit() function on each item
	void breadthFirst(NodeType, void visit(NodeType&));


private:
	// Must be set by the user during object instantiation. If true, the graph will be treated as directed and each function above will act as such.
	// if set to false, then the graph will be undirected and any edges will be assumed to be symmetric between vertices in our implementation.
	const bool directed;


};
#endif