Graph
===============

#### Overview

This project will contain a few different implementations of the famous graph data structure. The end goal is to implement both an undirected and directed graph using both an adjacency list and ajdacency matrix representation. This allows a user to choose which representation they want according to the specific needs of the project. As of right now, I have only implemented the undirected graph data structure using an adjacency list. It can be found in `/Graph/GraphAdjList/UndirectedGraph/`. The directories are broken up as follows  : 

* GraphInterface/ - This directory contains the GraphInterface class declaration, which all of the other graph classes in this project will inherit from.
* GraphAdjList/   - This directory contains all of the files related to the adjacency list representations of graphs, both directed and undirected.
* GraphAdjMat/   - This directory contains all of the files related to the adjacency matrix representations of graphs, both directed and undirected.

#### uGraph
This is the only currently implemented graph data structure. This is an undirected graph that can be either weighted or unweighted, up to the user! Each edge has a default weight of 1, and if the user wishes to override that weight then they are able to. The effect is that we have combined a weighted and unweighted graph into a single class. There might be some disadvantages to this method, if you know any please feel free to point them out.


