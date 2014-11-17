Graph
===============

#### Overview

Author  - John Allard
License - None, but feel free to use, distribute, modify, or make fun-of the code as you see fit.

This is a grouping of various implementations of different types of graph data structures. The directories are broken up as follows  : 

* GraphInterface/ - This directory contains the GraphInterface class declaration, which all of the other graph classes in this project will inherit from.
* GraphAdjList/   - This directory contains all of the files related to the adjacency list representations of graphs, both directed and undirected.
* GraphAdjMat/   - This directory contains all of the files related to the adjacency matrix representations of graphs, both directed and undirected.

Currently only the undirected graph using an adjacency list has been implemented, but it is quite thorough and working well! It is important to note that we make no distringuishment between weighted and unweighted graphs, the weights for all edges always default to 1.0, and you can override that default value on any insertEdge call as you see fit.

