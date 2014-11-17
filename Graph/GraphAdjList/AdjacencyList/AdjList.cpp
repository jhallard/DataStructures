/**
*   @Author   - John H Allard Jr.
*   @File     - AdjList.cpp
*   @Data     - 11/13/2014
*   @Purpose  - This file defines the adjascency list class, which consists of a vertex and a pointer to an edge. The purpose of this class
*               is mostly to simplify the syntax of the code inside of the uGraph class. The uGraph class will simply consist of a vector of this AdjLists,
*               where each AdjList corresponds to a single vertex in the graph and all of the edges that have contact with the vertex. All code is open license 
*               and free to use, just leave some sort of note in your source code giving credit to me and a link to my github (github.com/jhallard)
**/


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


    // @func - Destructor
    // @args - None
    // @info - Cleans up the edges allocated with new() in insertEdge function
    template <class VertexType>
    AdjList<VertexType>::~AdjList() {

        Edge<VertexType> * temp = pEdge;

        if(temp == nullptr)
            return;

        Edge<VertexType> * temp2 = temp->getNext();

        while(temp2 != nullptr){
            temp = temp2;
            temp2 = temp2->getNext();
            delete(temp);
        }
    }


    // @func   - setVertex
    // @args   - #1 Vertex Object
    // @return - Bool indicating success or failure
    template <class VertexType>
    bool AdjList<VertexType>::setVertex(Vertex<VertexType> newData){

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

        Edge<VertexType> * newEdge = new Edge<VertexType>(vert, wt);
        // newEdge->setVertex(vert);
        // newEdge.setWeight(wt);

        if(pEdge == nullptr) {
            pEdge = newEdge;
            return true;
        }

        Edge<VertexType> * temp;
        temp = pEdge;
        while(temp->getNext() != nullptr){
            temp = temp->getNext();
        }
        
        return temp->setNext(newEdge);
    

    }



    // @func - deleteEdge
    // @args - #1 the data contained by the vertex that you wish to delete the edge from
    // @info - finds the vertex containing the data passed in as an argument, and deletes it from the chain.
    template <class VertexType>
    bool AdjList<VertexType>::deleteEdge(VertexType data){

        Edge<VertexType> * temp;
        temp = pEdge;

        // Case #1 - No edges in the list, return false
        if(temp == nullptr)
            return false;

        // Case #2 - The edge to delete is the first node found
        else if(temp->getVertex()->getData() == data){
            pEdge = pEdge->getNext();
            return true;
        }
        // Case #3 - The edge may or may not be somewhere down the chain
        while(temp->getNext() != nullptr) {

            // if the edge to delete is the next node, set the next chain to be 2 nodes down, looping around the node to be deleted
            if(temp->getNext()->getVertex()->getData() == data){
                temp->setNext(temp->getNext()->getNext());
                return true;
            }
            // else we iterate to the next node in the chain
            else
                temp = temp->getNext();
            
        }
        // else we couldn't find an edge to the given vertex with the given data
        return false;

    }


    // @func - deleteEdge
    // @args - #1 Pointer to the vertex to be deleted.
    // @info - finds the vertex containing the data passed in as an argument, and deletes it from the chain.
    template <class VertexType>
    bool AdjList<VertexType>::deleteEdge(Vertex<VertexType> * vert){

        Edge<VertexType> * temp;
        temp = pEdge;

        // Case #1 - No edges in the list, return false
        if(temp == nullptr)
            return false;

        // Case #2 - The edge to delete is the first node found
        else if(temp->getVertex() == vert){
            pEdge = nullptr;
            return true;
        }
        // Case #3 - The edge may or may not be somewhere down the chain
        while(temp->getNext() != nullptr) {

            // if the edge to delete is the next node, set the next chain to be 2 nodes down, looping around the node to be deleted
            if(temp->getNext()->getVertex() == vert){
                temp->setNext(temp->getNext()->getNext());
                return true;
            }
            // else we iterate to the next node in the chain
            else
                temp = temp->getNext();
            
        }
        // else we couldn't find an edge to the given vertex with the given data
        return false;

    }


    // @func - getEdge
    // @args - #1 Pointer to the edge to be returned.
    // @info - ffinds and returns the given edge if it exists
    template <class VertexType>
    Edge<VertexType> * AdjList<VertexType>::getEdge(Vertex<VertexType> * vert) {

        Edge<VertexType> * temp;
        temp = pEdge;

        // Case #1 - No edges in the list, return false
        if(temp == nullptr)
            return nullptr;

        if(temp->getVertex() == vert)
            return temp;

        // Case #3 - The edge may or may not be somewhere down the chain
        while(temp->getNext() != nullptr) {

            // if the edge to return is the next node, return that node
            if(temp->getNext()->getVertex() == vert){
                return temp->getNext();
            }
            // else we iterate to the next node in the chain
            else
                temp = temp->getNext();
            
        }
        // else we couldn't find an edge to the given vertex with the given data
        return nullptr;

    }


    // @func   - getAllEdges
    // @args   - None
    // @return - Vector of pointers to all the edge objects in the class
    template <class VertexType>
    std::vector<Edge<VertexType> *> AdjList<VertexType>::getAllEdges() {

        std::vector<Edge<VertexType> *> retVec;
        Edge<VertexType> * temp;
        temp = pEdge;

        // Case #1 - No edges in the list, return false
        if(temp == nullptr)
            return retVec;

        // Case #3 - The edge may or may not be somewhere down the chain
        while(temp != nullptr) {

            retVec.push_back(temp);
            temp = temp->getNext();
            
        }

        return retVec;

    }
