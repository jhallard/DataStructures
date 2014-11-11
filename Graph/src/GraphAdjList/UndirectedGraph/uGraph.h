/**
*   @Author   - John H Allard Jr.
*   @File     - uGraph.h
*   @Data     - 11/11/2014
*   @Purpose  - This is the defintion of the uGraph class. This class represents a weighted (optional), undirected, tamplated graph data structure
*               that uses an adjacency list as an internal representation of the graph. The graph is templated to allow vertices to contain any
*               type of data that the user wishes it to contain. This class depends on the AdjList, Edge, and Vertex classes.
**/

#ifndef U_GRAPH_A_LIST_H
#define U_GRAPH_A_LIST_H

#include <stdexcept>
#include <vector>
#include <string>
#include <stdexcept>

#include "../../GraphInterface/GraphInterface.h"
#include "../AdjacencyList/AdjList.h"
#include "../Vertex/Vertex.h"
#include "../Edge/Edge.h"


template <class VertexType>
class uGraph : public GraphInterface <VertexType>
{


//////////////////////////////////////////////////////
////////         PUBLIC INTERFACE       //////////////
//////////////////////////////////////////////////////
public:

    // @func - Constructor#1
    // @args - None
    // @info - Initializes everything to empty
    uGraph();

    // @func  - Constructor#2
    // @args  - #1 String that contains the filename from which to load a graph
    // @error - Can throw IO error if invalid filename or file structure to build graph 
    uGraph(std::string fn);

    // @func   - insertVertex
    // @args   - #1 The value of the node to be inserted
    // @return - Boolean indicating succes 
    bool insertVertex(VertexType);

    // @func   - deleteVertex
    // @args   - none
    // @return - Boolean indicating success 
    bool deleteVertex(VertexType);

    // @func   - insertEdge
    // @args   - #1 The "From" Node, the "To" Node, the weight for this new edge 
    // @return - Boolean indicating succes 
    bool insertEdge(VertexType v1, VertexType v2, double weight = 1.0);

    // @func   - deleteEdge
    // @args   - #1 The "From" Node, the "To" Node. #Note These two vertices define the edge
    // @return - Boolean indicating succes 
    bool deleteEdge(VertexType v1, VertexType v2);


    // @func   - getWeight
    // @args   - #1 From node, #2 "To" Node
    // @return - Double value that is the weight of the given edge
    // @throws - Exception if the given edge does not exist.
    double getWeight(VertexType, VertexType) ;

    // @func   - numVertices
    // @args   - None
    // @return - The number of vertices currently in the graph.
    int getNumVertices() const;

    // @func   - numEdges
    // @args   - None
    // @return - The number of edges currently in the graph.
    int getNumEdges() const;

    // @func   - getVerex
    // @args   - #1 data associated with the vertex that you wish to retrieve
    // @return - returns a pointer to the vertex containing the appropriate data, returns nullptr if vertex cannot be found
    Vertex<VertexType> * getVertex(VertexType);

    // @func   - getVerex
    // @args   - #1 data associated with vetex #1, data associated with vertex #2
    // @return - returns a pointer to the edge that connects the two vertices. Returns nullptr if not found
    Edge<VertexType> * getEdge(VertexType, VertexType);

    // @func   - depthFirst
    // @args   - #1 Value contained in node to be searched for
    // @return - nothing
    // @info   - Performs a depth first traversal, calling the visit() function on each item
    void depthFirst(VertexType, void visit(VertexType&));

    // @func   - breadthFirst
    // @args   - #1 Value contained in node to be searched for
    // @return - nothing
    // @info   - Performs a breadth first traversal, calling the visit() function on each item
    void breadthFirst(VertexType, void visit(VertexType&));

    // ---- TODO ---- //
    // #1 - Add Copy Constructor, this class uses pointers and dynamic memory so we will need our own copy constructor.
    // #2 - Override equals operator, check to see if two graphs are equivilent



//////////////////////////////////////////////////////
////////           PRIVATE DATA      /////////////////
//////////////////////////////////////////////////////
private:

    // @member - numVertices
    // @info   - Number of vertices currently in the graph
    int numVertices;

    // @member - numEdges
    // @info   - Number of Edges currently in the graph
    int numEdges;

    // @member - list
    // @info   - A vector of pointers to adjacency lists, one adjlist for each vertex in our graph. Each adjlist represents that vertex and all of the edges eminating
    //           from it to other vertices in the graph
    std::vector< AdjList<VertexType> * > list;


//////////////////////////////////////////////////////
////////       PRIVATE FUNCTIONS     /////////////////
//////////////////////////////////////////////////////

    // @func   - findVertex
    // @args   - #1 Value contained in the vertex to be found
    // @return - pointer to the vertex to be found, null if not found
    // @info   - Goes through our vector of vertices and find which one (if any) contain the data given by the argument
    typename std::vector< AdjList<VertexType> * >::iterator findVertex(VertexType) ;

};

#include "uGraph.cpp"
#endif