/**
*   @Author   - John H Allard Jr.
*   @File     - adjList.h
*   @Data     - 11/13/2014
*   @Purpose  - This file defines the adjascency list class, which consists of a vertex and a pointer to an edge. The purpose of this class
*               is mostly to simplify the syntax of the code inside of the uGraph class. The uGraph class will simply consist of a vector of this AdjLists,
*               where each AdjList corresponds to a single vertex in the graph and all of the edges that have contact with the vertex.
**/


// V E -> E -> E -> E ->

#ifndef ADJ_LIST_H
#define ADJ_LIST_H

#include <stdexcept>
#include <vector>
#include <string>

#include "../Vertex/Vertex.h"
#include "../Edge/Edge.h"


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

    // @func - setVertex
    // @args - #1 A vertex object to set as our vertex
    // @ret  - bool indicating success or failure
    bool setVertex(Vertex<VertexType>);

    // @func - getVertex
    // @args - none
    // @ret  - pointer to the vertex object in this adj list
    Vertex<VertexType> * getVertex();

    // @func - addEdge #1
    // @args - #1 Vertex that the edge points to, #2 weighting of the edge
    // @info - pusheds this edge onto the back of the edge list.
    bool addEdge(Vertex<VertexType> * , double = 1.0);


    // @func - deleteEdge
    // @args - #1 the data contained by the vertex that you wish to delete the edge from
    // @info - finds the vertex containing the data passed in as an argument, and deletes it from the chain.
    bool deleteEdge(VertexType);


    // @func - deleteEdge
    // @args - #1 Pointer to the vertex to be deleted.
    // @info - finds the vertex containing the data passed in as an argument, and deletes it from the chain.
    bool deleteEdge(Vertex<VertexType> *);


    // @func - getEdge
    // @args - #1 Pointer to the edge to be returned.
    // @info - ffinds and returns the given edge if it exists
    Edge<VertexType> * getEdge(Vertex<VertexType> *);



private:

    Vertex<VertexType> vertex;

    Edge<VertexType> * pEdge;


};

#include "AdjList.cpp"
#endif