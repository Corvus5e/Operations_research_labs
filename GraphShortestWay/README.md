Program finds the shortest way in a graph between two nodes. 
----------------------------------------------------------------
Graph is read from a file. Graph is stored as adjacency matrix.

**File's structure**
Each row describes connections of one node with others. Every value separated by TAB. If there are no connection between nodes, any not number symbol  is placed. First line  - are names of nodes, separated by TAB.

Example of file [main_task.txt](https://github.com/Corvus5e/Operations_research_labs/blob/master/GraphShortestWay/graphs/main_task.txt)

Second line describes A node's connections.
Third line - of B node, and so on.


**Run example:**
```
GraphShortestWay.exe graph_folder/my_graph.txt A G Dijkstra
```
A and G - are names of nodes, Dijkstra - is name of used algorithm

**Names of aviable algorithms:**

Dijkstra         - Dijkstra algorithm <br />
Branch_and_bound - Branch and bound algorithm <br />