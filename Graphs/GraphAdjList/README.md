GraphAdjList
===============

#### Overview

This directory contains all of the types of graph classes that are derived from the `GraphInterface` class and that use an adjacency list to internally represent the graph data structure (as apposed to an adjacency matrix, etc).

An adjacency list consists of a vertex and a list  of edges that eminate from this vertex to the other vertices in the map, along with the weight associated with those edges.  Thus if some vertex v had edges connected it with vertices a, b, c, d, and e, the adj list for vertex v would look like :
 * `v -> a* -> b* -> c* -> d* -> e* -> null`

Where x* is an edge that leads from vertex v to vertex x. Thus to find all of the edges that eminate from a given vertex v, you just need to traverse the list of edges on the AdjList that contains vertex v. This above is just one adjacency list, our graph will have a single adjacency list for each vertex in the graph. So our graph data structure will look more like this :

 1. `   a  -> c* -> d* -> null        `
 2. `   b  -> v* -> d* -> e* -> null  `
 3. `   c  -> a* -> v* -> e* -> null  `
 4. `   d  -> a* -> b* -> null        `
 5. `   e  -> b* -> c* -> v* -> null  `
 6. `   v  -> b* -> c* -> null        `

As of now, there are two types of graphs that use an adjacency list implementation. They are uGraph (undirected graph) and dGraph(DirectedGraph). Both rely on the same AdjList, Vertex, and Edge classes to accomplish their implementations.

#### uGraph
This is an undirected graph that can be either weighted or unweighted, the choice is up to the user. Internally, the graph is always weighted. But edges without assigned weights are given a weight of infinity, so if no edge weights are assigned then all edges are treated equally. The data structure is templated over the vertex data, allowing the graph to work with standard and custom data types that implement some required functionality (must supply a hash function and equality comparison functionality for the vertex class).

#### dGraph
This is an directed graph that can be either weighted or unweighted, the choice is up to the user. It is nearly identical to the undirected graph, with slight changes showing up in the insert, remove, and traversal functions. There are certain functions, like deleteVertex, that actually take significantly longer (asymptotically slower) then the uGraph companion. This is because the directed graph doesn't know all edges that point to it, so it has to search the entire graph in order to clean up all edges that touch it. Checking for connectivity also takes longer, as the algorithm is more complex and involves a graph reversal.


