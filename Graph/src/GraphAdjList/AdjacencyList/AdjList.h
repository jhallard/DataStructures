/**
*   @Author   - John H Allard Jr.
*   @File     - adjList.h
*   @Data     - 11/13/2014
*   @Purpose  - This file defines the adjascency list class, which consists of a vertex and a pointer to an edge. The purpose of this class
*				is mostly to simplify the syntax of the code inside of the uGraph class. The uGraph class will simply consist of a vector of this AdjLists,
*				where each AdjList corresponds to a single vertex in the graph and all of the edges that have contact with the vertex.
**/


// V E -> E -> E -> E ->

#ifndef ADJ_LIST_H
#define ADJ_LIST_H

#include <stdexcept>
#include <vector>
#include <string>

#include "../../Vertex/Vertex.h"
#include "../../Edge/Edge.h"

// !!!!!!!!!
// REMOVE FOLLOWING LINE WHEN ACTUAL DEBUGGING
#define nullptr 0
// !!!!!!!!!

template <class VertexType>
class AdjList
{
	
public:

    // @func - Constructor#1
    // @args - None
    // @info - Initializes everything to empty
	AdjList();

    // @func - Constructor#2
    // @args - #1 Vertex data
	AdjList(VertexType);

	// @func - Constructor#3
    // @args - #1 A vertex object to set as our vertex
	AdjList(Vertex<VertexType>);

	bool setVertex(Vertex);

	Vertex getVertex(VertexType);

	// @func - addEdge #1
    // @args - #1 Vertex that the edge points to, #2 weighting of the edge
    // @info - pusheds this edge onto the back of the edge list.
	bool addEdge(Vertex<VertexType> * , double = 1.0);

	// @func - addEdge #2
    // @args - value contained in the vertex that the new edge will point to, #2 weighting of the edge
    // @info - This function is like the one above, but we have to go search through the vertices to see which one contains the matching data, then add that
    //			vertex as an edge in the graph
	bool addEdge(VertexType , double = 1.0);

	// @func - deleteEdge
    // @args - #1 the data contained by the vertex that you wish to delete the edge from
    // @info - finds the vertex containing the data passed in as an argument, and deletes it from the chain.
	bool deleteEdge(VertexType);


	// @func - deleteEdge
    // @args - #1 Pointer to the vertex to be deleted.
    // @info - finds the vertex containing the data passed in as an argument, and deletes it from the chain.
	bool deleteEdge(Vertex<VertexType> *);



private:

	Vertex<VertexType> vertex;

	Edge<VertexType> * pEdge;


};

#include "AdjList.cpp"
#endif