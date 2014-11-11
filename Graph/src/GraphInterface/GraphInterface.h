/**
*	@Author   - John H Allard Jr.
*	@File     - GraphInterface.h
*	@Data     - 11/11/2014
*	@Purpose  - Defines an interface for a graph data structure. As C++ has no true interfaces, this class consists purely of public virtual functions,
*				which ensures that the MAT_Graph and LIST_Graph classes, which will derive from this interface, must implement every function listed below.
*
**/

#ifndef GraphInterface_h
#define GraphInterface_h

template<class VertexType>
class GraphInterface
{
public:

	/*
	* @func   - insertVertex
	* @args   - #1 The value of the node to be inserted
	* @return - Boolean indicating succes 
	*/
	virtual bool insertVertex(VertexType) = 0;

	/*
	* @func   - deleteVertex
	* @args   - #1 The value of the node to be deleted
	* @return - Boolean indicating succes 
	*/
	virtual bool deleteVertex(VertexType) = 0;

	/*
	* @func   - insertEdge
	* @args   - #1 From node, #2 "To" Node, #3 Weight Value (default = 1.0)
	* @return - Boolean indicating succes 
	*/
	virtual bool insertEdge(VertexType, VertexType, double = 1.0) = 0;

	/*
	* @func   - deleteEdge
	* @args   - #1 From node, #2 "To" Node
	* @return - Boolean indicating succes 
	*/
	virtual bool deleteEdge(VertexType, VertexType) = 0;


	/*
	* @func   - getWeight
	* @args   - #1 From node, #2 "To" Node
	* @return - Boolean indicating succes 
	*/
	virtual double getWeight(VertexType, VertexType) = 0;

	/*
	* @func   - numVertices
	* @args   - None
	* @return - The number of vertices currently in the graph.
	*/
	virtual int getNumVertices() const = 0;

	/*
	* @func   - numEdges
	* @args   - None
	* @return - The number of edges currently in the graph.
	*/
	virtual int getNumEdges() const = 0;

	/*
	* @func   - depthFirst
	* @args   - None
	* @return - nothing
	* @info   - Performs a depth first traversal, calling the visit() function on each item
	*/
	virtual void depthFirst(VertexType, void visit(VertexType&)) = 0;

	/*
	* @func   - breadthFirst
	* @args   - None
	* @return - nothing
	* @info   - Performs a breadth first traversal, calling the visit() function on each item
	*/
	virtual void breadthFirst(VertexType, void visit(VertexType&)) = 0;


};

#endif