DataStructures
===============

#### Project Overview

Author  - John Allard
License - None, but feel free to use, distribute, modify, or make fun-of the code as you see fit.

The purpose of this project is to implement some of the more common, yet-complicated, data structures using the C++ programming language and some C++11 features.
The data structures created in this project are all fully templated and made to be as general, efficient, and reliable as possible. The currently implemented data structures are :
* Graph - When finished, this will be a grouping of related but different graph data structures. As of right now, only an undirected graph using an adjacency list representation has been implemented, but I will be soon implementing a directed graph data structure that also uses an adj. list. In the future I would also like to make both an undirected and directed graph using an adjacency matrix. 
Th current graph is completely templated and uses an adjacency list to represent the data structure. This class does not merely represent a graph, it also has built in many of the famous and useful graph algorithms like breadth first search, depth first search, connectivity tests, and more. 
* HashDictionary - This is a project I began implementing about a year ago for a data structures class, but recently I began improving on the implementation. It is also a few fully templated dictonary that uses chaining to handle collisions. The hash function used is the one provided by the std::hash function.
