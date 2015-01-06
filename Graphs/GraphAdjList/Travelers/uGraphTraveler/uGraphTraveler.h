/**
*   @Author   - John H Allard Jr.
*   @File     - dGraphTraveler.h
*   @Data     - 1/2/2014
*   @Purpose  - This file declares the uGraphTraveler, which derives from the Traveler class inside the GraphInterface namespace. This class must
*               implement the pure functions from the Traveler class to be used as a traversal object in the dGraph class. This class will simply 
*               assign all of these functions to do nothing, it is up to the user to derive from this class and override the functions to suit the 
*               needs of their specific algorithm.
**/

#ifndef uGraph_Traveler_h
#define uGraph_Traveler_h

#include "../../Edge/Edge.h"
#include "../../Vertex/Vertex.h"
#include "../Traveler/Traveler.h"

template<class VertexType>
class uGraphTraveler : public Traveler<VertexType>
{
public:
    ~uGraphTraveler() {};

    void discover_vertex(const VertexType &) {};

    void examine_edge(const Edge<VertexType> &) {};

    void starting_vertex(const VertexType &) {};

    void finished_trasversal() {};

};

#endif