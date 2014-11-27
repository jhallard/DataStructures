DataStructures
===============

#### Project Overview

**DataStructures** is a collection of data structures implemented using the C++ programming language and some C++11 features.
The data structures created in this project are all fully templated and made to be as general, efficient, and reliable as possible. This is a personal project developed by John Allard, if you are interested in contributing to this project please email me (john@jhallard.com) and we can work something out. All code in this project is currently unlicensed, but feel free to use, distribute, or poke fun at anything you wish.

###### Data Structures
* **Graph** - A graph is one of the most all-encompasing data structures known to man, and they are the source for some of the most interesting problems in computer science. This project contains a few different graph implementations, all of which come with their own implementation of BFS, DFS, min-cut, dijkstra's, and other popular graph algorithms. 
    * **uGraph** - A templated, undirected graph that uses a vector of adjacency lists to represent the graph internally.
    * **dGraph** - A templated, directed graph that also uses adjacency lists to represent the graph.
* **Dictionary** - An associative data structure, associate a key with an item. Many different ways to implement.
    * **HashDictonary** - A templated dictionary that uses chaining to resolve collisions. 

##### Graph
This project will contain a few different implementations of the famous graph data structure. The end goal is to implement both an undirected and directed graph using both an adjacency list and ajdacency matrix representation. This allows a user to choose which representation they want according to the specific needs of the project. As of right now, I have only implemented the undirected graph data structure using an adjacency list. It can be found in `/Graph/GraphAdjList/UndirectedGraph/`.

##### HashDictionary
I first implemented this for a data structures class around the spring of 2014, but I have recently begun to add changes and make improvements. This data structure represents a dictionary that uses hashing to insert and locate items. To resolve collisions, we use chaining with linked lists.

##### What's next?
There currently exists a working binary search tree class in this project, but this code is mostly not mine. It is from a data-structures book, but had significant parts missing (purposefully left for the student to fill in), so I took to the task of completing, testing, and improving the code. I plan on starting a new BST implementation from scratch using this previous implementation as a guideline.