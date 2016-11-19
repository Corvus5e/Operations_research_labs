h2 Program finds the shortest way in a graph between two nodes. 

Graph is read from a file. Graph is stored as adjacency matrix.

**File's structure**
Each row describes connections of one node with others. Every value separated by TAB. If there are no connection between nodes, any not number symbol  is placed. First line  - are names of nodes, separated by TAB.

Example of file(my_graph.txt):

A	B	C	D	E	F	G
-	2	4	5	-	-	-
-	-	1	-	5	12	-
-	-	-	-	-	9	18
-	-	-	-	-	-	8
-	-	-	-	-	4	-
-	-	-	-	-	-	1
-	-	-	-	-	-	-

Second line describes A node's connections.
Third line - of B node, and so on.


**Run example:**

GraphShortestWay.exe graph_folder/my_graph.txt A G Dijkstra

A and G - are names of nodes, Dijkstra - is name of used algorithm

**Names of aviable algorithms:**

Dijkstra         - Dijkstra algorithm
Branch_and_bound - Branch and bound algorithm