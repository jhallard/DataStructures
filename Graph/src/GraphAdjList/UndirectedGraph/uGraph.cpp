/**
*   @Author   - John H Allard Jr.
*   @File     - uGraph.cpp
*   @Data     - 11/12/2014
*   @Purpose  - This is my implementation of the uGraph (undirected Graph) class defined in uGraph.h. This class represents a templated, 
*				undirected graph, upon which a user can perform operation like searches, path finding, and other things. 
*				This class was implemented as part of my C++. Data Structures personal project. All code is open license and free to use.
*
*	@Details  - This class uses an adjacency list to represent a graph data structure. An adjacency list consists of some container of vertices
*				(can be an array, list, map, I'm using a vector), and pointers from those vertices to a list of edges that eminate from them. Thus
*				if some vertex v had edges connected it with vertices a, b, c, d, and e, the adj list for vertex v would look like
*				v -> a* -> b* -> c* -> d* -> null
*				Where x* is an edge that leads from vertex v to vertex x.
*				This above is just one adjacency list, our graph will have a single adjacency list for each vertex in the graph. So 

**/

#include "uGraph.h"


//////////////////////////////////////////////////////
//////////        PUBLIC FUNCTIONS     ///////////////
//////////////////////////////////////////////////////

// @func - Constructor#1
// @args - None
// @info - Initializes everything to empty
template<class VertexType>
uGraph<VertexType>::uGraph() : numEdges(0), numVertices(0) {
    
}

// @func  - Constructor#2
// @args  - #1 String that contains the filename from which to load a graph
// @error - Can throw IO error if invalid filename or file structure to build graph 
template<class VertexType>
uGraph<VertexType>::uGraph(std::string fn){

// #TODO Load the file given by 'fn' into the graph.
    
}

// @func   - insertNode
// @args   - #1 The value of the node to be inserted
// @return - Boolean indicating succes 
template<class VertexType>
bool uGraph<VertexType>::insertVertex(VertexType data) {

// Start by creating a new vertex
Vertex<VertexType> newVertex;

// Set the data of that vertex accordingly
if(!newVertex.setData(data))
	return false;

// allocate a new adjacency list on the heap for the new vertex
AdjList<VertexType> * newList = new AdjList<VertexType>(newVertex);

// push the new AdjList onto the vector of AdjLists
list.push_back(newList);

// increment number of vertices
numVertices++;

return true;
    
}

// @func   - deleteNode
// @args   - none
// @return - Boolean indicating succes 
template<class VertexType>
bool uGraph<VertexType>::deleteVertex(VertexType vert) {

 typename std::vector< AdjList<VertexType> * >::iterator theVertex = findVertex(vert);

 // if value returned in the end of the vector, the vertex doesn't exist
 if(theVertex == list.end())
 	return false;

 // else erase the bloody vertex
 list.erase(theVertex);

 return true;
    
}

// @func   - insertEdge
// @args   - #1 The "From" Node, the "To" Node, the weight for this new edge 
// @return - Boolean indicating succes 
template<class VertexType>
bool uGraph<VertexType>::insertEdge(VertexType v1, VertexType v2, double weight) {

	typename std::vector< AdjList<VertexType> * >::iterator vert1 = findVertex(v1);
	typename std::vector< AdjList<VertexType> * >::iterator vert2 = findVertex(v2);

	if(vert1 == list.end() || vert2 == list.end())
		return false;

	AdjList<VertexType> * adj1 = *vert1;
	AdjList<VertexType> * adj2 = *vert2;

	// add an edge from vertex 1 to vertex 2
	adj1->addEdge(adj2->getVertex(), weight);

	// add an edge from vertex 2 to vertex 1
	adj2->addEdge(adj1->getVertex(), weight);
	
	numEdges++;

	return true;
    
}

// @func   - deleteEdge
// @args   - #1 The "From" Node, the "To" Node. #Note These two vertices define the edge
// @return - Boolean indicating succes 
template<class VertexType>
bool uGraph<VertexType>::deleteEdge(VertexType v1, VertexType v2) {

	typename std::vector< AdjList<VertexType> * >::iterator vert1 = findVertex(v1);
	typename std::vector< AdjList<VertexType> * >::iterator vert2 = findVertex(v2);

	if(vert1 == list.end() || vert2 == list.end())
		return false;

	AdjList<VertexType> * adj1 = *vert1;
	AdjList<VertexType> * adj2 = *vert2;

	// add an edge from vertex 1 to vertex 2
	adj1->deleteEdge(adj2->getVertex());

	// add an edge from vertex 2 to vertex 1
	adj2->deleteEdge(adj1->getVertex());
	

	return true;
    
}


// @func   - getWeight
// @args   - #1 From node, #2 "To" Node
// @return - Boolean indicating succes 
template<class VertexType>
double uGraph<VertexType>::getWeight(VertexType v1, VertexType v2)  {

	typename std::vector< AdjList<VertexType> * >::iterator vert1 = findVertex(v1);
	typename std::vector< AdjList<VertexType> * >::iterator vert2 = findVertex(v2);

	if(vert1 == list.end() || vert2 == list.end())
		throw std::logic_error("Edge Not Found");

	AdjList<VertexType> * adj1 = *vert1;
	AdjList<VertexType> * adj2 = *vert2;

	return adj1->getEdge(adj2->getVertex())->getWeight();
    
}

// @func   - numVertices
// @args   - None
// @return - The number of vertices currently in the graph.

template<class VertexType>
int uGraph<VertexType>::getNumVertices() const {
	return numVertices;
    
}
// @func   - numEdges
// @args   - None
// @return - The number of edges currently in the graph.

template<class VertexType>
int uGraph<VertexType>::getNumEdges() const{
	return numEdges;
    
}
// @func   - depthFirst
// @args   - None
// @return - nothing
// @info   - Performs a depth first traversal, calling the visit() function on each item

template<class VertexType>
void uGraph<VertexType>::depthFirst(VertexType, void visit(VertexType&)){

	// #TODO - Perform Depth First Search
    
}

// @func   - breadthFirst
// @args   - None
// @return - nothing
// @info   - Performs a breadth first traversal, calling the visit() function on each item
template<class VertexType>
void uGraph<VertexType>::breadthFirst(VertexType, void visit(VertexType&)){

	// #TODO - Perform Breadth First Search
    
}


// @func   - getVerex
// @args   - #1 data associated with the vertex that you wish to retrieve
// @return - returns a pointer to the vertex containing the appropriate data, returns nullptr if vertex cannot be found
template<class VertexType>
Vertex<VertexType> * uGraph<VertexType>::getVertex(VertexType v) {

	typename std::vector< AdjList<VertexType> * >::iterator vert1 = findVertex(v);

	if(vert1 == list.end())
		return nullptr;

	AdjList<VertexType> * adj1 = *vert1;

	return adj1->getVertex();

}

// @func   - getEdge
// @args   - #1 data associated with vetex #1, data associated with vertex #2
// @return - returns a pointer to the edge that connects the two vertices. Returns nullptr if not found
template<class VertexType>
Edge<VertexType> * uGraph<VertexType>::getEdge(VertexType, VertexType) {

	// #TODO - Implement getEdge function, this will scan through the vertices for the two containing the data values passed in, 
	// it will check if there is an edge between these two vertices. If there is, it will reurn it, else it will return false;
}



//////////////////////////////////////////////////////
/////////        PRIVATE FUNCTIONS    ////////////////
//////////////////////////////////////////////////////

// @func   - findVertex
// @args   - #1 Value contained in the vertex to be found
// @return - pointer to the vertex to be found, null if not found
// @info   - Goes through our vector of vertices and find which one (if any) contain the data given by the argument
template<class VertexType>
typename std::vector< AdjList<VertexType> * >::iterator uGraph<VertexType>::findVertex(VertexType data) {

	typename std::vector< AdjList<VertexType> * >::iterator  it = list.begin();

	while(it != list.end())
	{
		AdjList<VertexType> * adj1 = *it;

		// We have found the correct vertex
		if(adj1->getVertex()->getData() == data)
			return it;
		it++;
	}	

	return list.end();

 }




