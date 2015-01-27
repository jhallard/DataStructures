/**
*   @Author   - John H Allard Jr.
*   @File     - adjList.h
*   @Data     - 11/13/2014
*   @Purpose  - This file declares the adjascency list class, which defines a vertex and all of the edges that are incident to this vertex
*               (for directed graphs, only outgoing edges). This is done by storing two main pieces of data, the VertexData associated
*               with the vertex for this adjacenecy list, and a std::list object that contains a series of Edge pointers (Edge is a self
*               defined type, see Edge/Edge.h). I also recently added a hash_map over the adjacent vertices for each adjacency list. This
*               allows us to have constant look-up time to see if a given edge exists, instead of having to perform a linear scan through
*               the edges. We still have to perform a linear scan to actually get the Edge from the list, because we can't map to iterators.
*               The graph classes (uGraph and dGraph) will all have a std::vector of AdjList objects, representing the actual graph.
**/


#ifndef ADJ_LIST_H
#define ADJ_LIST_H

#include <stdexcept>
#include <vector>
#include <string>
#include <list>

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
    bool addEdge(Vertex<VertexType> * , double = 1.0);// std::numeric_limits<double>::infinity());


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

    // @func   - getEdgeList
    // @args   - None
    // @return - The list of edges in the adjlist
    std::list<Edge<VertexType> * > * getEdgeList();

    // @func   - get_num_edges
    // @args   - None
    // @return - The number of edges connected to this particular vertex
    unsigned int get_num_edges();

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

    std::list<Edge<VertexType> * > edge_list;

    unsigned int num_edges;

    bool is_multi_graph;

    std::unordered_map<VertexType, bool> edge_map;


};

#include "AdjList.cpp"
#endif