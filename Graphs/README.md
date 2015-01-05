Graphs
===============

#### Overview

One of the main goals of this project is to create few different implementations of the famous graph data structure. I would like to implement both an undirected and directed graph using both adjacency list and ajdacency matrix representations. This would allow a user to choose which representation they want according to the specific needs of the project. As of right now, I have implemented both the directed and undirected graph data structures using an adjacency list. They can be found in `/Graph/GraphAdjList/UndirectedGraph/` and `/Graph/GraphAdjList/DirectedGraph/`. The directories are broken up as follows  : 

* `GraphInterface/` - This directory contains the GraphInterface class declaration, which all of the other graph classes in this project will inherit from.
* `GraphAdjList/`   - This directory contains all of the files related to the adjacency list representations of graphs, both directed and undirected.
* `GraphAdjMat/`   - This directory contains all of the files related to the adjacency matrix representations of graphs, both directed and undirected.

#### GraphInterface/GraphInterface.h
This is a pure, abstract interface class that all of the other defined graph classes will derive from. This class strictly defines the required functionality of the implemented graphs without imposing too many equirements on the implementation details.



