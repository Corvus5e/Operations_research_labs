
#include <orl_algorithms.h>
#include <QMap>
#include <unordered_set>

struct Node {
    int index; // index in graph
    double score; // lower score
    Node* parent;

    Node(int index, double score, Node* parent){
        this->index = index;
        this->score = score;
        this->parent = parent;
    }
};

void orl::branchBoundShortestWay(Graph &graph, int start_node, int end_node, QVector<int> &way){

}

void nextNodes(orl::Graph& g, std::unordered_set<int>& visited, QVector<int>& neighbours, QVector<Node*>& next_nodes)
{
    for(auto i = 0; i < neighbours.size(); i++){
        if(visited.find(neighbours[i]) == visited.end()){ //true - node is not visited
            next_nodes.push_back(new Node(neighbours[i],
                                          current->score + g.weight(current->index, neighbours[i]),
                                          current));
        }
    }
}

void update_records(QVector<Node*> lower_nodes, QVector<Node*>& records)
{
    /*for(){

    }*/
}

int findShortestWay(Node* current, orl::Graph& g, int destination_index, std::unordered_set<int> visited, QVector<Node*>& records)
{
    visited.insert(current->index);

    QVector<int> neighbours;
    g.neighbours(current->index, neighbours);

    QVector<Node*> next_nodes;
    nextNodes(g, visited, neighbours, next_nodes);

    if(next_nodes.size() > 0){

    }

    return 0;
}
