#include "Vertex.h"

// @func - Constructor #1
// @args - none
template<class VertexType> 
Vertex<VertexType>::Vertex() : index(0) { }

// @func - Constructor #2
// @args - #1 Data associated with the vertex, #2 Index associated with the vertex
template<class VertexType> 
Vertex<VertexType>::Vertex(VertexType newdata, unsigned int newindex) : data(newdata), index(newindex) { }


// get the index of the vertex in the adjascency list or matrix
template<class VertexType> 
int Vertex<VertexType>::getIndex() const {
    return this->index;
}

// set the index of the vertex ...
template<class VertexType> 
bool Vertex<VertexType>::setIndex(unsigned int ind) {
    if(ind < 0)
        return false;
    this->index = ind;
    return true;
}

// Get the data that the vertex contains (templated)
template<class VertexType> 
VertexType Vertex<VertexType>::getData() const{
    return this->data;
}

// set the data that the vertex contains
template<class VertexType> 
bool Vertex<VertexType>::setData(VertexType newData) {
    this->data = newData;
}
