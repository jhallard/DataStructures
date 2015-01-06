/**
*   @Author   - John H Allard Jr.
*   @File     - Edge.cpp
*   @Data     - 11/13/2014
*   @Purpose  - This is the implementation of the Edge class, which will be used by the different Graph classes in this directory.  This edge class will
*               contain a pointer to a vertex and a pointer to another edge, creating a linked list edges eminating from a source vertex to many other
*               vertices in the graph
**/

#include "Edge.h"

// @func - Constructor
// @args - #1 source vertex, #2 target vertex, #2 the weighting of the edge
template <class VertexType>
Edge<VertexType>::Edge(Vertex<VertexType> * source, Vertex<VertexType> * target, double wt) {
    this->setSource(source);
    this->setTarget(target);
    this->setWeight(wt);
    this->setNext(nullptr);

}

// @func   - getSource
// @args   - None
// @return - The vertex object pointed to by this edge. 
template <class VertexType>
Vertex<VertexType> * Edge<VertexType>::getSource() const {
    return this->source;
}

// @func   - getTarget
// @args   - None
// @return - The vertex object pointed to by this edge. 
template <class VertexType>
Vertex<VertexType> * Edge<VertexType>::getTarget() const {
    return this->target;
}

// @func   - getVertex
// @args   - None
// @return - The target vertex 
template <class VertexType>
Vertex<VertexType> * Edge<VertexType>::getVertex() const {
    return this->target;
}

// @func   - setTarget
// @args   - Pointer to the vertex that you wish to set
// @return - Bool indicating success or failure
template <class VertexType>
bool Edge<VertexType>::setTarget(Vertex<VertexType> * vert) {
    if(vert == nullptr)
        return false;

    this->target = vert;
    return true;
}

// @func   - setSource
// @args   - Pointer to the vertex that you wish to set
// @return - Bool indicating success or failure
template <class VertexType>
bool Edge<VertexType>::setSource(Vertex<VertexType> * vert) {
    if(vert == nullptr)
        return false;

    this->source = vert;
    return true;
}

// @func   - getNext
// @args   - None
// @return - The next edge in the list of outgoing edges contained by a single vertex
template <class VertexType>
Edge<VertexType> * Edge<VertexType>::getNext() const {

    return this->nextEdge;

}

// @func   - setNext
// @args   - #1 Pointer to the next Edge object
// @return - Pointless boolean indicating success
template <class VertexType>
bool Edge<VertexType>::setNext(Edge * next){

    this->nextEdge = next;
    return true;
}


// @func - setWeight 
// @arg  - #1 A double value representing the weight of the edge
// @ret  - bool indicating success
template <class VertexType>
bool Edge<VertexType>::setWeight(double wt){
    this->weight = wt;
}


// @func - getWeight 
// @arg  - none
// @ret  - the weight assocaited with this edge
template <class VertexType>
double Edge<VertexType>::getWeight() const {

    return this->weight;

}