DataStructures
===============

#### Project Overview

The purpose of this project is to implement some of the more advanced data structures using the C++ programming language and some C++11 features.
The data structures created in this project are all fully templated and made to be as general, efficient, and reliable as possible. This is a personal project developed by John Allard, if you are interested in contributing to this project please email me (john@jhallard.com) and we can work something out. All code in this project is currently unlicensed, feel free to use, distribute, or poke fun at any of this code as you wish.

The currently implemented data structures are :
* **uGraph** - A templated undirected graph. Comes with it's own implementation of BFS, DFS, min-cut, dijkstra's, and other popular graph algorithms. 
* **HashDictionary** - A templated dictionary that uses chaining to resolve collisions. 

##### Graph
This project will contain a few different implementations of the famous graph data structure. The end goal is to implement both an undirected and directed graph using both an adjacency list and ajdacency matrix representation. This allows a user to choose which representation they want according to the specific needs of the project. As of right now, I have only implemented the undirected graph data structure using an adjacency list. It can be found in `/Graph/GraphAdjList/UndirectedGraph/`.

##### HashDictionary
I first implemented this for a data structures class around the spring of 2014, but I have recently begun to add changes and make improvements. This data structure represents a dictionary that uses hashing to insert and locate items. To resolve collisions, we use chaining with linked lists.

##### What's next?
There currently exists a working binary search tree class in this project, but this code is mostly not mine. It is from a data-structures book, but had significant parts missing (purposefully left for the student to fill in), so I took to the task of completing, testing, and improving the code. I plan on starting a new BST implementation from scratch using this previous implementation as a guideline.