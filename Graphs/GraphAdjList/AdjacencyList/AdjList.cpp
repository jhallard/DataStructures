/**
*   @Author   - John H Allard Jr.
*   @File     - AdjList.cpp
*   @Data     - 11/13/2014
*   @Purpose  - This file defines the adjascency list class, which defines a vertex and all of the edges
*               that are incident to this vertex (for directed graphs, only outgoing edges). This is done
*               by storing two main pieces of data, the VertexData associated with the vertex for this
*               adjacenecy list, and a std::list object that contains a series of Edge pointers (Edge is
*               a self defined type, see Edge/Edge.h). I also recently added a hash_map over the adjacent
*               vertices for each adjacency list. This allows us to have constant look-up time to see if a
*               given edge exists, instead of having to perform a linear scan through the edges. We still
*               have to perform a linear scan to actually get the Edge from the list, because we can't map
*               to iterators. The graph classes (uGraph and dGraph) will all have a std::vector of AdjList
*               objects, representing the actual graph.
**/

#include "AdjList.h"

// @func - Constructor#1
// @args - None
// @info - Initializes everything to empty
template <class VertexType>
AdjList<VertexType>::AdjList() : vertex(), edge_list(), num_edges(0){
}

// @func - Constructor#2
// @args - #1 Vertex data
template <class VertexType>
AdjList<VertexType>::AdjList(const VertexType & newData) : vertex(newData), edge_list() {

}

// @func - Constructor#3
// @args - #1 A vertex object to set as our vertex
template <class VertexType>
AdjList<VertexType>::AdjList(const Vertex<VertexType> & newV){
    this->vertex = newV;
}


// @func - Destructor
// @args - None
// @info - Cleans up the edges allocated with new() in insertEdge function
template <class VertexType>
AdjList<VertexType>::~AdjList() {

    for(auto edge : edge_list) {
        delete(edge);
    }

    edge_list.clear();
}


// @func   - setVertex
// @args   - #1 Vertex Object
// @return - Bool indicating success or failure
template <class VertexType>
bool AdjList<VertexType>::setVertex(const Vertex<VertexType> & newData){

    this->vertex = newData;
    return true;
}

// @func   - getVertex
// @args   - None
// @return - Vertex data associated with the base of this adj. list
template <class VertexType>
Vertex<VertexType> * AdjList<VertexType>::getVertex() {
    return &(this->vertex);
}

// @func - addEdge
// @args - #1 Vertex that the edge points to, #2 weighting of the edge
// @info - pusheds this edge onto the back of the edge list.
template <class VertexType>
bool AdjList<VertexType>::addEdge(Vertex<VertexType> * vert, double wt){

    Edge<VertexType> * newEdge = new Edge<VertexType>(&this->vertex, vert, wt);

    // no self loops
    if(this->vertex.getData() == vert->getData()) {
        delete(newEdge);
        return false;
    }

    if(edge_map.find(vert->getData()) != edge_map.end()) {
        delete(newEdge);
        return false;
    }

    edge_map.insert(std::pair<VertexType, bool>(vert->getData(), true));
    edge_list.push_back(newEdge);

    return true;

}



// @func - deleteEdge
// @args - #1 the data contained by the vertex that you wish to delete the edge from
// @info - finds the vertex containing the data passed in as an argument, and deletes it from the chain.
template <class VertexType>
bool AdjList<VertexType>::deleteEdge(const VertexType & data){

    if(!edge_list.size())
        return false;

    if(edge_map.find(data) == edge_map.end()) {
        return false;
    }

    edge_map.erase(data);

    auto edge_iterator = edge_list.begin();

    for(; edge_iterator != edge_list.end(); ++edge_iterator) {

        if((*edge_iterator)->getTarget()->getData() == data) {
            delete(*edge_iterator);
            edge_list.erase(edge_iterator);
            num_edges--;
            return true;
        }
    }

    return false;
}


// @func - deleteEdge
// @args - #1 Pointer to the vertex to be deleted.
// @info - finds the vertex containing the data passed in as an argument, and deletes it from the chain.
template <class VertexType>
bool AdjList<VertexType>::deleteEdge(Vertex<VertexType> * vert){

    deleteEdge(vert->getData());

}

// @func - deleteAllEdges
// @args - None
// @info - deletes all edges ajascent to the this vertex
template <class VertexType>
bool AdjList<VertexType>::deleteAllEdges() {

    if(!edge_list.size())
        return true;

    auto edge_iterator = edge_list.begin();

    for(; edge_iterator != edge_list.end(); ++edge_iterator) {
        delete(*edge_iterator);
    }

    edge_list.clear();

    return true;
}

// @func - containsEdge
// @args - #1 Vertex data associated with the other side of the edge
// @info - true if an edge exists to the given vertex
template <class VertexType>
bool AdjList<VertexType>::containsEdge(const VertexType & data) {
    if(!edge_list.size() || edge_map.find(data) == edge_map.end()) {
        return false;
    }
    return true;
}


// @func - getEdge
// @args - #1 Pointer to the edge to be returned.
// @info - ffinds and returns the given edge if it exists
template <class VertexType>
Edge<VertexType> * AdjList<VertexType>::getEdge(const Vertex<VertexType> & vert) {

    if(!edge_list.size() || edge_map.find(vert.getData()) == edge_map.end()) {
        return nullptr;
    }

    for(auto edge : edge_list) {
        if(edge->getTarget()->getData() == vert.getData())
            return edge;
    }

    return nullptr;

}


// @func   - getAllEdges
// @args   - None
// @return - Vector of pointers to all the edge objects in the class
template <class VertexType>
std::vector<Edge<VertexType> *> AdjList<VertexType>::getAllEdges() {
    return std::vector<Edge<VertexType> *> {std::begin(edge_list), std::end(edge_list)};
}

// @func   - getEdgeList
// @args   - None
// @return - The list of edges contained in this class
template <class VertexType>
std::list<Edge<VertexType> * > * AdjList<VertexType>::getEdgeList() {
    return &edge_list;
}


// @func   - get_num_edges
// @args   - None
// @return - The number of edges connected to this particular vertex
template <class VertexType>
unsigned int AdjList<VertexType>::get_num_edges() {

    return edge_list.size();
}

// @func   - set_is_multi_graph
// @args   - boolean to be stored in is_multi_graph
// @return - Bool indicating success
template<class VertexType>
bool AdjList<VertexType>::set_is_multi_graph(bool val) {

    this->is_multi_graph = val;
    return true;
}

// @func   - get_is_multi_graph
// @args   - None
// @return - Bool value of is_multi_graph
template<class VertexType>
bool AdjList<VertexType>::get_is_multi_graph() {
    return is_multi_graph;
}


// @func   - cleanSelfLoops()
// @args   - none
// @return - bool indicating if any were found
template<class VertexType>
bool AdjList<VertexType>::removeSelfLoops() {

    bool ret = false;
    while(!this->deleteEdge(this->getVertex(), this->getVertex())) {
        ret = true;
    }

    return ret;

}
