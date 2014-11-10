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

template<class NodeType>
class GraphInterface
{
public:

	/*
	* @func   - insertNode
	* @args   - #1 The value of the node to be inserted
	* @return - Boolean indicating succes 
	*/
	virtual bool insertNode(NodeType) = 0;

	/*
	* @func   - deleteNode
	* @args   - #1 The value of the node to be deleted
	* @return - Boolean indicating succes 
	*/
	virtual bool deleteNode(NodeType) = 0;

	/*
	* @func   - insertEdge
	* @args   - #1 From node, #2 "To" Node, #3 Weight Value (default = 1.0)
	* @return - Boolean indicating succes 
	*/
	virtual bool insertEdge(NodeType, NodeType) = 0;

	/*
	* @func   - deleteEdge
	* @args   - #1 From node, #2 "To" Node
	* @return - Boolean indicating succes 
	*/
	virtual bool deleteEdge(NodeType, NodeType) = 0;


	/*
	* @func   - getWeight
	* @args   - #1 From node, #2 "To" Node
	* @return - Boolean indicating succes 
	*/
	virtual int getWeight(NodeType, NodeType) const = 0;

	/*
	* @func   - numVertices
	* @args   - None
	* @return - The number of vertices currently in the graph.
	*/
	virtual int numVertices() const = 0;

	/*
	* @func   - numEdges
	* @args   - None
	* @return - The number of edges currently in the graph.
	*/
	virtual int numEdges() const = 0;

	/*
	* @func   - depthFirst
	* @args   - None
	* @return - nothing
	* @info   - Performs a depth first traversal, calling the visit() function on each item
	*/
	virtual void depthFirst(NodeType, void visit(NodeType&)) = 0;

	/*
	* @func   - breadthFirst
	* @args   - None
	* @return - nothing
	* @info   - Performs a breadth first traversal, calling the visit() function on each item
	*/
	virtual void breadthFirst(NodeType, void visit(NodeType&)) = 0;


};

#endif