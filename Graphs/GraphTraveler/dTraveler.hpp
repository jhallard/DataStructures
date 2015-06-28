/**
*   @Author   - John H Allard Jr.
*   @File     - uTraveler.h
*   @Data     - 1/2/2014
*   @Purpose  - This file defines the a testing traveler class that will process the vertices and edges as they come in.
**/

#ifndef DTRAVELER_H
#define DTRAVELER_H

template<class V> class dGraph; // forward declaring dGraph class

template<class VertexType>
class dTraveler : public GraphTraveler<VertexType>
{
public:
    ~dTraveler() {};

    // @func - discover_vertex
    // @args - #1 Data in new vertex that has been discovered
    // @info - This function is called when we jump to a new vertex without traversing an edge, e.g. if we were
    //         going through a list of vertices without consideration to their connections to one another. This
    //         function is not called for BFS/DFS where we only traverse edges to get to new vertices
    void discover_vertex(const VertexType & vert) {
        graph.insertVertex(vert);
    }

    // @func - examine_edge
    // @args - #1 The Edge object that we are currently examining.
    // @info - This function is called when we are simply looking at the edges of a given vertex. e.g. during BFS, we
    //         look at all edges incident to the current vertex and push ones we haven't seen into a queue. This
    //         function would be called during each edge examination, regardless of whether is has been looked at before.
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

    // @func - starting_vertex
    // @args - #1 The data in the first vertex to be examined.
    // @info - This function is called once per use, to register the starting vertex and prepare accordingly.
    void starting_vertex(const VertexType & vert) {
        graph.insertVertex(vert);
    }

    // @func - finished_traversal
    // @args - none
    // @info - Called after the last vertex/edge in the graph is traversed to let the user finish any calculations
    //         and clean up any allocations.
    void finished_traversal() {
    }

    dGraph<VertexType> graph;

};

#endif
