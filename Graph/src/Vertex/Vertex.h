/**
*	@Author   - John H Allard Jr.
*	@File     - Vertex.h
*	@Data     - 11/11/2014
*	@Purpose  - This is the definition of the vertex class, which will be used by the different Graph classes in this directory. This class is small, and serves
*				the purpose of wrapping a small amount of data and functions together to simplify the process of working with vertices in the Graph classes.
**/
#ifndef MY_VERTEX_H
#define MY_VERTEX_H

template<class VertexType>
class Vertex
{

public:
	// get the index of the vertex in the adjascency list or matrix
	int getIndex() const;

	// set the index of the vertex ...
	bool setIndex(unsigned int);

	// Get the data that the vertex contains (templated)
	VertexType getData() const;

	// set the data that the vertex contains
	bool setData(VertexType);

private:
	// index in the adjascency list/ adjascency matrix
	unsigned int index;

	// Data that the vertex contains
	VertexType data;

};
#endif