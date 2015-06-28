/**
*   @Author   - John H Allard Jr.
*   @File     - Traveler.h
*   @Data     - 1/2/2014
*   @Purpose  - This file defines the GraphTraveler class which is closely-related to the GraphInterface class. This
*               class is designed to be passed to the various graph traversal functions (BFS, DFS, min-cost search, etc)
*               so that the user can run their graph algoithms while the search is being ran. This is opposed to the
*               other way of doing it, which is searching for the data, returning a vector of data, letting the
*               user manipulate the copy of the data, then have them store that back into the original graph. This class
*               is an interface, which means it is both pure and abstract.
*               This class consists of at least 4 different function that get called while a graph is being traversed.
*               These functions get called when we examine a new edge eminating from a specific vertex, or we reach the
*               last vertex is the graph traversal, for instance. Our traversal algorithms will automatically call these
*               member functions during the appropriate times on the Traveler object that you pass in. Because the user
*               will override the Traveler class, they can insert any sort of auxillery data to use in their algorithms
*               during traversal.
**/

#ifndef GRAPH_TRAVELER_H
#define GRAPH_TRAVELER_H

#include "../GraphAdjList/Edge/Edge.h"
#include "../GraphAdjList/Vertex/Vertex.h"
#include "../GraphInterface/GraphInterface.h"


template<class VertexType>
class GraphTraveler
{
public:

    // Virtual Destructor
    ~GraphTraveler() {};

    // @func - discover_vertex
    // @args - #1 Data in new vertex that has been discovered
    // @info - This function is called when we jump to a new vertex without traversing an edge, e.g. if we were
    //         going through a list of vertices without consideration to their connections to one another. This
    //         function is not called for BFS/DFS where we only traverse edges to get to new vertices
    virtual void discover_vertex(const VertexType &) = 0;

    // @func - examine_edge
    // @args - #1 The Edge object that we are currently examining.
    // @info - This function is called when we are simply looking at the edges of a given vertex. e.g. during BFS, we
    //         look at all edges incident to the current vertex and push ones we haven't seen into a queue. This
    //         function would be called during each edge examination, regardless of whether is has been looked at before.
    virtual void examine_edge(const Edge<VertexType> &) = 0;

    // @func - traverse_edge
    // @args - #1 An edge object that we are currently traversing (from source to target)
    // @info - This function is called when we actually move to a new vertex along an edge in the graph.
    virtual void traverse_edge(const Edge<VertexType> &) = 0;

    // @func - starting_vertex
    // @args - #1 The data in the first vertex to be examined.
    // @info - This function is called once per algorithm, to register the starting vertex and prepare accordingly.
    virtual void starting_vertex(const VertexType &) = 0;

    // @func - finished_traversal
    // @args - none
    // @info - Called after the last vertex/edge in the graph is traversed to let the user finish any calculations
    //         and clean up any allocations.
    virtual void finished_traversal() = 0;

};

#endif
