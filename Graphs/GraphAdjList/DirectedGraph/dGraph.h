/**
*   @Author   - John H Allard Jr.
*   @File     - dGraph.h
*   @Date     - 11/12/2014
*   @Repo     - https://github.com/jhallard/DataStructures/Graphs
*   @Purpose  - This is my declaration of the dGraph (directed Graph) class. This class represents a templated,
*               directed graph, upon which a user can perform operation like searches, path finding, and other things.
*               This class was implemented as part of my C++. Data Structures personal project. All code is open
*               license and free to use, just leave some sort of note in your source code giving credit to me and
*               a link to my github (github.com/jhallard)
*
*   @Details  - This class uses a series of adjacency lists to represent a graph data structure. An adjacency list
*               consists of vertex and a list of edges that eminate from this vertex to the other vertices in the
*               map, along with the weight associated with those edges. Thus if some vertex v had edges connected
*               it with vertices a, b, c, d, and e, the adj list for vertex v would look like :
*               v -> a* -> b* -> c* -> d* -> null
*               Where x* is an edge that leads from vertex v to vertex x. Thus to find all of the edges that eminate
*               from a given vertex v, you just need to traverse the list of edges on the AdjList that contains vertex v.
*               This above is just one adjacency list, our graph will have a single adjacency list for each vertex in
*               the graph. So our graph data structure  will look more like this :
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
*               This class inherits from the pure, virtual GraphInterface class (GraphInterface/GraphInterface.h). This
*               interface specifies exactly what functions both the undirected and directed graph classes that I make
*               must publically implement. This is done to help ensure that the all user interaction with the graph in
*               well planned out, consistent, and doesn't derive itself in any way from the implementation details of the
*               graph. This should allow me to make amny different representations of graphs (adjlist's, adjmatrices, etc.)
*               that can all be used in the exact same way by the user.
**/

#ifndef D_GRAPH_A_LIST_H
#define D_GRAPH_A_LIST_H

#include <stdexcept>
#include <vector>
#include <string>
#include <deque>
#include <queue>
#include <unordered_map>
#include <map>
#include <set>
#include <iostream>         // needed for printGraph function..
#include <limits>
#include <random>

#include "../../GraphInterface/GraphInterface.h"
#include "../AdjacencyList/AdjList.h"
#include "../Vertex/Vertex.h"
#include "../Edge/Edge.h"
#include "../../GraphTraveler/dTraveler.hpp"
#include "../../GraphTraveler/BipartiteTraveler.hpp"

// template<class V> BipartiteTraveler;


template <class VertexType>
class dGraph : public GraphInterface <VertexType>
{
    //////////////////////////////////////////////////////
    ////////         PUBLIC INTERFACE       //////////////
    //////////////////////////////////////////////////////
public:

    // @func - Constructor#1
    // @args - None
    // @info - Initializes everything to empty
    dGraph();

    // @func  - Constructor#2
    // @args  - #1 String that contains the filename from which to load a graph
    // @error - Can throw IO error if invalid filename or file structure to build graph
    dGraph(std::string fn);

    // @func  - Copy Constructor
    // @args  - dGraph object that you wish to make this a copy of
    dGraph(const dGraph<VertexType> &);

    // @func  - Destructor
    // @info  - Cleans up the dynamically allocated AdjList objects contains in the list vector.
    virtual ~dGraph();

    // @func - destoryGraph
    // @info - deletes all internal vertices and edges, cleaning up memory in the process
    bool destroyGraph(); 

    // @func   - operator=
    // @args   - #1 constant reference to another graph object, the value of which will be placed in this graph.
    // @return - The new graph copy
    dGraph<VertexType> operator=(const dGraph<VertexType> &);

    // @func   - operator==
    // @args   - #1 constant reference to another graph object to check for equality
    // @return - True if the graphs are the same, false otherwise.
    // @TODO   - This needs to be updated, it currently only returns true if the graphs are internally represented the same, which is not true
    //           if two graphs have all the same vertices and edges but are stored in different order.
    bool operator==(const dGraph<VertexType> &);

    // @func   - operator=
    // @args   - #1 constant reference to another graph object to copy into
    // @return - The new graph copy
    bool operator!=(const dGraph<VertexType> &);

    // @func   - intersection
    // @args   - #1 constant reference to another graph
    // @return - A new dGraph that is the intersection of this graph and the argument graph
    // @info   - The intersection will return a new graph that contains only the vertices and edges that exist in both graphs.
    bool getIntersection(const dGraph<VertexType> &);

    // @func   - union
    // @args   - #1 constant reference to another graph
    // @return - A new dGraph that is the union of this graph and the argument graph
    // @info   - The union will return a new graph that contains only the vertices that are in either graphs. The new graph will also
    //           only have edges that exist in either graphs.
    bool getUnion(const dGraph<VertexType> &);


    // @func   - insertVertex
    // @args   - #1 The value of the node to be inserted
    // @return - Boolean indicating succes
    bool insertVertex(const VertexType &);

    // @func   - deleteVertex
    // @args   - none
    // @return - Boolean indicating success
    bool deleteVertex(const VertexType &);

    // @func   - getAllVertices
    // @args   - none
    // @return - Vector of the data contained inside all vertices.
    std::vector<VertexType> getAllVertices() const;

    // @func   - getAllEdges
    // @args   - none
    // @return - Vector of all of the edges in the graph
    std::vector<Edge<VertexType> > getAllEdges() const;

    // @func   - updateVertex
    // @args   - #1 - Data contained by the vertex to be updated, #2 The new data to insert into that verex
    // @return - Boolean indicating success, returns false if it can't find the vertex to update.
    bool updateVertex(const VertexType &, const VertexType &);

    // @func   - deleteVertices
    // @args   - #1 Vector of Vertex data corresponding to the vertices to be added.
    // @return - Boolean indicating succes
    bool insertVertices(std::vector<VertexType>);

    // @func   - deleteVertices
    // @args   - #1 Vector of Vertex data corresponding to the vertices to be deleted.
    // @return - Boolean indicating success
    bool deleteVertices(std::vector<VertexType>);

    // @func   - insertEdge
    // @args   - #1 The "From" Node, #2 the "To" Node, #3 The weight for this new edge
    // @return - Boolean indicating succes
    bool insertEdge(const VertexType &, const VertexType &, double = 1.0);//std::numeric_limits<double>::infinity());

    // @func   - deleteEdge
    // @args   - #1 The "From" Node, the "To" Node.
    // @return - Boolean indicating succes
    bool deleteEdge(const VertexType &, const VertexType &);

    // @func   - numVertices
    // @args   - None
    // @return - The number of vertices currently in the graph.
    int getNumVertices() const;

    // @func   - numEdges
    // @args   - None
    // @return - The number of edges currently in the graph.
    int getNumEdges() const;

    // @func   - containsVerex
    // @args   - #1 data associated with the vertex that you wish to query for existence
    // @return - Bool corresponding to the existence of a vertex with the given data in this graph
    bool containsVertex(const VertexType &);

    // @func   - containsEdge
    // @args   - #1 data associated with the 'from' vertex, #2 data associated with the 'to' vertex.
    // @return - Bool corresponding to the existence of an edge in the graph between the two vertices
    // @info   - For directed graphs, this returns true only if the edge is going from arg#1 to arg#2. For undirected
    //           graphs it will return true if an edge exists between the vertices without considering the order.
    bool containsEdge(const VertexType &, const VertexType &);

    // @func   - getEdgeWeight
    // @args   - #1 data associated with vetex #1, data associated with vertex #2
    // @return - returns the weight of the edge, throws error if edge not found
    double getEdgeWeight(const VertexType &, const VertexType &);

    // @func   - getEdgeWeight
    // @args   - #1 data associated with vetex #1, data associated with vertex #2, #3 weight to set
    // @return - returns the weight of the edge, throws error if edge not found
    bool setEdgeWeight(const VertexType &, const VertexType &, double);

    // @func   - getIncidentEdges
    // @args   - Data contained in vertex that you wish to recieve a list of adjacent vertices of.
    // @return - Vector of pairs, first item is the vertex that the edge points to, second is the weight of that edge.
    std::vector< Edge<VertexType> > getIncidentEdges(const VertexType &) const;

    // @func   - processVertex
    // @args   - #1 Data contained in vertex that you wish to process, #2 GraphTraveler object that will process the vertex and it's edges
    // @return - Bool indicating if the vertex could be found or not.
    // @info   - This function will look at the source vertex and then examine all of it's edges (by calling the traveler functions)
    bool processVertex(const VertexType &, GraphTraveler<VertexType> *) const;

    // @func   - processVertices
    // @args   - #1 Data contained in vertex that you wish to process, #2 GraphTraveler object that will process the vertex and it's edges
    // @return - Bool indicating if the vertex could be found or not.
    // @info   - This function will look at the all of the vertices in the vector and then examine all of the edges of each vertex
    //           (by calling the appropraite traveler functions)
    bool processVertices(const std::vector<VertexType> &, GraphTraveler<VertexType> *) const;

    // @func   - makeGraphDense
    // @args   - A function that takes two vertices and assigns a weight to their edge
    // @return - Bool indicating success
    // @info   - This function removes all current edes from the graph, and instead makes a dense graph out of the current
    //           vertices with uniform edge weighting specified by the argument to the function.
    bool makeGraphDense(double setWeight(VertexType&, VertexType&) = nullptr);

    // @func   - reverse
    // @args   - none
    // @return - Bool indicating success
    // @info   - This function switches the direction of all edges
    bool reverse();

    // @func   - invert
    // @args   - #1 Weighing function that takes in two vertices and assigns a weight to an edge between them
    // @return - Bool indicating success
    // @info   - This function inverts the current graph, which means it removes all existing edges and emplaces all possible edges
    //           that didn't already exist.
    bool invert(double setWeight(VertexType&, VertexType&) = nullptr);

    // @func   - printGraph
    // @args   - none
    // @return - none
    // @info   - prints the adjecency list representation of the graph to the console.
    void printGraph() const;

    // @func   - isConnected
    // @args   - None
    // @return - Bool indicating whether or not the graph is connected
    // @info   - This function uses BFS to search to see if any given vertex can be reached from any other given vertex
    bool isConnected();

    // @func   - isBipartite
    // @args   - None
    // @return - Bool indicating whether or not the graph is bipartite
    // @info   - This function uses BFS, marking every other vertex a 0 or 1, and checking if it can reach all vertices without
    //           hitting the same value twice in a row.
    bool isBipartite();

    // @func   - getBipartition
    // @args   - std::pair pointer that will be filled with two vectors of vertices, consisting of one bipartition of the graph
    // @return - Bool indicating whether or not the graph is bipartite and able to be bipartitioned
    bool getBipartition(std::pair<std::vector<VertexType>, std::vector<VertexType> > *);

    // @func   - set_is_multi_graph
    // @args   - boolean to be stored in is_multi_graph
    // @return - Bool indicating success
    bool set_is_multi_graph(bool);

    // @func   - get_is_multi_graph
    // @args   - None
    // @return - Bool value of is_multi_graph
    bool get_is_multi_graph();

    // @func   - depthFirst
    // @args   - #1 Data associated with the starting vertex for the search, #2 Traveler class to process the graph components as they're discovered.
    // @return - Bool indicating if the function could find the starting vertex based on arg#1
    // @info   - Performs a depth first traversal, calling the appropraite function inside of the Traveler class when it encounters a new vertex or edge.
    //           This function assumes that all vertex data is unique, so if this is a graph of strings, no two strings should be the same.
    //           This precondition allows us to use an std::unordered_map to keep track of the seen and unseen vertices.
    bool depthFirst(const VertexType &, GraphTraveler<VertexType> * = nullptr);

    // @func   - breadthFirst
    // @args   - #1 Data associated with the starting vertex for the search,  #2 Traveler class to process the graph components as they're discovered.
    // @return - Bool indicating if the function could find the starting vertex based on arg#1
    // @info   - Performs a breadth first traversal, calling the appropraite function inside of the Traveler class when it encounters
    //           a new vertex or edge. This function assumes that all vertex data is unique, so if this is a graph of strings, no two
    //           strings should be the same. This precondition allows us to use an std::unordered_map to keep track of the seen and
    //           unseen vertices.
    bool breadthFirst(const VertexType &, GraphTraveler<VertexType> * = nullptr);

    // @func   - minimuminCut
    // @args   - none
    // @return - 2 column vector of vertices, each column representing one half of the cut.
    // @info   - Partitions the current graph into two subsets that have at the minmum number of edges between them.
    std::vector<std::vector<VertexType> > minimumCut();

    // @func   - minimuminSpanningTree
    // @args   - none
    // @return - Boolean that indicates if the minimum tree could be traversed or not, false if the graph is not strongly-connected
    // @info   - This function will traverse the graph is such an order as to build a minimum spanning tree,
    bool minimumSpanningTree(GraphTraveler<VertexType> * = nullptr);

    // @func   - dijkstrasMinimumTree
    // @args   - #1 Data contained in starting vertex for search, #2 optional destination vertex, if null we will find the path to every node
    //           otherwise we stop when we find the destination node
    // @return - A pair containing two maps. The first map takes a vertex and returns the previuos vertex in the path there from the source vertex.
    //           The second map takes a vertex and gives the total weight that it takes to get there from the source vertex.
    // @info   - Performs Dijkstra's path-finding algorithm to get from a starting vertex to any goal vertex in the map, throws an exception if
    //           the source vertex is not contained in the map.
    typename dGraph<VertexType>::dist_prev_pair * dijkstrasMinimumTree(const VertexType &,const  VertexType * = nullptr);

    // @func   - dijkstrasMinimumPath
    // @args   - #1 Source Vertex, #2 Dest Vertex, #3 the GraphTraveler-derived object that will recieve the vertices and edges in minimum order
    // @return - bool indicating success, will return false for graphs with no connection between src and dest vertices.
    // @info   - This function is intended for the user to call to compute the shortest path between any two vertices. This function calls
    //           the dijkstras(...) function and decodes the output to give the user the specific path they are looking for, as opposed to a
    //           structure that contains the shortest path from the source vertex to any vertex in the map.
    bool dijkstrasShortestPath(const VertexType &, const VertexType &, GraphTraveler<VertexType> * = nullptr);


    // @func   - aStar
    // @args   - #1 Data contained in starting vertex for search, #2 Vector of possible goal vertices to reach, #3 Pointer
    //           to a hueristic function on a given node
    // @return - Vector containing, in-order, the vertices to take to reach your goal. Empty if you are there or no path exists.
    // @info   - Performs the A* path-finding algorithm to get from a starting vertex to any goal vertex in a list of vertices.
    std::vector<VertexType> aStar(const VertexType &, std::vector<VertexType>, double hueristic(VertexType&, VertexType&));



    //////////////////////////////////////////////////////
    ////////           PRIVATE DATA      /////////////////
    //////////////////////////////////////////////////////
private:

    // @member - num_vertices
    // @info   - Number of vertices currently in the graph
    int num_vertices;

    // @member - num_edges
    // @info   - Number of Edges currently in the graph
    int num_edges;

    // @member - is_multi_graph
    // @info   - This is intended to be used by the minimumCut function, because it requires that duplicate edges be valid. Setting this to true
    //           will change the AdjList class to not reject duplicate edges, but it will still reject edges between the same vertex.
    bool is_multi_graph;

    // @member - list
    // @info   - A vector of pointers to adjacency lists, one adjlist for each vertex in our graph. Each adjlist represents
    //           that vertex and all of the edges eminating from it to other vertices in the graph
    std::vector< AdjList<VertexType> * > list;

    // @member - lookup_map
    // @info   - Allows us to look up where in our vector of vertices a vertex with a given set of VertexData is. This allows us to
    //           have an (amortized) O(1) lookup time to find a Vertex given a piece of VertexData, as apposed to scanning linearly
    //           through our vector of AdjLists.
    //           KeyType - VertexData (int, string, double, etc. Chosen at runtime by the user)
    //           Value   - A pointer to the AdjList object for the Vertex that contains the data contained by the key.
    std::unordered_map<VertexType,  AdjList<VertexType> *> lookup_map;

    // @typedef - (too long to retype)
    // @info    - This is a pair of unordered_maps that is returned from the dijkstras algorithm to the helper function. Contained
    //            inside these two maps is both the shortest path from the source vertex to any other node in the graph, and the net
    //            weight along that path. These two maps are decoded inside the helper function to return a single shortest path
    //            between two vertices, so the user doesn't have to decode it themselves.
    // typedef std::pair<std::unordered_map<VertexType, VertexType>, std::unordered_map<VertexType, double> > dist_prev_pair;
    typedef std::pair<std::unordered_map<VertexType, VertexType>, std::unordered_map<VertexType, double> > dist_prev_pair;



    //////////////////////////////////////////////////////
    ////////       PRIVATE FUNCTIONS     /////////////////
    //////////////////////////////////////////////////////

    // @func   - findVertex
    // @args   - #1 Value contained in the vertex to be found
    // @return - pointer to the vertex to be found, null if not found
    // @info   - Goes through our vector of vertices and find which one (if any) contain the data given by the argument
    AdjList<VertexType> *  findVertex(const VertexType &) const;


};

#include "dGraph.cpp"
#endif
