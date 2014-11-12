/**
*   @Author   - John H Allard Jr.
*   @File     - uGraph.h
*   @Data     - 11/12/2014
*   @Repo     - https://github.com/jhallad/DataStructures/Graph
*   @Purpose  - This is my definition of the uGraph (undirected Graph) class defined in uGraph.h. This class represents a templated, 
*               undirected graph, upon which a user can perform operation like searches, path finding, and other things. 
*               This class was implemented as part of my C++. Data Structures personal project. All code is open license and free to use.
*
*   @Details  - This class uses an adjacency list to represent a graph data structure. An adjacency list consists of some container of vertices
*               (can be an array, list, map, I'm using a vector), and pointers from those vertices to a list of edges that eminate from them. Thus
*               if some vertex v had edges connected it with vertices a, b, c, d, and e, the adj list for vertex v would look like :
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

#ifndef U_GRAPH_A_LIST_H
#define U_GRAPH_A_LIST_H

#include <stdexcept>
#include <vector>
#include <string>
#include <stdexcept>

#include "../../GraphInterface/GraphInterface.h"
#include "../AdjacencyList/AdjList.h"
#include "../Vertex/Vertex.h"
#include "../Edge/Edge.h"


template <class VertexType> // VertexType is whatever type of data you want your vertices to hold (ints, strings, custom classes, etc.)
class uGraph : public GraphInterface <VertexType>
{


//////////////////////////////////////////////////////
////////         PUBLIC INTERFACE       //////////////
//////////////////////////////////////////////////////
public:

    // @func - Constructor#1
    // @args - None
    // @info - Initializes everything to empty
    uGraph();

    // @func  - Constructor#2
    // @args  - #1 String that contains the filename from which to load a graph
    // @error - Can throw IO error if invalid filename or file structure to build graph 
    uGraph(std::string fn);

    // @func   - insertVertex
    // @args   - #1 The value of the node to be inserted
    // @return - Boolean indicating succes 
    bool insertVertex(VertexType);

    // @func   - deleteVertex
    // @args   - none
    // @return - Boolean indicating success 
    bool deleteVertex(VertexType);

    // @func   - insertEdge
    // @args   - #1 The "From" Node, #2 the "To" Node, #3 The weight for this new edge 
    // @return - Boolean indicating succes 
    bool insertEdge(VertexType, VertexType, double = 1.0);

    // @func   - deleteEdge
    // @args   - #1 The "From" Node, the "To" Node. 
    // @return - Boolean indicating succes 
    bool deleteEdge(VertexType, VertexType);


    // @func   - getWeight
    // @args   - #1 From node, #2 "To" Node
    // @return - Double value that is the weight of the given edge
    // @throws - Exception if the given edge does not exist.
    double getWeight(VertexType, VertexType) ;

    // @func   - numVertices
    // @args   - None
    // @return - The number of vertices currently in the graph.
    int getNumVertices() const;

    // @func   - numEdges
    // @args   - None
    // @return - The number of edges currently in the graph.
    int getNumEdges() const;

    // @func   - getVerex
    // @args   - #1 data associated with the vertex that you wish to retrieve
    // @return - returns a pointer to the vertex containing the appropriate data, returns nullptr if vertex cannot be found
    Vertex<VertexType> * getVertex(VertexType);

    // @func   - getVerex
    // @args   - #1 data associated with vetex #1, data associated with vertex #2
    // @return - returns a pointer to the edge that connects the two vertices. Returns nullptr if not found
    Edge<VertexType> * getEdge(VertexType, VertexType);

    // @func   - depthFirst
    // @args   - #1 Value contained in node to be searched for
    // @return - nothing
    // @info   - Performs a depth first traversal, calling the visit() function on each item
    void depthFirst(VertexType, void visit(VertexType&));

    // @func   - breadthFirst
    // @args   - #1 Value contained in node to be searched for
    // @return - nothing
    // @info   - Performs a breadth first traversal, calling the visit() function on each item
    void breadthFirst(VertexType, void visit(VertexType&));

    // @func   - getMinCut
    // @args   - none
    // @return - 2 column vector of vertices, each column representing one half of the cut. 
    // @info   - Partitions the current graph into two subsets that have at the minmum number of edges between them.
    std::vector<std::vector<VertexType> > getMinCut();

    // @func   - aStarSearch
    // @args   - #1 Data contained in starting vertex for search, #2 Vector of possible goal vertices to reach
    // @return - Vector containing, in-order, the vertices to take to reach your goal. Empty if you are there or no path exists.
    // @info   - Performs the A* path-finding algorithm to get from a starting vertex to any goal vertex in a list of vertices. 
    std::vector<VertexType> aStarSearch(VertexType, std::vector<VertexType>);



    // ------------------------------------------------------ #TODO ------------------------------------------------------ //
    // #1 - Add Copy Constructor, this class uses pointers and dynamic memory so we will need our own copy constructor.
    // #2 - Override equals operator, check to see if two graphs are equivilent
    // ------------------------------------------------------ #TODO ------------------------------------------------------ //



//////////////////////////////////////////////////////
////////           PRIVATE DATA      /////////////////
//////////////////////////////////////////////////////
private:

    // @member - numVertices
    // @info   - Number of vertices currently in the graph
    int numVertices;

    // @member - numEdges
    // @info   - Number of Edges currently in the graph
    int numEdges;

    // @member - list
    // @info   - A vector of pointers to adjacency lists, one adjlist for each vertex in our graph. Each adjlist represents that vertex and all of the edges eminating
    //           from it to other vertices in the graph
    std::vector< AdjList<VertexType> * > list;

    // @member - isMultiGraph
    // @info   - This boolean value determines if the user is allowed to add multiple edges between the same two vertices. The default value is true.
    //           Can only be accessed indirectly through the get and set functions, if a user tries to set it to false when there are already multiple edges
    //           between vertices, the graph will go through and clean up redundant edges, saving the one with the lowest score.
    // #TODO   - Figure out how to implement this
    bool isMultiGraph;



//////////////////////////////////////////////////////
////////       PRIVATE FUNCTIONS     /////////////////
//////////////////////////////////////////////////////

    // @func   - findVertex
    // @args   - #1 Value contained in the vertex to be found
    // @return - pointer to the vertex to be found, null if not found
    // @info   - Goes through our vector of vertices and find which one (if any) contain the data given by the argument
    typename std::vector< AdjList<VertexType> * >::iterator findVertex(VertexType) ;

};

#include "uGraph.cpp"
#endif