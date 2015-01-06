/**
*   @Author   - John H Allard Jr.
*   @File     - Traveler.h
*   @Data     - 1/2/2014
*   @Purpose  - This file defines the Traveler class, which is a class defined within the GraphInterface class. This class is designed to be passed to
*               the various graph traversal functions (BFS, DFS, min-cost search, etc) so that the user can run their graph algoithms while the search
*               is being ran. This is opposed to the other way of doing it, which is searching for the data, returning a vector of data, letting the
*               user manipulate the copy of the data, then have them store that back into the original graph. This class is an interface, which means it
*               is both pure and abstract. Both of the uGraph and dGraph classes will have their own derived graph traveler classes that define default
*               traveler functionality. 
*               This class consists of at least 4 different function that get called while a graph is being traversed. These functions get called when
*               we examine a new edge eminating from a specific vertex, or we reach the last vertex is the graph traversal, for instance. Our traversal
*               algorithms will automatically call these member functions during the appropriate times on the Traveler object that you pass in. Because
*               the user will override the Traveler class, they can insert any sort of auxillery data to use in their algorithms during traversal.
**/

#ifndef Graph_Traveler_h
#define Graph_Traveler_h

#include "../../Edge/Edge.h"
#include "../../Vertex/Vertex.h"
// #include "../../../GraphInterface/GraphInterface.h"


template<class VertexType>
class Traveler
{
public:
    ~Traveler() {};

    virtual void discover_vertex(const VertexType &) = 0;

    virtual void examine_edge(const Edge<VertexType> &) = 0;

    virtual void starting_vertex(const VertexType &) = 0;

    virtual void finished_trasversal() = 0;

};

#endif