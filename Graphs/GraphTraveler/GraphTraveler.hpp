/**
*   @Author   - John H Allard Jr.
*   @File     - Traveler.h
*   @Data     - 1/2/2014
*   @Purpose  - This file defines the GraphTraveler class which is closely-related to the GraphInterface class. This class is designed to be passed to
*               the various graph traversal functions (BFS, DFS, min-cost search, etc) so that the user can run their graph algoithms while the search
*               is being ran. This is opposed to the other way of doing it, which is searching for the data, returning a vector of data, letting the
*               user manipulate the copy of the data, then have them store that back into the original graph. This class is an interface, which means it
*               is both pure and abstract.
*               This class consists of at least 4 different function that get called while a graph is being traversed. These functions get called when
*               we examine a new edge eminating from a specific vertex, or we reach the last vertex is the graph traversal, for instance. Our traversal
*               algorithms will automatically call these member functions during the appropriate times on the Traveler object that you pass in. Because
*               the user will override the Traveler class, they can insert any sort of auxillery data to use in their algorithms during traversal.
**/

#ifndef Graph_Traveler_h
#define Graph_Traveler_h

#include "../GraphAdjList/Edge/Edge.h"
#include "../GraphAdjList/Vertex/Vertex.h"
#include "../GraphInterface/GraphInterface.h"


template<class VertexType>
class GraphTraveler
{
public:

    // Virtual Destructor
    ~GraphTraveler() {};

    // @function - discover_vertex
    // @args     - #1 Data in new vertex that has been discovered
    // @info     - This function is called when a new vertex is moved to as the current vertex (except on the first vertex, starting_vertex is
    //             called in that case). You can use this function to push vertices into a graph or other structure.
    virtual void discover_vertex(const VertexType &) = 0;

    // @function - examine_edge
    // @args     - #1 An edge object, this contains a pointer to the target verex and the weight on the edge.
    // @info     - This function is called when we are looking at the neighbors of the current vertex during a search. 
    virtual void examine_edge(const Edge<VertexType> &) = 0;

    // @function - traverse_edge
    // @args     - #1 An edge object, this contains a pointer to the target verex and the weight on the edge.
    // @info     - This function is called when we traverse an edge to a new vertex 
    virtual void traverse_edge(const Edge<VertexType> &) = 0;

    // @function - starting_vertex
    // @args     - 
    // @info
    virtual void starting_vertex(const VertexType &) = 0;

    // @function - finsihed_traversal 
    // @args     - none
    // @info     - Called after the last vertex/edge in the graph is traversed
    virtual void finished_traversal() = 0;

};

#endif