Bugs and Enhancement Report : uGraph
===============

#### uGraph Overview

 The uGraph class represents a templated, undirected graph that can be either wieghted or unweighted, which is up to the user to decide. This class uses a vector of adjacency lists (as defined in AdjList.h) to represent the graph abstract data type. The class contains a large grouping of premade graph traversal, searching, and partitioning algorithms built in. 


##### Bug Report
This is a list of bugs in contained in the uGraph class (or it's subclasses). The bugs are ranked on a scale of 1-5 in severity, with 5 being the most important.
* Function : ** dijkstras ** - This function seems to work the vast majority of the time, especially if the edges have random weights assigned to them. For instance, in the file `/Testing/uGraphTesting/uGraphTest.cpp`, there is a test that loads up a graph with 2,000+ vertices and 5,000-10,000+ edges. If the edge weights are random, the test can find a path between the source node and any node the majority of the time, but once in the while it will fail. This has to be an error because the test is always performed on a connected graph (as in, we keep regenerating a graph until it is connected), which means that any and all vertices contain a path to any other vertex in the graph. If you try and run the test on a graph that has all weights the same value (equal to 1.0, for example), then the test fails at a much higher rate. This is especially confusing, because there shouldn't be anything special about the case where the edges have the same weights. 
* Function : ** minimumCut **

##### Enhancements

