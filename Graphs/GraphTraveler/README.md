GraphTraveler
===============

#### Overview

This directory contains the abstract GraphTraveler interface class as well as all of it's implementations used internally 
for the graphs in this project. To start, a GraphTraveler is simply an interface that defines an object that can interact
with our graph while we are traversing it. This object has functions that will get called whenever we discover a vertex in
the graph, examine an edge in the graph, or traverse an edge in the graph. This allows the user to run their algorithms
during our traversal functions, as opposed to continually querying our graph for data, working on a copy of that data, then
updating the graph. For an example of this : During DepthFirstSearch, you will be able to work on the graph while we are
traversing the nodes in a BFS fashion. This lets you implement many algorithms (checking for bipartiteness, checking for
connectivity, etc.) while we are performing the search.
