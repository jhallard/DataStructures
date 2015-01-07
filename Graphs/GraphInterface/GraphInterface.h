/**
*   @Author   - John H Allard Jr.
*   @File     - GraphInterface.h
*   @Data     - 11/11/2014
*   @Purpose  - This file defines an interface for a graph data structure. As C++ has no true interfaces, this class consists purely of public virtual
*               functions, which ensures that the all of the graphs which will derive from this interface must implement every function listed below. 
*               To see graph implementations that use this interface, look inside of the GraphAdjList or GraphAdjMat directories. All code is open 
*               license and free to use, just leave some sort of note in your source code giving credit to me and a link to my github (github.com/jhallard)
**/

#ifndef GraphInterface_h
#define GraphInterface_h

#include <unordered_map>
#include <limits>
#include "../GraphAdjList/Edge/Edge.h"
#include "../GraphAdjList/Vertex/Vertex.h"
#include "../GraphTraveler/GraphTraveler.hpp"

template<class VertexType>
class GraphInterface
{
public:

    // @func  - Destructor
    // @info  - Cleans up the dynamically allocated AdjList objects contained in the list vector.
    virtual ~GraphInterface() {};

    // @func   - insertVertex
    // @args   - #1 The value of the node to be inserted
    // @return - Boolean indicating succes 
    virtual bool insertVertex(const VertexType &) = 0;

    // @func   - deleteVertex
    // @args   - Vertex data of the node to be deleted
    // @return - Boolean indicating success 
    virtual bool deleteVertex(const VertexType &) = 0;

    // @func   - deleteVertices
    // @args   - #1 Vector of Vertex data corresponding to the vertices to be added.
    // @return - Boolean indicating succes 
    virtual bool insertVertices(std::vector<VertexType>) = 0;

    // @func   - deleteVertices
    // @args   - #1 Vector of Vertex data corresponding to the vertices to be deleted.
    // @return - Boolean indicating success 
    virtual bool deleteVertices(std::vector<VertexType>) = 0;

    // @func   - getAllVertices
    // @args   - none
    // @return - Vector of the data contained inside all vertices. 
    virtual std::vector<VertexType> getAllVertices() const = 0;

    // @func   - insertEdge
    // @args   - #1 The "From" Node, #2 the "To" Node, #3 the weight for this new edge 
    // @return - Boolean indicating succes 
    virtual bool insertEdge(const VertexType &, const VertexType &, double = std::numeric_limits<double>::infinity()) = 0;

    // @func   - deleteEdge
    // @args   - #1 The "From" Node, #2 the "To" Node.
    // @return - Boolean indicating succes 
    virtual bool deleteEdge(const VertexType &, const VertexType &) = 0;

    // @func   - getNumVertices
    // @args   - None
    // @return - The number of vertices currently in the graph.
    virtual int getNumVertices() const = 0;

    // @func   - getNumEdges
    // @args   - None
    // @return - The number of edges currently in the graph.
    virtual int getNumEdges() const = 0;

    // @func   - containsVertex
    // @args   - #1 data associated with the vertex that you wish to query for existence 
    // @return - Bool corresponding to the existence of a vertex with the given data in this graph
    virtual bool containsVertex(const VertexType &) = 0;

    // @func   - containsEdge
    // @args   - #1 data associated with the 'from' vertex, #2 data associated with the 'to' vertex.
    // @return - Bool corresponding to the existence of an edge in the graph between the two vertices
    // @info   - For directed graphs, this returns true only if the edge is going from arg#1 to arg#2. For undirected
    //           graphs it will return true if an edge exists between the vertices without considering the order.
    virtual bool containsEdge(const VertexType &, const VertexType &) = 0;

    // @func   - getEdgeWeight
    // @args   - #1 data associated with vetex #1, data associated with vertex #2
    // @return - returns the weight of the edge, throws error if edge not found
    virtual double getEdgeWeight(const VertexType &, const VertexType &) = 0;

    // @func   - getEdgeWeight
    // @args   - #1 data associated with vetex #1, data associated with vertex #2, #3 weight to set
    // @return - returns the weight of the edge, throws error if edge not found
    virtual bool setEdgeWeight(const VertexType &, const VertexType &, double) = 0;

    // @func   - getAdjVertices
    // @args   - #1 Data contained in vertex that you wish to recieve a list of adjacent vertices of.
    // @return - Vector of pairs, first item is an adjacent vertex, second is the weight of the edge between the two vertices.
    virtual std::vector<std::pair<VertexType, double> > getAdjVertices(const VertexType &) const = 0;

    // @func   - makeGraphDense
    // @args   - #1 Weight to assign to all edges in the new graph.
    // @return - Bool indicating success
    // @info   - This function removes all current edges from the graph, and instead makes a dense graph out of the current vertices
    //           with the weight for each edge determined by the given function (arg #1).
    virtual bool makeGraphDense(double setWeight(VertexType&, VertexType&) = nullptr) = 0;

    // @func   - invert
    // @args   - #1 Weighing function that takes in two vertices and assigns a weight to an edge between them
    // @return - Bool indicating success
    // @info   - This function inverts the current graph, which means it removes all existing edges and emplaces all possible edges
    //           that didn't already exist.
    virtual bool invert(double setWeight(VertexType&, VertexType&) = nullptr) = 0;

    // @func   - reverse
    // @args   - none
    // @return - Bool indicating success
    // @info   - This function switches the direction of all edges, only does something meaningful for directed graphs.
    virtual bool reverse() = 0;

    // @func   - isConnected
    // @args   - None
    // @return - Bool indicating whether or not the graph is connected
    // @info   - This function searches through the given graph to see if any given vertex can be reached from any other given vertex
    virtual bool isConnected() = 0;

    // @func   - isBipartite
    // @args   - None
    // @return - Bool indicating whether or not the graph is bipartite
    // @info   - This function uses BFS, marking every other vertex a 0 or 1, and checking if it can reach all vertices without
    //           hitting the same value twice in a row. 
    virtual bool isBipartite() = 0;

    // @func   - getBipartition
    // @args   - std::pair pointer that will be filled with two vectors of vertices, consisting of one bipartition of the graph
    // @return - Bool indicating whether or not the graph is bipartite and able to be bipartitioned
    virtual bool getBipartition(std::pair<std::vector<VertexType>, std::vector<VertexType> > *) = 0;

    // @func   - depthFirst
    // @args   - #1 Data associated with the starting vertex for the search, #2 Traveler class to process the graph components as they're discovered.
    // @return - Bool indicating if the function could find the starting vertex based on arg#1
    // @info   - Performs a depth first traversal, calling the appropraite function inside of the Traveler class when it encounters a new vertex or edge.
    //           This function assumes that all vertex data is unique, so if this is a graph of strings, no two strings should be the same.
    //           This precondition allows us to use an std::unordered_map to keep track of the seen and unseen vertices.
    virtual bool depthFirst(const VertexType &, GraphTraveler<VertexType> * = nullptr) = 0;

    // @func   - breadthFirst
    // @args   - #1 Data associated with the starting vertex for the search,  #2 Traveler class to process the graph components as they're discovered. 
    // @return - Bool indicating if the function could find the starting vertex based on arg#1
    // @info   - Performs a breadth first traversal, calling the appropraite function inside of the Traveler class when it encounters a new vertex or edge.
    //           This function assumes that all vertex data is unique, so if this is a graph of strings, no two strings should be the same.
    //           This precondition allows us to use an std::unordered_map to keep track of the seen and unseen vertices.
    virtual bool breadthFirst(const VertexType &, GraphTraveler<VertexType> * = nullptr) = 0;

    // @func   - minimuminCut
    // @args   - none
    // @return - 2 column vector of vertices, each column representing one half of the cut. 
    // @info   - Partitions the current graph into two subsets that have at the minmum number of edges between them.
    //           Not yet completed, only about half-way done. This function signature probably isn't even final.
    virtual std::vector<std::vector<VertexType> > minimumCut() = 0;

    // @func   - minimuminSpanningTree
    // @args   - none
    // @return - Boolean that indicates if the minimum tree could be traversed or not, false if the graph is not strongly-connected 
    // @info   - This function will traverse the graph is such an order as to build a minimum spanning tree, 
    virtual bool minimumSpanningTree(GraphTraveler<VertexType> * = nullptr) = 0;

    // @func   - dijkstrasMinimumTree
    // @args   - #1 Data contained in starting vertex for search
    // @return - A pair containing two maps. The first map takes a vertex and returns the previuos vertex in the path there from the source vertex. 
    //           The second map takes a vertex and gives the total weight that it takes to get there from the source vertex.
    // @info   - Performs Dijkstra's path-finding algorithm to get from a starting vertex to any goal vertex in the map, throws an exception if
    //           the source vertex is not contained in the map.
    virtual std::pair<std::unordered_map<VertexType, VertexType>, std::unordered_map<VertexType, double> > dijkstrasMinimumTree(const VertexType &) = 0;

    // @func   - dijkstrasMinimumPath
    // @args   - #1 Source Vertex, #2 Dest Vertex, #3 the GraphTraveler-derived object that will recieve the vertices and edges in minimum order
    // @return - bool indicating success, will return false for graphs with no connection between src and dest vertices.
    // @info   - This function is intended for the user to call to compute the shortest path between any two vertices. This function calls
    //           the dijkstras(...) function and decodes the output to give the user the specific path they are looking for, as opposed to a 
    //           structure that contains the shortest path from the source vertex to any vertex in the map.
    virtual bool dijkstrasMinimumPath(const VertexType &, const VertexType &, GraphTraveler<VertexType> * = nullptr) = 0;

    // dijkstrasMinimumPath dijkstrasMinimumTree

    // @func   - aStar
    // @args   - #1 Data contained in starting vertex for search, #2 Vector of possible goal vertices to reach, #3 Pointer to a hueristic function on a given node
    // @return - Vector containing, in-order, the vertices to take to reach your goal. Empty if you are there or no path exists.
    // @info   - Performs the A* path-finding algorithm to get from a starting vertex to any goal vertex in a list of vertices. 
    virtual std::vector<VertexType> aStar(const VertexType &, std::vector<VertexType>, double hueristic(VertexType&, VertexType&)) = 0;


};
#endif