
#include <orl_algorithms.h>
#include <limits>

namespace {

int getNextNode(QVector<double>& dists, QList<int>& not_visited)
{
    if(not_visited.size() > 0){
        int index(not_visited.first());
        double min(dists[index]);
        auto remove_element = not_visited.begin();

        for(auto i = not_visited.begin(); i != not_visited.end(); i++){
            if(min > dists[(*i)]){
                min = dists[(*i)];
                index = *i;
                remove_element = i;
            }
        }

        not_visited.erase(remove_element);

        return index;
    }
    else
        return -1;
}

void restoreShortestWay(int from, int to, QVector<int>& track, QVector<int>& way)
{
    for(int v = to; v != from; v = track[v]){
        if(v == -1){
            way.clear();
            return;
        }
        way.push_back(v);
    }
    way.push_back(from);
    std::reverse(way.begin(), way.end());
}

}

void orl::dijkstraShortestWay(orl::Graph &g, int start_node_number, int end_node_number, QVector<int> &way)
{
    QVector<int> track(g.size(), -1);
    QVector<double> shortest_dist(g.size(), std::numeric_limits<double>::infinity());
    QList<int> not_visited;
    for(auto i = 0; i < g.size(); i++)
        not_visited.push_back(i);

    shortest_dist[start_node_number] = 0;
    int curr = getNextNode(shortest_dist, not_visited);

    while(curr >= 0){

        QVector<int> neighbours;
        g.neighbours(curr, neighbours);

        for(auto i = 0; i < neighbours.size(); i++){
            if(_finite(shortest_dist[neighbours[i]])){

                double new_dist =  g.weight(curr, neighbours[i]) + shortest_dist[curr];

                if(shortest_dist[neighbours[i]] > new_dist){
                    shortest_dist[neighbours[i]] = new_dist;
                    track[neighbours[i]] = curr;
                }
            }
            else{
                shortest_dist[neighbours[i]] = g.weight(curr, neighbours[i]) + shortest_dist[curr];
                track[neighbours[i]] = curr;
            }
        }

        curr = getNextNode(shortest_dist, not_visited);
        neighbours.clear();
    }

    restoreShortestWay(start_node_number, end_node_number, track, way);
}
