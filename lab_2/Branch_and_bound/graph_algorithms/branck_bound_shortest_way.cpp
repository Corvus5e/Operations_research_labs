
#include <orl_algorithms.h>
#include <limits>
#include <algorithm>

namespace {

struct Node {
    int index;    // index in graph
    double score; // lower score    

    Node(){ }

    Node(int index, double score){
        this->index = index;
        this->score = score;        
    }
};

bool nodeScoreComp(Node& n1, Node& n2)
{
    return n1.score < n2.score;
}

void getNeighbourNodes(Node& current_node, orl::Graph& g, QVector<Node>& next_nodes)
{
    QVector<int> neighbours;
    g.neighbours(current_node.index, neighbours);
    for(auto i = 0; i < neighbours.size(); i++){
        double node_score = current_node.score + g.weight(current_node.index, neighbours[i]);
        next_nodes.push_back(Node(neighbours[i], node_score));
    }
}

void restoreShortestWay(int start, int end, QVector<int>& way_map, QVector<int>& shortest_way)
{
    for(auto i = end; i != start; i = way_map[i]){
        if(i >= 0){
            shortest_way.push_back(i);
        }
        else {
            shortest_way.clear();
            return;
        }
    }
    shortest_way.push_back(start);
    std::reverse(shortest_way.begin(), shortest_way.end());
}

}
void orl::branchBoundShortestWay(Graph &graph, int start_node, int end_node, QVector<int> &shortest_way)
{
    QVector<double> records(graph.size(), std::numeric_limits<double>::infinity());
    QVector<int> way_map(graph.size(), -1);
    QVector<Node> next_nodes;

    records[start_node] = 0.0;
    next_nodes.push_back(Node(start_node, 0));

    while(next_nodes.size() > 0){

        auto current_node_it = std::min_element(next_nodes.begin(), next_nodes.end(), nodeScoreComp);
        Node current_node = (*current_node_it);
        next_nodes.erase(current_node_it);

        if(current_node.index != end_node){
            QVector<Node> neighbours_nodes;
            getNeighbourNodes(current_node, graph, neighbours_nodes);

            for(auto i = 0; i < neighbours_nodes.size(); i++){
                if( neighbours_nodes[i].score < records[neighbours_nodes[i].index]){
                    records[neighbours_nodes[i].index] = neighbours_nodes[i].score;
                    next_nodes.push_back(neighbours_nodes[i]);
                    way_map[neighbours_nodes[i].index] = current_node.index;
                }
            }
        }
    }

    restoreShortestWay(start_node, end_node, way_map, shortest_way);

}
