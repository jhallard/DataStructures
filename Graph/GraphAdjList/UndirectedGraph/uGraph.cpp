/**
*   @Author   - John H Allard Jr.
*   @File     - uGraph.h
*   @Date     - 11/12/2014
*   @Repo     - https://github.com/jhallad/DataStructures/Graph
*   @Purpose  - This is my definition of the uGraph (undirected Graph) class. This class represents a templated, 
*               undirected graph, upon which a user can perform operations like searches, path finding, minimium-cut, etc. 
*               This class was implemented as part of my C++ Data Structures personal project. All code is open license and free to use, just leave some
*               sort of note in your source code giving credit to me and a link to my github (github.com/jhallard)
*
*   @Details  - This class uses a series of adjacency lists to represent a graph data structure. An adjacency list consists of a vertex and a list 
*               of edges that eminate from this vertex to the other vertices in the map, along with the weight associated with those edges. 
*               Thus if some vertex v had edges connected it with vertices a, b, c, d, and e, the adj list for vertex v would look like :
*               v -> a* -> b* -> c* -> d* -> e* -> null
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
*               This class inherits from the pure, virtual GraphInterface class (../../GraphInterface/GraphInterface.h). This interface specifies exactly what functions
*               both the undirected and directed graph classes that I make must publically implement. This is done to help ensure that the all user interaction
*               with the graph in well planned out, consistent, and doesn't derive itself in any way from the implementation details of the graph. This should allow
*               me to make many different representations of graphs (adjlist's, adjmatrices, etc.) that can all be used in the exact same way by the user.
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
uGraph<VertexType>::uGraph() : numEdges(0), numVertices(0), connectivityCount(0), isMultiGraph(true) {
    
}

// @func  - Constructor#2
// @args  - #1 String that contains the filename from which to load a graph
// @error - Can throw IO error if invalid filename or file structure to build graph is given
template<class VertexType>
uGraph<VertexType>::uGraph(std::string fn){

// #TODO Load the file given by 'fn' into the graph.
    
}


// @func  - Destructor
// @info  - Cleans up the dynamically allocated AdjList objects contains in the list vector.
template<class VertexType>
uGraph<VertexType>::~uGraph() {
    for(int i = 0; i < list.size(); i++)
        delete(list[i]);

    list.clear();
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

    // if true then a vertex with the same data is already in our graph, so return false
    if(lookupMap.find(data) != lookupMap.end())
        return false;

    // allocate a new adjacency list on the heap for the new vertex
    AdjList<VertexType> * newList = new AdjList<VertexType>(newVertex);

    // push the new AdjList onto the vector of AdjLists
    list.push_back(newList);

    // insert the new vertex into our map for easy future lookup
    lookupMap.insert(std::pair<VertexType, AdjList<VertexType> * >(data, newList));

    // increment number of vertices
    numVertices++;

    return true;
    
}

// @func   - deleteVertices
// @args   - #1 Vector of Vertex data corresponding to the vertices to be added.
// @return - Boolean indicating success, is false if any of the individual insertions fail
template<class VertexType>
bool uGraph<VertexType>::insertVertices(std::vector<VertexType> vertices) {

    bool ret = true;

    for(int i = 0; i < vertices.size(); i++) {
        if(!this->insertVertex(vertices[i]))
            ret = false;
    }

    return ret;

}

// @func   - deleteVertices
// @args   - #1 Vector of Vertex data corresponding to the vertices to be deleted.
// @return - Boolean indicating success, is false if any of the individual deletions fail
template<class VertexType>
bool uGraph<VertexType>::deleteVertices(std::vector<VertexType> vertices) {

    bool ret = true;

    for(int i = 0; i < vertices.size(); i++) {
        if(!this->deleteVertex(vertices[i]))
            ret = false;
    }

    return ret;
}


// @func   - deleteNode
// @args   - none
// @return - Boolean indicating success
// @info   - Because this is an undirected graph, we not only have to delete the vertex in question and any edges that
//           eminate from it, but we also have to go to the other vertices and delete any edges that end at the vertex
//           to be deleted. Thankfully, because of our use of maps and pointers this isn't difficult nor too costly. Running time
//           should be O(n) where n is the number of edges that leave the vertex to be deleted.
template<class VertexType>
bool uGraph<VertexType>::deleteVertex(VertexType data) {

    AdjList<VertexType> *  adjList = this->findVertex(data);

    // if value returned in the end of the vector, the vertex doesn't exist
    if(adjList == nullptr)
        return false;

    std::vector<Edge<VertexType> *> edges = adjList->getAllEdges();


    // Here we go through all of the edges eminating from the vertex to be deleted, and delete the symmetric edges that
    // point back to this vertex to be deleted. The is a nuance of our implementation, an undirected graph in this implementation
    // consists of pairs of edges between abridged vertices with equal weights.
    for(int i = 0; i < edges.size(); i++) {

        // locate the adjacency list of the vertex on the other end of the edge from the vertex to be deleted
        AdjList<VertexType> * temp = findVertex(edges[i]->getVertex()->getData());

        if(temp == nullptr)
            continue;

        // delete that vertices edge with the vertex to be deleted
        temp->deleteEdge(data);
        
    }

    // finally remove the node for the current vertex from our map of vertices.
    typename std::unordered_map<VertexType, AdjList<VertexType> * >::iterator get = lookupMap.find(data);

    // if true then a vertex with the given data does not exist in our map, which is a problem, and means our internal structure
    // is inconsistent, we'll just return false and turn a blind eye.
    if(get == lookupMap.end())
        return false;
    else 
        lookupMap.erase(get);

    for(typename std::vector<AdjList<VertexType> *>::iterator it = list.begin() ; it != list.end(); ++it) {

        AdjList<VertexType> * adj1 = *it;

        if(adj1->getVertex()->getData() == data) {
            AdjList<VertexType> * toDelete = adj1;
            list.erase(it);
            delete(toDelete);
            break;
        }
    }        

    // decrement the number of vertices
    numVertices--;

    return true;
    
}


// @func   - insertEdge
// @args   - #1 The "From" Node, the "To" Node, the weight for this new edge 
// @return - Boolean indicating succes 
template<class VertexType>
bool uGraph<VertexType>::insertEdge(VertexType v1, VertexType v2, double weight) {

   AdjList<VertexType> *  adj1 = this->findVertex(v1);
   AdjList<VertexType> *  adj2 = this->findVertex(v2);

    // if value returned in the end of the vector, the vertex doesn't exist
    if(adj1 == nullptr || adj2 == nullptr) 
        return false;
    
    // this part makes sure we don't insert duplicate edges (edges between the same vertices even if they have different weights)
    // if we aren't specifically defined to be a multigraph
    if(!this->isMultiGraph && (adj1->getEdge(adj2->getVertex()) != nullptr || adj2->getEdge(adj1->getVertex()) != nullptr))
        return false;

    // add an edge from vertex 1 to vertex 2
    adj1->addEdge(adj2->getVertex(), weight);

    // add an edge from vertex 2 to vertex 1
    adj2->addEdge(adj1->getVertex(), weight);
    
    numEdges++; // only add 1 to the number of edges even though we added two edges to our data structure
                // this is because it's an undirected graph, so it needs edges in both directions

    return true;
    
}


// @func   - deleteEdge
// @args   - #1 The "From" Node, the "To" Node. #Note These two vertices define the edge
// @return - Boolean indicating succes 
template<class VertexType>
bool uGraph<VertexType>::deleteEdge(VertexType v1, VertexType v2) {

   AdjList<VertexType> *  adj1 = this->findVertex(v1);
   AdjList<VertexType> *  adj2 = this->findVertex(v2);

    // if value returned in the end of the vector, the vertex doesn't exist
    if(adj1 == nullptr || adj2 == nullptr)
        return false;

    // add an edge from vertex 1 to vertex 2
    adj1->deleteEdge(adj2->getVertex());

    // add an edge from vertex 2 to vertex 1
    adj2->deleteEdge(adj1->getVertex());

    numEdges--;
    

    return true;
    
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


// @func   - containsVerex
// @args   - #1 data associated with the vertex that you wish to query for existence 
// @return - Bool corresponding to the existence of a vertex with the given data in this graph
template<class VertexType>
bool uGraph<VertexType>::containsVertex(VertexType v) {

    return (nullptr != findVertex(v));
}


// @func   - getEdgeWeight
// @args   - #1 data associated with vetex #1, data associated with vertex #2
// @return - returns the weight of the edge, throws error if edge not found
// @TODO   - Figure out how to implement this without exceptions, although that would
//           most likely imply putting restrictions on the weighting (e.g. wt >= 0)
template<class VertexType>
double uGraph<VertexType>::getEdgeWeight(VertexType v1, VertexType v2) {

   AdjList<VertexType> *  adj1 = this->findVertex(v1);
   AdjList<VertexType> *  adj2 = this->findVertex(v2);

    // if value returned in the end of the vector, the vertex doesn't exist
    if(adj1 == nullptr || adj2 == nullptr)
        throw std::logic_error("Can't find Vertices in Graph");

    Edge<VertexType> * temp =  adj1->getEdge(adj2->getVertex());

    if(temp == nullptr)
        throw std::logic_error("No Edge Exists Between Given Vertices");

    return temp->getWeight();
}



// @func   - getAdjVertices
// @args   - Data contained in vertex that you wish to recieve a list of adjacent vertices of.
// @return - Vector of pairs, first item is the vertex that the edge points to, second is the weight of that edge.
template<class VertexType>
std::vector< std::pair<VertexType, double> > uGraph<VertexType>::getAdjVertices(VertexType v1){

    std::vector< std::pair<VertexType, double> > retVector;

    AdjList<VertexType> *  adj1 = findVertex(v1);

    if(adj1 == nullptr)
        return retVector;

    std::vector<Edge<VertexType> *> edgeList = adj1->getAllEdges();

    for(int i = 0; i < edgeList.size(); i++)  {
        retVector.push_back(std::pair<VertexType, double>(edgeList[i]->getVertex()->getData(), edgeList[i]->getWeight()));
    }

    return retVector;
}


// @func   - printGraph
// @args   - none
// @return - none
// @info   - prints the adjecency list representation of the graph.
template<class VertexType> void uGraph<VertexType>::printGraph() {
    
    for(int i = 0; i < list.size(); i++) {
        std::cout << "Vertex : " << list[i]->getVertex()->getData() << " -> ";

        std::vector<Edge<VertexType> *> edges = list[i]->getAllEdges(); 

        for(int j = 0; j < edges.size(); j++) {
            std::cout << edges[j]->getVertex()->getData() << ", ";
        }

        std::cout << "\n";
    }
    std::cout << "\n\n\n";
}


// @func   - isConnected
// @args   - None
// @return - Bool indicating whether or not the graph is connected
// @info   - This function searches through the given graph to see if any given vertex can be reached from any other given vertex
template<class VertexType>
bool uGraph<VertexType>::isConnected() {

    this->connectivityCount = 0;

    auto f = [](VertexType&) -> void { int x = 0; };

    this->breadthFirst(list[0]->getVertex()->getData(), f);

    return connectivityCount == list.size();
}


// @func   - depthFirst
// @args   - #1 Data associated with the starting vertex for the search, #2 function pointer that takes a set of vertex data as an argument
// @return - Bool indicating if the function could find the starting vertex based on arg#1
// @info   - Performs a depth first traversal, calling the visit() function on each item. This function assumes that all vertex data is unique,
//           so if this is a graph of strings, no two strings should be the same. This precondition allows us to use an std::unordered_map to keep
//           track of the seen and unseen vertices.
template<class VertexType>
bool uGraph<VertexType>::depthFirst(VertexType rootData, void visit(VertexType&)) {

    // Our deque object, stores the vertices as they appear to the search
    // We actually use it as a stack for this problem, by inserting and removing from the 
    // back of the queue 
    std::deque<Vertex<VertexType> *> q;

    // A map that allows us to 'mark' the vertices when they've been seen.
    // maps a set of unique vertex data to a bool that is true if that data has been seen before
    typename std::unordered_map<VertexType, bool> marked;

    AdjList<VertexType> *  rootVert = findVertex(rootData);

    if(rootVert == nullptr)
        return false;

    marked.insert(std::pair<VertexType, bool>(rootData, true));
    q.push_back(rootVert->getVertex());

    while(q.size()) {

        Vertex<VertexType> * tempVert = q.back();q.pop_back();
        AdjList<VertexType> *  adj = findVertex(tempVert->getData());

        if(adj == nullptr) 
            return false;

        connectivityCount++;

        // visit the node that we just popped off the stack
        VertexType tempData = adj->getVertex()->getData();
        visit(tempData);

        std::vector<Edge<VertexType> *> edges = adj->getAllEdges();

        for(int i = 0; i < edges.size(); i++) {

            Vertex<VertexType> * tempVert = edges[i]->getVertex();
            VertexType tempData = tempVert->getData();
            typename std::unordered_map<VertexType, bool>::const_iterator get = marked.find(tempData);

            if(get == marked.end()) {
                marked.insert(std::pair<VertexType, bool>(tempVert->getData(), true));
                q.push_back(tempVert);
            }
        }

    }

    return true;
    
}


// @func   - breadthFirst
// @args   - #1 Data associated with the starting vertex for the search, #2 function pointer that takes a set of vertex data as an argument
// @return - Bool indicating if the function could find the starting vertex based on arg#1
// @info   - Performs a breadth first traversal, calling the visit() function on each item. This function assumes that all vertex data is unique,
//           so if this is a graph of strings, no two strings should be the same. This precondition allows us to use an std::unordered_map to keep
//           track of the seen and unseen vertices.
template<class VertexType>
bool uGraph<VertexType>::breadthFirst(VertexType rootData, void visit(VertexType&)) {

    // Our queue object, stores the vertices as they appear to the search
    std::deque<Vertex<VertexType> *> q;

    // A map that allows us to 'mark' the vertices when they've been seen.
    // maps a set of unique vertex data to a bool that is true if that data has been seen before
    typename std::unordered_map<VertexType, bool> marked;

    AdjList<VertexType> *  rootVert = findVertex(rootData);

    if(rootVert == nullptr)
        return false;


    marked.insert(std::pair<VertexType, bool>(rootData, true));
    q.push_back(rootVert->getVertex());

    while(q.size()) {

        Vertex<VertexType> * tempVert = q.front();q.pop_front();
        AdjList<VertexType> *  adj = findVertex(tempVert->getData());

        connectivityCount++; // used internally

        if(adj == nullptr)
            return false;

        VertexType tempData = adj->getVertex()->getData();
        visit(tempData);

        std::vector<Edge<VertexType> *> edges = adj->getAllEdges();

        // Go through all of the edges associated with the current vertex
        for(int i = 0; i < edges.size(); i++) {

            Vertex<VertexType> * tempVert = edges[i]->getVertex();
            VertexType tempData = tempVert->getData();

            typename std::unordered_map<VertexType, bool>::const_iterator get = marked.find(tempData);

            // if the current vertex hasn't been seen
            if(get == marked.end()) {
                // mark the vertex
                marked.insert(std::pair<VertexType, bool>(tempVert->getData(), true));
                // enqueue the new vertex
                q.push_back(tempVert);
            }

        }

    }

    return true;
}


// @func   - getMinCut
// @args   - none
// @return - 2 column vector of vertices, each column representing one half of the cut. 
// @info   - Partitions the current graph into two subsets that have at the minmum number of edges between them.
template<class VertexType>
std::vector<std::vector<VertexType> > uGraph<VertexType>::getMinCut() {

    // #TODO - Implement min-cut algorithm for the graph
}

// @func   - dijkstras
// @args   - #1 Data contained in starting vertex for search, #2 Vector of possible goal vertices to reach
// @return - Vector containing, in-order, the vertices to take to reach your goal. Empty if you are there or no path exists.
// @info   - Performs Dijkstra's path-finding algorithm to get from a starting vertex to any goal vertex in a list of vertices. 
template<class VertexType>
std::vector<VertexType> uGraph<VertexType>::dijkstras(VertexType, std::vector<VertexType>) {

     // #TODO - Implement Dijkstras Path-finding algorithm
}


// @func   - aStar
// @args   - #1 Data contained in starting vertex for search, #2 Vector of possible goal vertices to reach, #3 Pointer to a hueristic function on a given node
// @return - Vector containing, in-order, the vertices to take to reach your goal. Empty if you are there or no path exists.
// @info   - Performs the A* path-finding algorithm to get from a starting vertex to any goal vertex in a list of vertices. 
template<class VertexType>
std::vector<VertexType> uGraph<VertexType>::aStar(VertexType, std::vector<VertexType>, double hueristic(VertexType&, VertexType&)) {

     // #TODO - Implement A* Path-finding algorithm

}


//////////////////////////////////////////////////////
/////////        PRIVATE FUNCTIONS    ////////////////
//////////////////////////////////////////////////////

// @func   - findVertex
// @args   - #1 Value contained in the vertex to be found
// @return - Pointer to the AdjList containing the vertex in queston. nullptr if not found (possibly should throw exception?)
// @info   - Goes through our vector of vertices and find which one (if any) contain the data given by the argument
template<class VertexType>
AdjList<VertexType> * uGraph<VertexType>::findVertex(VertexType data) {

    typename std::unordered_map<VertexType, AdjList<VertexType> * >::const_iterator get = lookupMap.find(data);

    // if true then a vertex with the given data does not exist in our map, so return nullptr.
    if(get == lookupMap.end()) 
        return nullptr;
    
    return get->second;
 }

// @func   - isConnectedHelper
// @args   - #1 Boolean, if true then the count of member is reset, else the count is incremented
// @return - integer representing the current count of objects.
// @info   - This function adds one to a counter every time it is called, it is used by the isConnected function to determine
//           if the number of vertices reached in a BFS is the same as the number of vertices in the graph.
template<class VertexType>
void uGraph<VertexType>::isConnectedHelper(VertexType&) {

    this->connectivityCount++;
}




