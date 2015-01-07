/**
*   @Author   - John H Allard Jr.
*   @File     - uTraveler.h
*   @Data     - 1/2/2014
*   @Purpose  - This file defines the a testing traveler class that will process the vertices and edges as they come in.
**/

#ifndef BiPartite_Traveler_h
#define BiPartite_Traveler_h

#include "../Edge/Edge.h"
#include "../Vertex/Vertex.h"

template<class V> class dGraph; // forward declaring dGraph class

template<class VertexType>
class BipartiteTraveler : public GraphTraveler<VertexType>
{
public:

    bool current_color;
    bool is_bipartite;
    std::unordered_map<VertexType, bool> vertex_colors;
    
    BipartiteTraveler() : current_color(false), is_bipartite(true) {}  
    ~BipartiteTraveler() {};

    void discover_vertex(const VertexType & vert) {

        if(vertex_colors.find(vert) == vertex_colors.end()) {
            vertex_colors.insert(std::pair<VertexType, bool>(vert, current_color));
        }
        else if(vertex_colors.at(vert) != current_color) {
            current_color = (vertex_colors.at(vert));
        }
    }

    void examine_edge(const Edge<VertexType> & edge) {

        VertexType vert = edge.getVertex()->getData();

        if(vertex_colors.find(vert) == vertex_colors.end()) {
            vertex_colors.insert(std::pair<VertexType, bool>(vert, !current_color));
        }
        else if(vertex_colors.at(vert) == current_color) {
                is_bipartite = false;
        }
    }


    // @function - traverse_edge
    // @args     - #1 An edge object, this contains a pointer to the target verex and the weight on the edge.
    // @info     - This function is called when we traverse an edge to a new vertex 
    void traverse_edge(const Edge<VertexType> & edge) {

        VertexType vert = edge.getVertex()->getData();
        
        if(vertex_colors.find(vert) == vertex_colors.end()) {
            vertex_colors.insert(std::pair<VertexType, bool>(vert, current_color));
        }
        else if(vertex_colors.at(vert) != current_color) {
            current_color = (vertex_colors.at(vert));
        }
    }


    void starting_vertex(const VertexType & vert) {
            vertex_colors.insert(std::pair<VertexType, bool>(vert, current_color));
    }

    void finished_traversal() {
    }

};

#endif