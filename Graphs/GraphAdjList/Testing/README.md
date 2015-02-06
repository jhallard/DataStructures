Testing
===============

#### Overview
This directory contains all of the testing functionality for the graph classes in the data structures project. The testing is performed with the help of the GoogleTest librariries for C++. These libraries supply a simple and lightweight methodology for writing unit tests. This directory is broken up into subdirectories for dGraph and uGraph related testing suites. Each graph type contains multiple testing suites which can be ran together or separetely. These tests are divided based on the vertex data, so graphs over integers are in thier own folder, graphs over strings are in their own folder, etc. These tests not only test for correctness but also measure and log running times so that improvements in the implementation can be logged over time.

#### uGraph
This directory contains all of the unit tests for the uGraph (undirected graph) class. As of right now, there are only two sets of unit tests for the uGraph class. One is very comprehensive (7 files, 1300+ lines of code, 1-2 minutes to complete), and uses integers as the vertex data. The second one handles strings as the vertices and is only part implemented as of right now.

#### dGraph
This directory contains all of the unit tests for the dGraph (directed graph) class. As of right now, there are only two sets of unit tests for the dGraph class. One is very comprehensive (7 files, 1300+ lines of code, 1-2 minutes to complete), and uses integers as the vertex data. The second one handles strings as the vertices and is only part implemented as of right now.



