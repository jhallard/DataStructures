
	#include "AdjList.h"

    // @func - Constructor#1
    // @args - None
    // @info - Initializes everything to empty
	template <class VertexType>
	AdjList<VertexType>::AdjList() : vertex(), pEdge(nullptr){
	}

    // @func - Constructor#2
    // @args - #1 Vertex data
	template <class VertexType>
	AdjList<VertexType>::AdjList(VertexType newData) vertex(newData), pEdge(nullptr) {

	}

	// @func - Constructor#3
    // @args - #1 A vertex object to set as our vertex
	template <class VertexType>
	AdjList<VertexType>::AdjList(Vertex<VertexType> newV){
		this->vertex = newV;
		this->pEdge = nullptr;

	}

	// @func - setData
	template <class VertexType>
	bool AdjList<VertexType>::setVertex(Vertex newData){

		this->vertex = newData;
		return true;
	}

	// @func getData
	template <class VertexType>
	Vertex AdjList<VertexType>::getVertex(){

		return this->vertex;

	}

	// @func - addEdge
    // @args - #1 Vertex that the edge points to, #2 weighting of the edge
    // @info - pusheds this edge onto the back of the edge list.
	template <class VertexType>
	bool AdjList<VertexType>::addEdge(Vertex<VertexType> * , double){

	}

	// @func - deleteEdge
    // @args - #1 the data contained by the vertex that you wish to delete the edge from
    // @info - finds the vertex containing the data passed in as an argument, and deletes it from the chain.
	template <class VertexType>
	bool AdjList<VertexType>::deleteEdge(VertexType){

	}


	// @func - deleteEdge
    // @args - #1 Pointer to the vertex to be deleted.
    // @info - finds the vertex containing the data passed in as an argument, and deletes it from the chain.
	template <class VertexType>
	bool AdjList<VertexType>::deleteEdge(Vertex<VertexType> *){

	}

