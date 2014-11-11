
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
	AdjList<VertexType>::AdjList(VertexType newData) : vertex(newData), pEdge(nullptr) {

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
	bool AdjList<VertexType>::setVertex(Vertex<VertexType> newData){

		this->vertex = newData;
		return true;
	}

	// @func getData
	template <class VertexType>
	Vertex<VertexType> * AdjList<VertexType>::getVertex() const{

		return this->vertex;

	}

	// @func - addEdge
    // @args - #1 Vertex that the edge points to, #2 weighting of the edge
    // @info - pusheds this edge onto the back of the edge list.
	template <class VertexType>
	bool AdjList<VertexType>::addEdge(Vertex<VertexType> * vert, double wt){

		Edge<VertexType> * newEdge = new Edge<VertexType>();
		newEdge->setVertex(vert);
		newEdge.setWeight(wt);

		if(pEdge == nullptr) {
			pEdge = newEdge;
			return true;
		}

		Edge<VertexType> * temp;
		temp = pEdge;
		while(temp.getNext() != nullptr){
			temp = temp.getNext();
		}
		
		return temp.setNext(newEdge);
	

	}

	// @func - addEdge #2
    // @args - value contained in the vertex that the new edge will point to, #2 weighting of the edge
    // @info - This function is like the one above, but we have to go search through the vertices to see which one contains the matching data, then add that vertex as an edge in the graph
	template <class VertexType>
	bool AdjList<VertexType>::addEdge(VertexType , double){

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

