/**
*   @Author   - John H Allard Jr.
*   @File     - adjList.h
*   @Data     - 11/13/2014
*   @Purpose  - This file defines the adjascency list class, which consists of a vertex and a pointer to an edge. The purpose of this class
*				is mostly to simplify the syntax of the code inside of the uGraph class. This class basically serves as a wrapper for std::pair
*
*   @TODO     - Decide on if the graph is going to be weighted or not, if it is, what type of values are going to be the weights? 
*               Will it be templated?  Is this going to be a directed or undirected graph? Undirected would certainly be easier.
*
**/

#ifndef ADJ_LIST_H
#define ADJ_LIST_H

#include <stdexcept>
#include <vector>
#include <string>

#include "../../Vertex/Vertex.h"
#include "../../Edge/Edge.h"


template <class VertexType>
class AdjList
{
	
public:



private:

	Vertex<VertexType> vertex;
	Edge<VertexType> * pEdge;


};