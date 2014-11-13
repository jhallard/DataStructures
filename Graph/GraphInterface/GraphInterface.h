/**
*   @Author   - John H Allard Jr.
*   @File     - GraphInterface.h
*   @Data     - 11/11/2014
*   @Purpose  - Defines an interface for a graph data structure. As C++ has no true interfaces, this class consists purely of public virtual functions,
*               which ensures that the all of the graphs I build (un/directed, adjacency lists, adjacency matrices, etc), which will derive 
*               from this interface, must implement every function listed below. To see graph implementations that use this interface, look inside
*               of the GraphAdjList or GraphAdjMat directories. 
**/

#ifndef GraphInterface_h
#define GraphInterface_h

#include "../GraphAdjList/Edge/Edge.h"
#include "../GraphAdjList/Vertex/Vertex.h"

template<class VertexType>
class GraphInterface
{
public:

    // @func   - insertVertex
    // @args   - #1 The value of the node to be inserted
    // @return - Boolean indicating succes 
    virtual bool insertVertex(VertexType) = 0;

    // @func   - deleteVertex
    // @args   - none
    // @return - Boolean indicating success 
    virtual bool deleteVertex(VertexType) = 0;

    // @func   - insertEdge
    // @args   - #1 The "From" Node, #2 the "To" Node, #3 the weight for this new edge 
    // @return - Boolean indicating succes 
    virtual bool insertEdge(VertexType, VertexType, double = 1.0) = 0;

    // @func   - deleteEdge
    // @args   - #1 The "From" Node, #2 the "To" Node.
    // @return - Boolean indicating succes 
    virtual bool deleteEdge(VertexType, VertexType) = 0;

    // @func   - getWeight
    // @args   - #1 From node, #2 "To" Node
    // @return - Double value that is the weight of the given edge
    // @throws - Exception if the given edge does not exist.
    virtual double getWeight(VertexType, VertexType)  = 0;

    // @func   - numVertices
    // @args   - None
    // @return - The number of vertices currently in the graph.
    virtual int getNumVertices() const = 0;

    // @func   - numEdges
    // @args   - None
    // @return - The number of edges currently in the graph.
    virtual int getNumEdges() const = 0;

    // @func   - containsVertex
    // @args   - #1 data associated with the vertex that you wish to check exists
    // @return - Bool indicating if a vertex containing the given data is found in the graph
    virtual bool containsVertex(VertexType) = 0;

    // @func   - getEdgeWeight
    // @args   - #1 data associated with vetex #1, data associated with vertex #2
    // @return - returns the weight of the edge, throws error if edge not found
    virtual double getEdgeWeight(VertexType, VertexType) = 0;

    // @func   - getAdjVertices
    // @args   - #1 Data contained in vertex that you wish to recieve a list of adjacent vertices of.
    // @return - Vector of pairs, first item is an adjacent vertex, second is the weight of the edge between the two vertices.
    virtual std::vector< std::pair<VertexType, double> > getAdjVertices(VertexType) = 0;

    // @func   - depthFirst
    // @args   - #1 Value contained in node to be searched for
    // @return - nothing
    // @info   - Performs a depth first traversal, calling the visit() function on each item
    virtual void depthFirst(VertexType, void visit(VertexType&)) = 0;

    // @func   - breadthFirst
    // @args   - #1 Value contained in node to be searched for
    // @return - nothing
    // @info   - Performs a breadth first traversal, calling the visit() function on each item
    virtual void breadthFirst(VertexType, void visit(VertexType&)) = 0;

    // @func   - getMinCut
    // @args   - none
    // @return - 2 column vector of vertices, each column representing one half of the cut. 
    // @info   - Partitions the current graph into two subsets that have at the minmum number of edges between them.
    virtual std::vector<std::vector<VertexType> > getMinCut() = 0;

    // @func   - aStarSearch
    // @args   - #1 Data contained in starting vertex for search, #2 Vector of possible goal vertices to reach
    // @return - Vector containing, in-order, the vertices to take to reach your goal. Empty if you are there or no path exists.
    // @info   - Performs the A* path-finding algorithm to get from a starting vertex to any goal vertex in a list of vertices. 
    virtual std::vector<VertexType> aStarSearch(VertexType, std::vector<VertexType>) = 0;


};

#endif