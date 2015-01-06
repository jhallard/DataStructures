/**
*   @Author   - John H Allard Jr.
*   @File     - Traveler.h
*   @Data     - 1/2/2014
*   @Purpose  - This file defines the a testing traveler class that will process the vertices and edges as they come in.
**/

#ifndef My_Traveler_h
#define My_Traveler_h

#include "../Edge/Edge.h"
#include "../Vertex/Vertex.h"
#include "../DirectedGraph/dGraph.h"


template<class VertexType>
class Traveler : public GraphTraveler<VertexType>
{
public:
    ~Traveler() {};

    void discover_vertex(const VertexType & vert) {
        VertexType tmp = vert;
        last_vertex = tmp;
        graph.insertVertex(last_vertex);
    }

    void examine_edge(const Edge<VertexType> & edge) {
        Edge<VertexType> tmp = edge;
        graph.insertVertex(tmp.getVertex()->getData());
        graph.insertEdge(last_vertex, tmp.getVertex()->getData(), tmp.getWeight());
    }

    void starting_vertex(const VertexType & vert) {
        last_vertex = vert;
    }

    void finished_traversal() {
        last_vertex = VertexType();
    }

    dGraph<VertexType> graph;
    VertexType last_vertex;

};

#endif