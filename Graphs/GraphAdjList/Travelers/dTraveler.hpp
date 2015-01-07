/**
*   @Author   - John H Allard Jr.
*   @File     - uTraveler.h
*   @Data     - 1/2/2014
*   @Purpose  - This file defines the a testing traveler class that will process the vertices and edges as they come in.
**/

#ifndef dTraveler_h
#define dTraveler_h

#include "../Edge/Edge.h"
#include "../Vertex/Vertex.h"

template<class V> class dGraph; // forward declaring dGraph class

template<class VertexType>
class dTraveler : public GraphTraveler<VertexType>
{
public:
    ~dTraveler() {};

    void discover_vertex(const VertexType & vert) {
        graph.insertVertex(vert);
    }

    void examine_edge(const Edge<VertexType> & edge) {
        graph.insertVertex(edge.getVertex()->getData());
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

    dGraph<VertexType> graph;

};

#endif