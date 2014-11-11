
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
    // @args - Cleans up the edges allocated with new()
    template <class VertexType>
    AdjList<VertexType>::~AdjList() {

        // #TODO - Clean up lost node memory
    }


    // @func - setData
    template <class VertexType>
    bool AdjList<VertexType>::setVertex(Vertex<VertexType> newData){

        this->vertex = newData;
        return true;
    }

    // @func getData
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
            pEdge = nullptr;
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
                temp = temp.getNext();
            
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

            // if the edge to delete is the next node, set the next chain to be 2 nodes down, looping around the node to be deleted
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
