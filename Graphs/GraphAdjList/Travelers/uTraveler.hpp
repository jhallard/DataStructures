/**
*   @Author   - John H Allard Jr.
*   @File     - uTraveler.h
*   @Data     - 1/2/2014
*   @Purpose  - This file defines the a testing traveler class that will process the vertices and edges as they come in.
**/

#ifndef uTraveler_h
#define uTraveler_h

#include "../Edge/Edge.h"
#include "../Vertex/Vertex.h"

template<class V> class uGraph;

template<class VertexType>
class uTraveler : public GraphTraveler<VertexType>
{
public:
    ~uTraveler() {};

    void discover_vertex(const VertexType & vert) {
        graph.insertVertex(vert);
    }

    void examine_edge(const Edge<VertexType> & edge) {
        graph.insertVertex(edge.getTarget()->getData());
        graph.insertEdge(edge.getSource()->getData(), edge.getTarget()->getData(), edge.getWeight());
    }

    void starting_vertex(const VertexType & vert) {
        graph.insertVertex(vert);
    }

    void finished_traversal() {
    }

    uGraph<VertexType> graph;

};

#endif