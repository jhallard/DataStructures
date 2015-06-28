/**
*   @Author   - John H Allard Jr.
*   @File     - dGraph.cpp
*   @Date     - 11/12/2014
*   @Repo     - https://github.com/jhallard/DataStructures/Graphs
*   @Purpose  - This is my definition of the dGraph (directed Graph) class. This class represents a templated,
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


#include "dGraph.h"


//////////////////////////////////////////////////////
//////////        PUBLIC FUNCTIONS     ///////////////
//////////////////////////////////////////////////////

// @func - Constructor#1
// @args - None
// @info - Initializes everything to empty
template<class VertexType>
dGraph<VertexType>::dGraph() : num_edges(0), num_vertices(0) {

}

// @func  - Constructor#2
// @args  - #1 String that contains the filename from which to load a graph
// @error - Can throw IO error if invalid filename or file structure to build graph is given
template<class VertexType>
dGraph<VertexType>::dGraph(std::string fn){

// #TODO Load the file given by 'fn' into the graph.

}

// @func  - Copy Constructor
// @args  - #1 uGraph object that you wish to make this a copy of
template<class VertexType>
dGraph<VertexType>::dGraph(const dGraph<VertexType> & toCopy) {

    auto ourVertices = getAllVertices();
    // Go through, delete, and clean up all vertices and edges.z
    for(auto i : ourVertices) {
        deleteVertex(i);
    }

    list.clear();

    num_vertices = 0;
    num_edges = 0;

    auto theirVertices = toCopy.getAllVertices();
    for(auto i : theirVertices) {
        auto edges = toCopy.getIncidentEdges(i);
        insertVertex(i);

        for(auto edge : edges) {
            insertEdge(i, edge.getTarget()->getData(), edge.getWeight());
        }
    }
}


// @func  - Destructor
// @info  - Cleans up the dynamically allocated AdjList objects contains in the list vector.
template<class VertexType>
dGraph<VertexType>::~dGraph() {
    for(int i = 0; i < list.size(); i++) {
        delete(list[i]);
    }

    list.clear();
}

// @func   - operator=
// @args   - #1 constant reference to another graph object to copy into
// @return - The new graph copy
template<class VertexType>
dGraph<VertexType> dGraph<VertexType>::operator=(const dGraph<VertexType> & toCopy) {

    auto ourVertices = getAllVertices();
    // Go through, delete, and clean up all vertices and edges.z
    for(auto i : ourVertices) {
        deleteVertex(i);
    }

    list.clear();

    num_vertices = 0;
    num_edges = 0;
    auto theirVertices = toCopy.getAllVertices();

    for(auto i : theirVertices) {
        insertVertex(i);
    }

    for(auto i : theirVertices) {
        auto edges = toCopy.getIncidentEdges(i);

        for(auto edge : edges) {
            insertEdge(i, edge.getTarget()->getData(), edge.getWeight());
        }
    }

    return *this;
}

// @func   - operator==
// @args   - #1 constant reference to another graph object to compare to this one
// @return - True if the graphs are the same, that is they have all of the same vertices and edges between vertices, including indentical weights.
// @info   - This is currently not a 100% correct implementation, it will only return true if all vertices are the same and stored internally in the same
//           order, same with the adjacent edges for each vertex. To fix this, we need to hash all vertices for comparison.
template<class VertexType>
bool dGraph<VertexType>::operator==(const dGraph<VertexType> & toCopy) {

    auto our_vertices = getAllVertices();

    auto their_vertices = toCopy.getAllVertices();

    if(our_vertices.size() != their_vertices.size())
        return false;

    for(int i = 0; i < our_vertices.size(); i++) {
        if(our_vertices[i] != their_vertices[i])
            return false;

        auto our_edges = getIncidentEdges(our_vertices[i]);
        auto their_edges = toCopy.getIncidentEdges(their_vertices[i]);

        if(our_edges != their_edges)
            return false;
    }

    return true;
}

// @func   - operator!=
// @args   - #1 constant reference to another graph object to compare to this one
// @return - True if they are not the same, false otherwise
template<class VertexType>
bool dGraph<VertexType>::operator!=(const dGraph<VertexType> & toCopy) {

    return !(operator==(toCopy));
}

// @func   - getIntersection
// @args   - #1 constant reference to another graph
// @return - A new dGraph that is the intersection of this graph and the argument graph
// @info   - The intersection will return a new graph that contains only the vertices that are in both graphs. The new graph will also
//           only have edges that exist in both graphs.
template<class VertexType>
bool dGraph<VertexType>::getIntersection(const dGraph<VertexType> & other_graph) {

    std::unordered_map<VertexType, int> vertex_map;
    std::vector<VertexType> common_vertices;
    dGraph<VertexType> new_graph;

    // map all of our vertices
    for(auto & vertex : getAllVertices()) {
        vertex_map.insert(std::make_pair(vertex, 1));
    }

    // map all of their vertices that intersect with our vertices
    for(auto & vertex : other_graph.getAllVertices()) {
        if(vertex_map.find(vertex) != vertex_map.end()) {
            vertex_map.at(vertex) = 2;
        }
    }

    // get all of the intersected vertices
    for(auto pair : vertex_map) {
        if(pair.second == 2) {
            common_vertices.push_back(pair.first);
            new_graph.insertVertex(pair.first);
        }
    }

    // add all of the intersected edges
    for(auto vertex : common_vertices) {
        for(auto edge : getIncidentEdges(vertex)) {
            if(other_graph.containsEdge(vertex, edge.getTarget())) {
                new_graph.insertEdge(vertex, edge.getTarget(), edge.getWeight());
            }
        }
    }

    *this = new_graph;


    return true;
}

// @func   - getUnion
// @args   - #1 constant reference to another graph
// @return - A new dGraph that is the union of this graph and the argument graph
// @info   - The union will return a new graph that contains only the vertices that are in either graphs. The new graph will also
//           only have edges that exist in either graphs.
template<class VertexType>
bool dGraph<VertexType>::getUnion(const dGraph<VertexType> & other_graph) {

    for(auto vertex : other_graph.getAllVertices()) {
        insertVertex(vertex);
        for(auto edge: other_graph.getIncidentEdges(vertex)) {
            insertEdge(edge.getSource()->getData(), edge.getTarget()->getData(), edge.getWeight());
        }
    }

    return true;
}


// @func   - insertNode
// @args   - #1 The value of the node to be inserted
// @return - Boolean indicating succes
template<class VertexType>
bool dGraph<VertexType>::insertVertex(const VertexType & data) {

    // Start by creating a new vertex
    Vertex<VertexType> newVertex;

    // Set the data of that vertex accordingly
    if(!newVertex.setData(data))
        return false;

    // if true then a vertex with the same data is already in our graph, so return false
    if(lookup_map.find(data) != lookup_map.end())
        return false;

    // allocate a new adjacency list on the heap for the new vertex
    AdjList<VertexType> * newList = new AdjList<VertexType>(newVertex);

    // push the new AdjList onto the vector of AdjLists
    list.push_back(newList);

    // insert the new vertex into our map for easy future lookup
    lookup_map.insert(std::pair<VertexType, AdjList<VertexType> * >(data, newList));

    // increment number of vertices
    num_vertices++;

    return true;

}

// @func   - deleteVertices
// @args   - #1 Vector of Vertex data corresponding to the vertices to be added.
// @return - Boolean indicating success, is false if any of the individual insertions fail
template<class VertexType>
bool dGraph<VertexType>::insertVertices(std::vector<VertexType> vertices) {

    bool ret = true;

    for(int i = 0; i < vertices.size(); i++) {
        if(!insertVertex(vertices[i]))
            ret = false;
    }

    return ret;

}

// @func   - deleteVertices
// @args   - #1 Vector of Vertex data corresponding to the vertices to be deleted.
// @return - Boolean indicating success, is false if any of the individual deletions fail
template<class VertexType>
bool dGraph<VertexType>::deleteVertices(std::vector<VertexType> vertices) {

    bool ret = true;

    for(int i = 0; i < vertices.size(); i++) {
        if(!deleteVertex(vertices[i]))
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
bool dGraph<VertexType>::deleteVertex(const VertexType & data) {

    AdjList<VertexType> *  adjList = findVertex(data);

    if(adjList == nullptr)
        return false;

    std::vector<Edge<VertexType> *> edges = adjList->getAllEdges();

    int numEdgesToDelete = edges.size();

    // Go through the entire graph and delete all edges that point to the vertex to be deleted
    for(auto i : list) {
        if(i->containsEdge(data)) {
            i->deleteEdge(data);
            numEdgesToDelete++;
        }
    }


    // finally remove the node for the current vertex from our map of vertices.
    typename std::unordered_map<VertexType, AdjList<VertexType> * >::iterator get = lookup_map.find(data);

    // if true then a vertex with the given data does not exist in our map, which is a problem, and means our internal structure
    // is inconsistent, we'll just return false and turn a blind eye.
    if(get == lookup_map.end())
        return false;
    else
        lookup_map.erase(get);

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
    num_vertices--;

    // decrement the number of edges by the number of edges that were attached to the vertex we just destroyed.
    num_edges -= numEdgesToDelete;

    return true;

}


// @func   - insertEdge
// @args   - #1 The "From" Node, the "To" Node, the weight for this new edge
// @return - Boolean indicating succes
template<class VertexType>
bool dGraph<VertexType>::insertEdge(const VertexType & v1, const VertexType & v2, double weight) {

    // This assumes we don't want edges between the same vertex
    if(v1 == v2) {
        return false;
    }

   AdjList<VertexType> *  adj1 = findVertex(v1);
   AdjList<VertexType> *  adj2 = findVertex(v2);

    if(adj1 == nullptr || adj2 == nullptr)
        return false;

    // add an edge from vertex 1 to vertex 2
    if(adj1->addEdge(adj2->getVertex(), weight)) {
        num_edges++;
        return true;
    }

    return false;

}


// @func   - deleteEdge
// @args   - #1 The "From" Node, the "To" Node. #Note These two vertices define the edge
// @return - Boolean indicating succes
template<class VertexType>
bool dGraph<VertexType>::deleteEdge(const VertexType & v1, const VertexType & v2) {

   AdjList<VertexType> *  adj1 = findVertex(v1);
   AdjList<VertexType> *  adj2 = findVertex(v2);

    if(adj1 == nullptr || adj2 == nullptr)
        return false;

    // delete an edge from vertex 1 to vertex 2
    if(!adj1->deleteEdge(adj2->getVertex())) {
        return false;
    }

    num_edges--;
    return true;

}

// @func   - getAllVertices
// @args   - none
// @return - Vector of the data contained inside all vertices.
template<class VertexType>
std::vector<VertexType> dGraph<VertexType>::getAllVertices() const{
    std::vector<VertexType> ret;
    for(auto i : list)
        ret.push_back(i->getVertex()->getData());

    return ret;
}

// @func   - getAllEdges
// @args   - none
// @return - Vector of all of the edges in the graph
template<class VertexType>
std::vector<Edge<VertexType> > dGraph<VertexType>::getAllEdges() const {

    std::vector<Edge<VertexType> > edge_list;

    for(auto vertex : list) {

        for(auto edge : vertex->getAllEdges()) {
            edge_list.push_back(*edge);
        }
    }

    return edge_list;
}


// @func   - getNumVertices
// @args   - None
// @return - The number of vertices currently in the graph.
template<class VertexType>
int dGraph<VertexType>::getNumVertices() const {

    return num_vertices;
}


// @func   - getNumEdges
// @args   - None
// @return - The number of edges currently in the graph.
template<class VertexType>
int dGraph<VertexType>::getNumEdges() const{

    return num_edges;
}


// @func   - containsVerex
// @args   - #1 data associated with the vertex that you wish to query for existence
// @return - Bool corresponding to the existence of a vertex with the given data in this graph
template<class VertexType>
bool dGraph<VertexType>::containsVertex(const VertexType & v) {

    return (nullptr != findVertex(v));
}

// @func   - containsEdge
// @args   - #1 data associated with the 'from' vertex, #2 data associated with the 'to' vertex.
// @return - Bool corresponding to the existence of an edge in the graph between the two vertices
// @info   - For directed graphs, this returns true only if the edge is going from arg#1 to arg#2. For undirected
//           graphs it will return true if an edge exists between the vertices without considering the order.
template<class VertexType>
bool dGraph<VertexType>::containsEdge(const VertexType & src_vert, const VertexType & dest_vert) {

    // check if the src vertex exists, if so check if it has an edge to the dest vertex
    return (findVertex(src_vert) == nullptr)? false : findVertex(src_vert)->containsEdge(dest_vert);
}


// @func   - getEdgeWeight
// @args   - #1 data associated with vetex #1, data associated with vertex #2
// @return - returns the weight of the edge, throws error if edge not found
// @TODO   - Figure out how to implement this without exceptions, although that would
//           most likely imply putting restrictions on the weighting (e.g. wt >= 0)
template<class VertexType>
double dGraph<VertexType>::getEdgeWeight(const VertexType & v1, const VertexType & v2) {

   AdjList<VertexType> *  adj1 = findVertex(v1);
   AdjList<VertexType> *  adj2 = findVertex(v2);

    if(adj1 == nullptr || adj2 == nullptr)
        throw std::logic_error("Can't find Vertices in Graph");

    Edge<VertexType> * temp =  adj1->getEdge(*adj2->getVertex());

    if(temp == nullptr)
        throw std::logic_error("No Edge Exists Between Given Vertices");

    return temp->getWeight();
}

// @func   - setEdgeWeight
// @args   - #1 data associated with source vetex, #2 data associated with destination vertex, #3 new weight to be set
// @return - returns the true if we succeed in changing the value for both edges (undirected graph has edges going both ways)
template<class VertexType>
bool dGraph<VertexType>::setEdgeWeight(const VertexType & src_vert, const VertexType & dest_vert, double weight) {

    AdjList<VertexType> *  adj1 = findVertex(src_vert);
    AdjList<VertexType> *  adj2 = findVertex(dest_vert);

    if(adj1 == nullptr || adj2 == nullptr)
        return false;

    Edge<VertexType> * edge1 = adj1->getEdge(dest_vert);

    if(edge1 == nullptr)
        return false;

    return edge1->setWeight(weight);
}



// @func   - getIncidentEdges
// @args   - Data contained in vertex that you wish to recieve a list of adjacent vertices of.
// @return - Vector of pairs, first item is the vertex that the edge points to, second is the weight of that edge.
template<class VertexType>
std::vector<Edge<VertexType> > dGraph<VertexType>::getIncidentEdges(const VertexType & v1) const{

    std::vector< Edge<VertexType> > retVector;

    AdjList<VertexType> *  adj1 = findVertex(v1);

    if(adj1 == nullptr)
        throw std::logic_error("getIncidentEdges() | Error : Vertex not found in graph\n");

    std::vector<Edge<VertexType> *> edgeList = adj1->getAllEdges();

    for(auto edge : edgeList)  {
       retVector.push_back(*edge);
    }

    return retVector;
}

// @func   - processVertex
// @args   - #1 Data contained in vertex that you wish to process, #2 GraphTraveler object that will process the vertex and it's edges
// @return - VBool indicating if the vertex could be found or not.
// @info   - This function will look at the source vertex and then examine all of it's edges (by calling the traveler functions)
template<class VertexType>
bool dGraph<VertexType>::processVertex(const VertexType & source, GraphTraveler<VertexType> * traveler) const {

    auto adj_list = findVertex(source);

    if(!adj_list || !traveler) {
        return false;
    }

    traveler->starting_vertex(source);

    for(auto edge : adj_list->getAllEdges()) {
        traveler->examine_edge(*edge);
    }

    traveler->finished_traversal();
    return true;
}

// @func   - processVertices
// @args   - #1 Data contained in vertex that you wish to process, #2 GraphTraveler object that will process the vertex and it's edges
// @return - Bool indicating if the vertex could be found or not.
// @info   - This function will look at the all of the vertices in the vector and then examine all of the edges of each vertex
//           (by calling the appropraite traveler functions)
template<class VertexType>
bool dGraph<VertexType>::processVertices(const std::vector<VertexType> & vertices, GraphTraveler<VertexType> * traveler) const {

    if(!traveler || !vertices.size())
        return false;

    traveler->starting_vertex(vertices[0]);

    for(auto vertex : vertices) {

        auto adj_list = findVertex(vertex);

        if(!adj_list) {
            return false;
        }

        traveler->discover_vertex(adj_list->getVertex()->getData());

        for(auto edge : adj_list->getAllEdges()) {
            traveler->examine_edge(*edge);
        }
    }

    traveler->finished_traversal();
    return true;
}

// @func   - makeGraphDense
// @args   - #1 A function that takes two vertices and assigns a weight to their edge
// @return - Bool indicating success
// @info   - This function removes all current edes from the graph, and instead makes a dense graph out of the current vertices with uniform
//           edge weighting specified by the argument to the function.
template<class VertexType>
bool dGraph<VertexType>::makeGraphDense(double setWeight(VertexType&, VertexType&)) {

    for(auto vertex : list)
        vertex->deleteAllEdges();

    for(int i = 0; i < list.size(); i++) {
        for(int j = 0; j < list.size(); j++) {
            insertEdge(list[i]->getVertex()->getData(), list[j]->getVertex()->getData());
        }
    }

    return true;
}

// @func   - reverse
// @args   - none
// @return - Bool indicating success
// @info   - This function switches the direction of all edges
template<class VertexType>
bool dGraph<VertexType>::reverse() {

    dGraph<VertexType> temp_graph;
    for(auto i : list)
        temp_graph.insertVertex(i->getVertex()->getData());

    for(auto i : list) {
        for(auto j : i->getAllEdges()) {
            temp_graph.insertEdge(j->getVertex()->getData(), i->getVertex()->getData(), j->getWeight());
        }
    }

    *this = temp_graph;
    return true;
}

// @func   - invert
// @args   - #1 Weighing function that takes in two vertices and assigns a weight to an edge between them
// @return - Bool indicating success
// @info   - This function inverts the current graph, which means it removes all existing edges and emplaces all possible edges
//           that didn't already exist.
template<class VertexType>
bool dGraph<VertexType>::invert(double setWeight(VertexType&, VertexType&)) {

    dGraph<VertexType> temp_graph;
    double weight = std::numeric_limits<double>::infinity();

    for(auto vert : list)
        temp_graph.insertVertex(vert->getVertex()->getData());

    for(int i = 0; i < list.size(); i++) {
        VertexType data1 = list[i]->getVertex()->getData();

        for(int j = 0; j < list.size(); j++) {
            VertexType data2 = list[j]->getVertex()->getData();
            (setWeight == nullptr)? weight = std::numeric_limits<double>::infinity() : weight = setWeight(data1, data2);

            if(!containsEdge(data1, data2))
                temp_graph.insertEdge(data1, data2);
        }
    }

    *this = temp_graph;
    return true;
}


// @func   - printGraph
// @args   - none
// @return - none
// @info   - prints the adjecency list representation of the graph.
template<class VertexType>
void dGraph<VertexType>::printGraph() const {

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
bool dGraph<VertexType>::isConnected() {

    dGraph<VertexType> temp_graph = *this;

    dTraveler<VertexType> * trav = new dTraveler<VertexType>();
    dTraveler<VertexType> * trav2 = new dTraveler<VertexType>();

    depthFirst(list[0]->getVertex()->getData(), trav);//, f);

    if(trav->graph.getNumVertices() != list.size())
        return false;

    temp_graph.reverse();

    temp_graph.depthFirst(list[0]->getVertex()->getData(), trav2);

    bool ret = (trav2->graph.getNumVertices() == list.size());

    delete(trav);
    delete(trav2);

    return ret;
}

// @func   - isBipartite
// @args   - None
// @return - Bool indicating whether or not the graph is bipartite
// @info   - This function uses BFS, marking every other vertex a 0 or 1, and checking if it can reach all vertices without
//           hitting the same value twice in a row.
template<class VertexType>
bool dGraph<VertexType>::isBipartite() {

    BipartiteTraveler<VertexType> * traveler = new BipartiteTraveler<VertexType>();

    depthFirst(list[0]->getVertex()->getData(), traveler);

    bool ret = traveler->is_bipartite;
    delete(traveler);

    return ret;
}

// @func   - Bipartition
// @args   - std::pair pointer that will be filled with two vectors of vertices, consisting of one bipartition of the graph
// @return - Bool indicating whether or not the graph is bipartite and able to be bipartitioned
template<class VertexType>
bool dGraph<VertexType>::getBipartition(std::pair<std::vector<VertexType>, std::vector<VertexType> > * ret) {

    BipartiteTraveler<VertexType> * traveler = new BipartiteTraveler<VertexType>();

    depthFirst(list[0]->getVertex()->getData(), traveler);

    if(!traveler->is_bipartite)
        return false;

    std::vector<VertexType> u_vertices, v_vertices;

    for(auto vertex : traveler->vertex_colors) {
        if(vertex.second)
            u_vertices.push_back(vertex.first);
        else
            v_vertices.push_back(vertex.first);
    }

    ret->first = u_vertices;
    ret->second = v_vertices;

    delete(traveler);

    return true;
}


// @func   - set_is_multi_graph
// @args   - boolean to be stored in is_multi_graph
// @return - Bool indicating success
template<class VertexType>
bool dGraph<VertexType>::set_is_multi_graph(bool val) {

    is_multi_graph = val;

    for(auto i : list) {
        i->set_is_multi_graph(val);
    }

    return true;
}

// @func   - get_is_multi_graph
// @args   - None
// @return - Bool value of is_multi_graph
template<class VertexType>
bool dGraph<VertexType>::get_is_multi_graph() {
    return is_multi_graph;
}


// @func   - depthFirst
// @args   - #1 Data associated with the starting vertex for the search, #2 Traveler class to process the graph components
//           as they're discovered.
// @return - Bool indicating if the function could find the starting vertex based on arg#1
// @info   - Performs a depth first traversal, calling the appropraite function inside of the Traveler class when it
//           encounters a new vertex or edge. This function assumes that all vertex data is unique, so if this is a
//           graph of strings, no two strings should be the same. This precondition allows us to use an std::unordered_map
//           to keep track of the seen and unseen vertices.
template<class VertexType>
bool dGraph<VertexType>::depthFirst(const VertexType & root_data, GraphTraveler<VertexType> * traveler) {

    // Our deque object, stores the vertices as they appear to the search
    // We actually use it as a stack for this problem, by inserting and removing from the
    // back of the queue
    std::deque<Vertex<VertexType> *> q;

    // A map that allows us to 'mark' the vertices when they've been seen.
    // maps a set of unique vertex data to a bool that is true if that data has been seen before
    typename std::unordered_map<VertexType, bool> marked;

    // Maps a target vertex that is examined to the source vertex that we were at when we examined it
    typename std::unordered_map<VertexType, VertexType> prev;

    AdjList<VertexType> * root_vert = findVertex(root_data);

    if(root_vert == nullptr)
        return false;

    marked.insert(std::pair<VertexType, bool>(root_data, true));
    q.push_back(root_vert->getVertex());

    AdjList<VertexType> *  current_vertex = nullptr;
    bool first_iteration = true;

    while(q.size()) {

        Vertex<VertexType> * tempVert = q.back();q.pop_back();
        current_vertex = findVertex(tempVert->getData());

        if(current_vertex == nullptr)
            return false;

        // visit the node that we just popped off the stack
        VertexType tempData = current_vertex->getVertex()->getData();

        // visit the new vertex
        if(traveler && first_iteration) {
            traveler->starting_vertex(root_vert->getVertex()->getData());
            first_iteration = false;
        }
        else if(traveler) {
            AdjList<VertexType> * last_vertex = findVertex(prev.at(current_vertex->getVertex()->getData()));
            Edge<VertexType> * new_edge = last_vertex->getEdge(*current_vertex->getVertex());
            if(new_edge)
                traveler->traverse_edge(*new_edge);
        }


        std::vector<Edge<VertexType> *> edges = current_vertex->getAllEdges();

        for(auto edge : edges) {

            Vertex<VertexType> * tempVert = edge->getVertex();
            VertexType tempData = tempVert->getData();

            typename std::unordered_map<VertexType, bool>::const_iterator get = marked.find(tempData);

            if(traveler != nullptr) {
                traveler->examine_edge(*edge);
                // std::cout << "3st\n";
            }

            // if we haven't seen the target vertex for this edge
            if(get == marked.end()) {
                // add the source vertex for this target vertex to our map
                prev.insert(std::pair<VertexType, VertexType>(tempData, edge->getSource()->getData()));

                // mark the target vertex as seen
                marked.insert(std::pair<VertexType, bool>(tempVert->getData(), true));

                // push it into our queue
                q.push_back(tempVert);
            }
        }

    }

    if(traveler != nullptr)
        traveler->finished_traversal();

    return true;

}


// @func   - breadthFirst
// @args   - #1 Data associated with the starting vertex for the search,  #2 Traveler class to process the graph
//           components as they're discovered.
// @return - Bool indicating if the function could find the starting vertex based on arg#1
// @info   - Performs a breadth first traversal, calling the appropriate function inside of the Traveler class when
//           it encounters a new vertex or edge. This function assumes that all vertex data is unique, so if this is
//           a graph of strings, no two strings should be the same. This precondition allows us to use an
//           std::unordered_map to keep track of the seen and unseen vertices.
template<class VertexType>
bool dGraph<VertexType>::breadthFirst(const VertexType & root_data, GraphTraveler<VertexType> * traveler) {

    // Our queue object, stores the vertices as they appear to the search
    std::deque<Vertex<VertexType> *> q;

    // A map that allows us to mark the vertices when they've been seen.
    // maps a set of unique vertex data to a bool that is true if that data has been seen before
    typename std::unordered_map<VertexType, bool> marked;

    // Maps a target vertex that is examined to the source vertex that we were at when we examined it
    typename std::unordered_map<VertexType, VertexType> prev;

    AdjList<VertexType> *  root_vert = findVertex(root_data);

    if(root_vert == nullptr)
        return false;


    marked.insert(std::pair<VertexType, bool>(root_data, true));
    q.push_back(root_vert->getVertex());


    AdjList<VertexType> *  current_vertex = nullptr;
    bool first_iteration = true;

    while(q.size()) {

        Vertex<VertexType> * tempVert = q.front();q.pop_front();
        current_vertex = findVertex(tempVert->getData());

        if(current_vertex == nullptr)
            return false;

        VertexType tempData = current_vertex->getVertex()->getData();

        // visit the new vertex
        if(traveler && first_iteration) {
            traveler->starting_vertex(root_vert->getVertex()->getData());
            first_iteration = false;
        }
        else if(traveler) {
            AdjList<VertexType> * last_vertex = findVertex(prev.at(current_vertex->getVertex()->getData()));
            Edge<VertexType> * new_edge = last_vertex->getEdge(*current_vertex->getVertex());
            if(new_edge)
                traveler->traverse_edge(*new_edge);
        }


        std::vector<Edge<VertexType> *> edges = current_vertex->getAllEdges();

        // Go through all of the edges associated with the current vertex
        for(auto edge : edges) {

            Vertex<VertexType> * tempVert = edge->getVertex();
            VertexType tempData = tempVert->getData();

            typename std::unordered_map<VertexType, bool>::const_iterator get = marked.find(tempData);

            // examine the new edge
            if(traveler != nullptr)
                traveler->examine_edge(*edge);

            // if the current vertex hasn't been seen
            if(get == marked.end()) {

                // add the source vertex for this target vertex to our map
                prev.insert(std::pair<VertexType, VertexType>(tempData, edge->getSource()->getData()));

                // mark the vertex
                marked.insert(std::pair<VertexType, bool>(tempVert->getData(), true));
                // enqueue the new vertex
                q.push_back(tempVert);
            }

        }

    }
    if(traveler != nullptr)
        traveler->finished_traversal();

    return true;
}

// @func   - minimumCut
// @args   - none
// @return - 2 column vector of vertices, each column representing one half of the cut.
// @info   - Partitions the current graph into two subsets that have at the minmum number of edges between them.
// @TODO   - Currently in beta-stage, needs to be tested, debugged, and cleaned. Is semi-working through.
template<class VertexType>
std::vector<std::vector<VertexType> > dGraph<VertexType>::minimumCut() {

    srand(time(0));
    int lowest = std::numeric_limits<int>::max();
    std::vector<std::vector<VertexType> > ret;
    std::vector< AdjList<VertexType> * > finalList;

    // the following are used to choose an edge to contract randomly
    std::random_device rd;
    std::mt19937 gen(rd());

    // We really need to turn this into a loop that does it the expected number of times it takes to get a min-cut
    for(int i = 0; i < 3; i++) {

        std::unordered_map<VertexType, std::vector<VertexType> > collapsed;

        std::vector< AdjList<VertexType> * > newList = list;

        for(auto i : list) {

            collapsed.insert(std::pair<VertexType, std::vector<VertexType> >(i->getVertex()->getData(), std::vector<VertexType>()));
            AdjList<VertexType> * newAdj = new AdjList<VertexType>();
            newAdj->setVertex(i->getVertex()->getData());
            newAdj->set_is_multi_graph(true);

            newList.push_back(newAdj);

            std::vector<Edge<VertexType> *> edges = i->getAllEdges();

            for(auto j : edges) {
                newList.back()->addEdge(j->getVertex(), j->getWeight());
            }
        }

        // While we haven't reduced the graph to 2 vertices
        while(newList.size() > 2) {

            std::uniform_int_distribution<> dist_Vert(0, newList.size()-1);
            int randVertex = dist_Vert(gen);

            auto adj1 = newList[randVertex];

            std::vector<Edge<VertexType> *> edges = adj1->getAllEdges();

            if(!edges.size())
                continue;

            std::uniform_int_distribution<> dist_Edges(0, edges.size()-1);
            int randEdge = dist_Edges(gen);

            AdjList<VertexType> * adj2 = nullptr;


            typename std::vector<AdjList<VertexType> *>::iterator vertToDelete;
            for(typename std::vector<AdjList<VertexType> *>::iterator it = newList.begin() ; it != newList.end(); ++it) {

                AdjList<VertexType> * tempAdj = *it;

                if(tempAdj->getVertex()->getData() ==  edges[randEdge]->getVertex()->getData()) {
                    adj2 = tempAdj;
                    vertToDelete = it;
                    break;
                }
            }

            if(adj2 == nullptr) {
                adj1->deleteEdge(edges[randEdge]->getVertex());
                continue;
            }
            // std::cout << "mid";
            // std::cout << adj1->getVertex()->getData() << " :: " << adj2->getVertex()->getData() << "\n";

            std::vector<Edge<VertexType> *> edges2 = adj2->getAllEdges();

            // std::cout << "mid2";
            for(auto i : edges2) {
                AdjList<VertexType> * tempAdj;
                for(auto j : newList) {
                    if(j->getVertex()->getData() == i->getVertex()->getData()) {
                        tempAdj = j;
                        break;
                    }
                }
                adj1->addEdge(tempAdj->getVertex(), i->getWeight());
            }

            // std::cout << "mid3";

            if(collapsed.find(adj1->getVertex()->getData()) != collapsed.end()) {
                // std::cout << "t1";
                collapsed.at(adj1->getVertex()->getData()).push_back(adj2->getVertex()->getData());
                // std::cout << "t2";
                auto delVert = collapsed.find(adj2->getVertex()->getData());
                // std::cout << "t3";
                if(delVert != collapsed.end()) {
                    collapsed.erase(delVert);
                    // std::cout << "t4";
                }
            }

            newList.erase(vertToDelete);
            // std::cout << "end\n";
        }

        if(lowest > newList[0]->getAllEdges().size()) {
            lowest = newList[0]->getAllEdges().size();
            finalList = newList;
        }
    }
    dGraph<VertexType> * retGraph = new dGraph<VertexType>();

    // retGraph->printGraph();

    std::cout << "Vertex 1 " << finalList[0]->getVertex()->getData() << "\n\n\n";
    std::cout << "Vertex 2 " << finalList[1]->getVertex()->getData() << "\n";
    std::cout << "Edges " <<finalList[0]->getAllEdges().size() << "\n";

    delete(retGraph);

    return ret;
}


// @func   - minimuminSpanningTree
// @args   - none
// @return - Boolean that indicates if the minimum tree could be traversed or not, false if the graph is not strongly-connected
// @info   - This function will traverse the graph is such an order as to build a minimum spanning tree, As of right now it requires
//           that the graph be strongly connected, in-order to avoid an infinite loop. It also always starts at the first
//           vertex inserted into the graph. It really should just take any vertex and create the minimum spanning tree of
//           parts of the graph that are accessable to that specific vertex. That way we can have an accompanying function
//           that computes a minimum spanning forest over the graphs vertices.
template<class VertexType>
bool dGraph<VertexType>::minimumSpanningTree(GraphTraveler<VertexType> * traveler) {

    // A non connected graph cannot be spanned, without this we risk an infinite loop
    if(!isConnected())
        return false;

    std::unordered_map<VertexType, std::pair<VertexType, double> > set; // maps a vertex to a weight and the vertex that connects to it
    std::unordered_map<VertexType, bool> mst_set;
    double imax = std::numeric_limits<double>::infinity();

    for(int i = 0; i < list.size(); i++) {
        VertexType tempData = list[i]->getVertex()->getData();
        set.insert(std::pair<VertexType, std::pair<VertexType, double> >(tempData, std::pair<VertexType, double>(tempData, imax)));
    }

    set.at(list[0]->getVertex()->getData()).second = 0;

    Vertex<VertexType> * best_vertex = list[0]->getVertex();
    Vertex<VertexType> * last_vertex = best_vertex;

    bool first_iteration = true;

    while(mst_set.size() != list.size()) {
        double lowest_weight = imax;
        int index = 0;   // index of the vertex with the lowest wieght found


        if(traveler && first_iteration) {
            traveler->starting_vertex(set.at(best_vertex->getData()).first);
            first_iteration = false;
        }

        // VERY inneficient! Here we scan linearly through all vertices to find the smallest, we need a priority queue!
        for(int i = 0; i < list.size(); i++) {

            if(mst_set.find(list[i]->getVertex()->getData()) == mst_set.end()) {

                if(set.at(list[i]->getVertex()->getData()).second <= lowest_weight) {
                    lowest_weight = set.at(list[i]->getVertex()->getData()).second;
                    index = i;
                }
            }
        }

        best_vertex = list[index]->getVertex();// best vertex to choose to add to the min tree
        last_vertex =  findVertex(set.at(best_vertex->getData()).first)->getVertex();

        // Take the vertex with the smallest weight and mark it as connected to our min tree
        mst_set.insert(std::pair<VertexType, bool>(best_vertex->getData(), true));

        // examine the new edge inserted into the minimum-tree
        if(traveler)  {
            Edge<VertexType> new_edge(last_vertex, best_vertex, lowest_weight);
            traveler->traverse_edge(new_edge);
        }

        // Get all of that vertices neighbors
        std::vector<Edge<VertexType> *> edges = list[index]->getAllEdges();


        // Update the weighting of the vertices that are neighbors of the last vertex
        for(auto edge : edges) {

            if(traveler)  {
                Edge<VertexType> new_edge(edge->getSource(), edge->getTarget(), edge->getWeight());
                traveler->examine_edge(new_edge);
            }

            if(edge->getWeight() <= set.at(edge->getTarget()->getData()).second) {
                set.at(edge->getTarget()->getData()) = std::pair<VertexType, double>(list[index]->getVertex()->getData(), edge->getWeight());
            }

        }

    }

    if(traveler)
        traveler->finished_traversal();

    return true;
}


// @func   - dijkstrasMinimumTree
// @args   - #1 Data contained in starting vertex for search, #2 optional destination vertex, if null we will
//           find the path to every node otherwise we stop when we find the destination node
// @return - A pair containing two maps. The first map takes a vertex and returns the previuos vertex in the
//           path there from the source vertex.The second map takes a vertex and gives the total weight that
//           it takes to get there from the source vertex.
// @info   - Performs Dijkstra's path-finding algorithm to get from a starting vertex to any goal vertex in the
//           map, throws an exception if the source vertex is not contained in the map.
template<class VertexType>
typename dGraph<VertexType>::dist_prev_pair * dGraph<VertexType>::dijkstrasMinimumTree(const VertexType & source, const VertexType * dest) {

    //auto start = std::chrono::high_resolution_clock::now();


    if(findVertex(source) == nullptr)
        throw std::logic_error("Source Vertex Not in Graph\n");

    double max_weight = std ::numeric_limits<double>::infinity();

    // Convenient define, this pair will as the type of each entity in our priority queue (a std::set)
    using vert_dist_pair = std::pair<double, VertexType>;

    // Convenient syntax define, this set orders its elements based on our custom lambda function, which gives us a priority queue
    // over the vertices and their distance from the source node
    using priority_queue = std::set<vert_dist_pair, bool (*)(const vert_dist_pair & a, const vert_dist_pair & b) >;

    // This function takes two pairs<weight, Vertex> and does the comparison only on the weight, not the vertex data. This is passed
    // into our std::set object to allow it to order the nodes according the lowest weight, which gives us a priority queue.
    // auto f = [](const std::pair<double, VertexType> & a, const std::pair<double, VertexType> & b) -> bool { return  a.first < b.first; };
    auto f = [](const vert_dist_pair & a, const vert_dist_pair & b) -> bool { return  a.first-b.first < 0.000000001; };

    // The priority queue object that we use to run the algorithm. This is really a std::set with a specific ordering function. This set consists
    // of std::pairs, which is a pair of VertexData and a double value, which is the weight along the shortest path to reach that vertex that has
    // so far been discovered. The ordering function orders the vertices in the set based off of the double value only.
    priority_queue queue(f);

    // a pair of maps, this returns both the path between the nodes and the net weight along each path to the user-accessible interface function
    typename dGraph<VertexType>::dist_prev_pair * ret = new dGraph<VertexType>::dist_prev_pair();


    std::unordered_map<VertexType, double> dist;     // Maps a vertex to it's distance from the source vertex
    std::unordered_map<VertexType, VertexType> prev; // Maps a given vertex to the previous vertex that we took to get there
    std::unordered_map<VertexType, bool> scanned;    // Maps a given vertex to a bool, letting us know if we have examine all of it's neighbors.

    dist.reserve(getNumVertices());
    prev.reserve(getNumVertices());

    for(auto & vertex : list) { // Initialize the distances to infinity for all vertices
        dist.insert(std::pair<VertexType, double>(vertex->getVertex()->getData(), max_weight));
        queue.insert(std::make_pair(dist.at(vertex->getVertex()->getData()), vertex->getVertex()->getData()));
    }

    queue.erase(std::make_pair(dist.at(source), source));
    dist.at(source) = 0;
    queue.insert(std::make_pair(dist.at(source), source));

    while(!queue.empty()) {

        // grab from the front of the queue
        double current_dist = queue.begin()->first;
        AdjList<VertexType> * current_vert = findVertex(queue.begin()->second);
        if(dest != nullptr && current_vert->getVertex()->getData() == *dest) {
            break;
        }
        queue.erase(queue.begin());
        scanned.insert(std::pair<VertexType,bool>(current_vert->getVertex()->getData(), true));

        // get the incident edges for the current vertex
        auto edges = current_vert->getEdgeList();

        // cycle through these edges and adjust the path weighting associated with the target vertex
        // if it is lower than the current shortest path to that vertex
        for(auto & edge : *edges) {

            AdjList<VertexType> * temp_vert = findVertex(edge->getTarget()->getData());
            VertexType temp_data = temp_vert->getVertex()->getData();

            double temp_weight = edge->getWeight() + current_dist;

            if(scanned.find(temp_data) == scanned.end() && temp_weight <= dist.at(temp_data)) {

                queue.erase(std::make_pair(dist.at(temp_data), temp_data));
                dist.at(temp_data) = temp_weight;
                if(prev.find(temp_data) == prev.end()) {
                    prev.emplace(temp_data, current_vert->getVertex()->getData());
                }
                else {
                    prev.at(temp_data) = current_vert->getVertex()->getData();
                }
                queue.insert(std::make_pair(dist.at(temp_data), temp_data));
            }

        }
    }

    ret->first = prev;
    ret->second = dist;
    //auto elapsed = std::chrono::high_resolution_clock::now() - start;
    //long long m = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count();

    //std::cout << "Total Time : " << m << "\n";

    return ret;
}

// @func   - dijkstrasShortestPath
// @args   - #1 Source Vertex, #2 Dest Vertex, #3 the GraphTraveler-derived object that will recieve the vertices and edges in minimum order
// @return - bool indicating success, will return false for graphs with no connection between src and dest vertices.
// @info   - This function is intended for the user to call to compute the shortest path between any two vertices. This function calls
//           the dijkstras(...) function and decodes the output to give the user the specific path they are looking for, as opposed to a
//           structure that contains the shortest path from the source vertex to any vertex in the map.
template<class VertexType>
bool dGraph<VertexType>::dijkstrasShortestPath(const VertexType & src, const VertexType & dest, GraphTraveler<VertexType> * traveler) {

    std::unordered_map<VertexType, VertexType> * prev;
    std::unordered_map<VertexType, double> * dist;
    std::vector<VertexType> path;
    //std::pair<std::vector<VertexType>, double> ret;

    if(findVertex(src) == nullptr || findVertex(dest) == nullptr)
        throw std::logic_error("SRC or DEST Vertices Do Not Exist in Graph\n");

    if(src == dest) {
        path.push_back(dest);
        if(traveler != nullptr) {
            traveler->starting_vertex(src);
            traveler->finished_traversal();
        }
        return true;
    }

    typename dGraph<VertexType>::dist_prev_pair * the_pair = dijkstrasMinimumTree(src, &dest);
    prev = &the_pair->first;
    dist = &the_pair->second;


    VertexType prev_vert = dest;
    path.push_back(dest);
    int count = 0;
    while(prev_vert != src && count < list.size()) {

        if(prev->find(prev_vert) == prev->end()) {
            return false;//std::pair<std::vector<VertexType>, double>();
        }
        prev_vert = prev->at(prev_vert);
        path.push_back(prev_vert);
        count++;
    }

    if(!path.size())
        return false;

    if(traveler != nullptr) {

        VertexType current = *(path.end()-1);
        VertexType last = current;
        traveler->starting_vertex(current);

        for(int i = path.size()-2; i >= 0; --i) {
            current = path[i];

            if(!containsEdge(last, current)) {
                return false;
            }

            Edge<VertexType> next_edge = *(findVertex(last)->getEdge(current));

            traveler->traverse_edge(next_edge);
            last = current;
        }

        traveler->finished_traversal();
    }
    delete(the_pair);

    return true;
}

// @func   - aStar
// @args   - #1 Data contained in starting vertex for search,  #2 Pointer to a hueristic function on a given node
// @return - Vector containing, in-order, the vertices to take to reach your goal. Empty if you are there or no path exists.
// @info   - Performs the A* path-finding algorithm to get from a starting vertex to any goal vertex in a list of vertices.
template<class VertexType>
std::vector<VertexType> dGraph<VertexType>::aStar(const VertexType &, std::vector<VertexType>, double hueristic(VertexType&, VertexType&)) {

     // #TODO - Implement A* Path-finding algorithm

}


/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////         PRIVATE FUNCTIONS        //////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

// @func   - findVertex
// @args   - #1 Value contained in the vertex to be found
// @return - Pointer to the AdjList containing the vertex in queston. nullptr if not found (possibly should throw exception?)
// @info   - Goes through our vector of vertices and find which one (if any) contain the data given by the argument
template<class VertexType>
AdjList<VertexType> * dGraph<VertexType>::findVertex(const VertexType & data) const{

    auto get = lookup_map.find(data);

    // if true then a vertex with the given data does not exist in our map, so return nullptr.
    if(get == lookup_map.end())
        return nullptr;

    return get->second;
 }
