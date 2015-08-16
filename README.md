DataStructures
===============

#### Project Overview

**DataStructures** is a collection of data structures implemented using the C++ programming language and some C++11 features.
The structures created in this project are all fully templated and made to be as general, efficient, and reliable as possible. This is a personal project developed to improve my understanding of the fundamental data structures, but if you are interested in contributing to this project please email me (john@jhallard.com) and we can work something out. All code in this project is currently unlicensed, but feel free to use, distribute, or poke fun at anything you wish.

##### Build
**Note** - *The project is not currently build ready, and can't be used as a library for your use. Certain self-containted parts, like the graphs, are working and tested, those could be manually included into a project.*

    git clone https://github.com/jhallard/DataStructures.git
    cd DataStructures
    cmake CMakeLists.txt
    make

#### Graphs
Graphs are one of the most powerful and all-encompasing data structures known to man, and they are the source for some of the most interesting problems in computer science. This project contains a few different graph implementations, all of which come with their own implementation of BFS, DFS, min-cut, dijkstra's, and other popular graph algorithms. Below is a listing of the various flavors of graphs that are implemented.
* GraphInterface - `/Graphs/GraphInterface/` : The interface class from which all of graph implementations in this project derive. 
* uGraph - `/Graphs/GraphAdjList/UndirectedGraph/` : An implementation of a undirected graph that uses a series of adjacency lists to internally represent the graph structure. Almost fully implemented an tested, needs some more work.
* dGraph - `/Graphs/GraphAdjList/DirectedGraph/` :  An implementation of a undirected graph that uses a series of adjacency lists to internally represent the graph structure. Currently about 75% implemented.

#### Dictionaries
* HashDictionary - `Dictionaries/HashDictionary/` : This data structure represents a dictionary that uses hashing to insert and locate items. To resolve collisions, we use chaining with linked lists. I first implemented this for a data structures class around the spring of 2014, but I have recently begun to add changes and make improvements.

#### Directory Structure :
* `/Graphs/` 
    *  `GraphAdjList/`
        * `UndirectedGraph/` - A templated, undirected graph that uses a vector of adjacency lists to represent the graph internally.
        * `DirectedGraph/` - A templated, directed graph that also uses adjacency lists to represent the graph.
* `GraphAdjMat/`
    * (Currently Unimplemented) 
* `/Dictionaries/`
    * `HashDictonary` - A templated dictionary that uses chaining to resolve collisions. 
* `BUGS` -  Contains a list of bugs and possible enhancements for each project.


#### What's next?
In the future I plan to implement at least the following data structures :
* `PriorityQueue` - I will most likely try to implement a priority queue in a few different ways, including binary and fibonacci heaps.
* `Tree` - I would like to implement a few different tree flavors, included binary, AVL, Red/Black, n-ary, and possibly others. The current implementation of BinaryTree is only partially mine, the code was supplied by a textbook but was incomplete (would not compile), I completed it and added more features, but I would like to start my own from scratch.
* `Deque` - A deque can be used as a stack, a queue, or a deque, so implementing this one data structure would be quite useful. The priority queue can possibly derive from this class and just override the insetion and deletion functions.
