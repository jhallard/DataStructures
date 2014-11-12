/**
*   @Author   - John H Allard Jr.
*   @File     - uGraph.h
*   @Data     - 11/12/2014
*   @Repo     - https://github.com/jhallad/DataStructures/Graph
*   @Purpose  - This is my definition of the uGraph (undirected Graph) class defined in uGraph.h. This class represents a templated, 
*               undirected graph, upon which a user can perform operation like searches, path finding, and other things. 
*               This class was implemented as part of my C++. Data Structures personal project. All code is open license and free to use.
*
*   @Details  - This class uses a series of adjacency lists to represent a graph data structure. An adjacency list consista vertex and a list 
*               of edges that eminate from this vertex to the other vertices in the map, along with the weight associated with those edges. 
*               Thus if some vertex v had edges connected it with vertices a, b, c, d, and e, the adj list for vertex v would look like :
*               v -> a* -> b* -> c* -> d* -> null
*               Where x* is an edge that leads from vertex v to vertex x. Thus to find all of the edges that eminate from a given vertex v, you just need to
*               traverse the list of edges on the AdjList that contains vertex v.
*               This above is just one adjacency list, our graph will have a single adjacency list for each vertex in the graph. So our graph data structure
*               will look more like this :
*               -----------------------------------
*             1 |   a  -> c* -> d* -> null        |
*             2 |   b  -> v* -> d* -> e* -> null  |
*             3 |   c  -> a* -> v* -> e* -> null  |
*             4 |   d  -> a* -> b* -> null        | 
*             5 |   e  -> b* -> c* -> v* -> null  |
*             6 |   v  -> b* -> c* -> null        |
*               -----------------------------------
*
*               Inheritance Hierarchy :
*               This class inherits from the pure, virtual GraphInterface class (GraphInterface/GraphInterface.h). This interface specifies exactly what functions
*               both the undirected and directed graph classes that I make must publically implement. This is done to help ensure that the all user interaction
*               with the graph in well planned out, consistent, and doesn't derive itself in any way from the implementation details of the graph. This should allow
*               me to make amny different representations of graphs (adjlist's, adjmatrices, etc.) that can all be used in the exact same way by the user.
*
*               Time Complexity :
*               Below is a break down of the time and space complexity for the various operations performed by this graph.
*               #TODO - List Big-O's for all of the important functions in this class.
**/

#include "uGraph.h"


//////////////////////////////////////////////////////
//////////        PUBLIC FUNCTIONS     ///////////////
//////////////////////////////////////////////////////

// @func - Constructor#1
// @args - None
// @info - Initializes everything to empty
template<class VertexType>
uGraph<VertexType>::uGraph() : numEdges(0), numVertices(0), isMultiGraph(true) {
    
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

 typename std::vector< AdjList<VertexType> * >::iterator theVertex = this->findVertex(vert);

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

    typename std::vector< AdjList<VertexType> * >::iterator vert1 = this->findVertex(v1);
    typename std::vector< AdjList<VertexType> * >::iterator vert2 = this->findVertex(v2);

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

    typename std::vector< AdjList<VertexType> * >::iterator vert1 = this->findVertex(v1);
    typename std::vector< AdjList<VertexType> * >::iterator vert2 = this->findVertex(v2);

    if(vert1 == list.end() || vert2 == list.end())
        return false;

    AdjList<VertexType> * adj1 = *vert1;
    AdjList<VertexType> * adj2 = *vert2;

    // add an edge from vertex 1 to vertex 2
    adj1->deleteEdge(adj2->getVertex());

    // add an edge from vertex 2 to vertex 1
    adj2->deleteEdge(adj1->getVertex());

    numEdges--;
    

    return true;
    
}


// @func   - getWeight
// @args   - #1 One Vertex of the edge in question, #2 The other vertex of teh edge in question
// @return - Boolean indicating succes 
template<class VertexType>
double uGraph<VertexType>::getWeight(VertexType v1, VertexType v2)  {

    typename std::vector< AdjList<VertexType> * >::iterator vert1 = this->findVertex(v1);
    typename std::vector< AdjList<VertexType> * >::iterator vert2 = this->findVertex(v2);

    if(vert1 == list.end() || vert2 == list.end())
        throw std::logic_error("Edge Not Found");

    AdjList<VertexType> * adj1 = *vert1;
    AdjList<VertexType> * adj2 = *vert2;

    return adj1->getEdge(adj2->getVertex())->getWeight();
    
}

// @func   - getNumVertices
// @args   - None
// @return - The number of vertices currently in the graph.
template<class VertexType>
int uGraph<VertexType>::getNumVertices() const {
    return this->numVertices;
    
}

// @func   - getNumEdges
// @args   - None
// @return - The number of edges currently in the graph.
template<class VertexType>
int uGraph<VertexType>::getNumEdges() const{
    return this->numEdges;
    
}


// @func   - getVerex
// @args   - #1 data associated with the vertex that you wish to retrieve
// @return - returns the vertex containing the appropriate data, returns nullptr if vertex cannot be found
template<class VertexType>
bool uGraph<VertexType>::containsVertex(VertexType v) {

    typename std::vector< AdjList<VertexType> * >::iterator vert1 = findVertex(v);

    return vert1 == list.end();
}

// @func   - getEdgeWeight
// @args   - #1 data associated with vetex #1, data associated with vertex #2
// @return - returns the weight of the edge, throws error if edge not found
template<class VertexType>
double uGraph<VertexType>::getEdgeWeight(VertexType v1, VertexType v2) {

    typename std::vector< AdjList<VertexType> * >::iterator vert1 = findVertex(v1);
    typename std::vector< AdjList<VertexType> * >::iterator vert2 = findVertex(v2);

    if(vert1 == list.end())
        throw std::logic_error("Edge Not Found in Graph\n");

    AdjList<VertexType> * adj1 = *vert1;
    AdjList<VertexType> * adj2 = *vert2;

    return adj1->getEdge(adj2->getVertex())->getWeight();
}



// @func   - getAdjVertices
// @args   - Data contained in vertex that you wish to recieve a list of adjacent vertices of.
// @return - Vector of pairs, first item is the vertex that the edge points to, second is the weight of that edge.
template<class VertexType>
std::vector< std::pair<VertexType, double> > uGraph<VertexType>::getAdjVertices(VertexType){

    // #TODO - return list of pairs of adj vertices and the weighting of the edge 
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


// @func   - getMinCut
// @args   - none
// @return - 2 column vector of vertices, each column representing one half of the cut. 
// @info   - Partitions the current graph into two subsets that have at the minmum number of edges between them.
template<class VertexType>
std::vector<std::vector<VertexType> > uGraph<VertexType>::getMinCut() {

    // #TODO - Implement min-cut algorithm for the graph
}


// @func   - aStarSearch
// @args   - #1 Data contained in starting vertex for search, #2 Vector of possible goal vertices to reach
// @return - Vector containing, in-order, the vertices to take to reach your goal. Empty if you are there or no path exists.
// @info   - Performs the A* path-finding algorithm to get from a starting vertex to any goal vertex in a list of vertices. 
template<class VertexType>
std::vector<VertexType> uGraph<VertexType>::aStarSearch(VertexType, std::vector<VertexType>) {

    // #TODO - Implement A* Search Algorithm
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



