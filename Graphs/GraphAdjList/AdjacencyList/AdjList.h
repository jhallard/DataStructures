/**
*   @Author   - John H Allard Jr.
*   @File     - adjList.h
*   @Data     - 11/13/2014
*   @Purpose  - This file declares the adjascency list class, which consists of a vertex and a pointer to an edge. The purpose of this class
*               is mostly to simplify the syntax of the code inside of the uGraph class. The uGraph class will simply consist of a vector of this AdjLists,
*               where each AdjList corresponds to a single vertex in the graph and all of the edges that have contact with the vertex.
*               All code is open license and free to use, just leave some sort of note in your source code giving credit to me and 
*               a link to my github (github.com/jhallard)
**/


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
    AdjList(const VertexType &);

    // @func - Constructor#3
    // @args - #1 A vertex object to set as our vertex
    AdjList(const Vertex<VertexType> &);

    // @func - Destructor
    // @args - Cleans up the edges allocated with new()
    ~AdjList();

    // @func - setVertex
    // @args - #1 A vertex object to set as our vertex
    // @ret  - bool indicating success or failure
    bool setVertex(const Vertex<VertexType> &);

    // @func - getVertex
    // @args - none
    // @ret  - pointer to the vertex object in this adj list
    Vertex<VertexType> * getVertex();

    // @func - addEdge #1
    // @args - #1 Vertex that the edge points to, #2 weighting of the edge
    // @info - pusheds this edge onto the back of the edge list.
    bool addEdge(Vertex<VertexType> * , double =  std::numeric_limits<double>::infinity());


    // @func - deleteEdge
    // @args - #1 the data contained by the vertex that you wish to delete the edge from
    // @info - finds the vertex containing the data passed in as an argument, and deletes it from the chain.
    bool deleteEdge(const VertexType &);

    // @func - deleteEdge
    // @args - #1 Pointer to the vertex to be deleted.
    // @info - finds the vertex containing the data passed in as an argument, and deletes it from the chain.
    bool deleteEdge(Vertex<VertexType> *);

    // @func - deleteAllEdges
    // @args - None
    // @info - deletes all edges ajascent to the this vertex
    bool deleteAllEdges();

    // @func - getEdge
    // @args - #1 Pointer to the edge object
    // @info - finds and returns the given edge if it exists, returns null otherwise
    Edge<VertexType> * getEdge(const Vertex<VertexType> &);

    // @func   - getAllEdges
    // @args   - None
    // @return - Vector of pointers to all the edge objects in the class
    std::vector<Edge<VertexType> *> getAllEdges();

    // @func   - getNumEdges
    // @args   - None
    // @return - The number of edges connected to this particular vertex
    unsigned int getNumEdges();

    // @func   - set_is_multi_graph
    // @args   - boolean to be stored in is_multi_graph
    // @return - Bool indicating success
    bool set_is_multi_graph(bool);

    // @func   - get_is_multi_graph
    // @args   - None
    // @return - Bool value of is_multi_graph
    bool get_is_multi_graph();




private:

    // @func   - removeSelfLoops()
    // @args   - none
    // @return - bool indicating if any were found
    // @info   - This function removes any self-loops in the graph. It is private because the only time when the graph can have self-loops is when vertices
    //           are collapsed into each other from another member function (like minimumCut), the user should never encounter a situation where self loops
    //           arise in the graph (they are created and destroyed inside a function).
    bool removeSelfLoops();

    // @member  - vertex
    // @info    - The vertex object for this adj list.
    Vertex<VertexType> vertex;

    // @member  - pEdge
    // @info    - Head node pointer for the linked list of edges that eminate from the vertex member
    Edge<VertexType> * pEdge;

    unsigned int numEdges;

    bool is_multi_graph;


};

#include "AdjList.cpp"
#endif