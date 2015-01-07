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
    }

    // @function - traverse_edge
    // @args     - #1 An edge object, this contains a pointer to the target verex and the weight on the edge.
    // @info     - This function is called when we traverse an edge to a new vertex 
    void traverse_edge(const Edge<VertexType> & edge) {
        graph.insertVertex(edge.getVertex()->getData());
        graph.insertVertex(edge.getSource()->getData());
        graph.insertEdge(edge.getSource()->getData(), edge.getVertex()->getData(), edge.getWeight());
    }


    void starting_vertex(const VertexType & vert) {
        graph.insertVertex(vert);
    }

    void finished_traversal() {
    }

    uGraph<VertexType> graph;

};

#endif