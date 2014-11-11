/**
*   @Author   - John H Allard Jr.
*   @File     - uGraph.cpp
*   @Data     - 11/12/2014
*   @Purpose  - This is my implementation of the uGraph (undirected Graph) class defined in uGraph.h. This class represents a templated, undirected graph,
*				upon which a user can perform operation like searches, path finding, and other things. This class was implemented as part of my C++ 
*				Data Structures personal project. All code is open license and free to use.
**/

#include "uGraph.h"


//////////////////////////////////////////////////////
////////         PUBLIC FUNCTIONS    /////////////////
//////////////////////////////////////////////////////

// @func - Constructor#1
// @args - None
// @info - Initializes everything to empty
template<class VertexType> uGraph::uGraph() numEdges(0), numVertices(0) {
	
}

// @func  - Constructor#2
// @args  - #1 String that contains the filename from which to load a graph
// @error - Can throw IO error if invalid filename or file structure to build graph 
template<class VertexType> uGraph::uGraph(std::string fn){

// #TODO Load the file given by 'fn' into the graph.
	
}

// @func   - insertNode
// @args   - #1 The value of the node to be inserted
// @return - Boolean indicating succes 
template<class VertexType> bool uGraph::insertNode(VertexType data) {

// Start by creating a new vertex
Vertex<VertexType>* newVertex = new Vertex<VertexType>();
newVertex.setData(data);
newVertex.setIndex(list.size());

std::pair<Vertex<VertexType> , Edge<VertexType> *> adjList = new std::pair<Vertex<VertexType> , Edge<VertexType> *>();
list.push_back()
	
}

// @func   - deleteNode
// @args   - none
// @return - Boolean indicating succes 
template<class VertexType> bool uGraph::deleteNode(VertexType){
	
}

// @func   - insertEdge
// @args   - #1 The "From" Node, the "To" Node, the weight for this new edge 
// @return - Boolean indicating succes 
template<class VertexType> bool insertEdge(VertexType v1, VertexType v2, double weight = 1.0){
	
}

// @func   - deleteEdge
// @args   - #1 The "From" Node, the "To" Node. #Note These two vertices define the edge
// @return - Boolean indicating succes 
template<class VertexType> bool deleteEdge(VertexType v1, VertexType v2){
	
}


// @func   - getWeight
// @args   - #1 From node, #2 "To" Node
// @return - Boolean indicating succes 
template<class VertexType> int getWeight(VertexType, VertexType) const{
	
}

// @func   - numVertices
// @args   - None
// @return - The number of vertices currently in the graph.

template<class VertexType> int getNumVertices() const{
	
}
// @func   - numEdges
// @args   - None
// @return - The number of edges currently in the graph.

template<class VertexType>int getNumEdges() const{
	
}
// @func   - depthFirst
// @args   - None
// @return - nothing
// @info   - Performs a depth first traversal, calling the visit() function on each item

template<class VertexType> void depthFirst(VertexType, void visit(VertexType&)){
	
}

// @func   - breadthFirst
// @args   - None
// @return - nothing
// @info   - Performs a breadth first traversal, calling the visit() function on each item
template<class VertexType> void breadthFirst(VertexType, void visit(VertexType&)){
	
}



//////////////////////////////////////////////////////
/////////        PRIVATE FUNCTIONS    ////////////////
//////////////////////////////////////////////////////


