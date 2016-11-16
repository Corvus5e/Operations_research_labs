#include <graph.h>

#include <QFile>
#include <QTextStream>
#include <QList>

#include <exception>
#include <iostream>
#include <iomanip>
#include <limits>
#include <math.h>


Graph::Graph()
{

}

void Graph::readGraph(const QString& file, Graph *graph){
    QFile f(file);
    if(!f.open(QIODevice::ReadOnly | QIODevice::Text)){
        std::string msg("Failed to open file ");
        msg.append(file.toStdString());

        throw std::exception(msg.c_str());
    }

    QTextStream in(&f);

    if(!in.atEnd()){
      QString line =  in.readLine();
      QStringList names = line.split(QRegExp("\\s+"), QString::SkipEmptyParts);
      graph->initNodeNames(names);
    }

    while(!in.atEnd()){
      QString line =  in.readLine();
      QStringList values = line.split(QRegExp("\\s+"), QString::SkipEmptyParts);
      graph->addMatrixRow(values);
    }

}

void Graph::initNodeNames(const QStringList& list){
    for(auto it = list.begin(); it != list.end(); it++){
        this->node_names.push_back(*it);
    }
}

void Graph::addMatrixRow(const QStringList& values){

    QVector<double> row;

    for(auto it = values.begin(); it != values.end(); it++){

        bool ok = false;
        double value = (*it).toDouble(&ok);

        if(ok)
            row.push_back(value);
        else
            row.push_back(0.0); // no connection
    }

    if(row.size() == this->node_names.size()){
       this->matrix.push_back(row);
    }
    else{
        throw std::exception("Number of nodes is not equal to number of values in current row.");
    }
}

QString& Graph::getNodeName(int node_number){
    return this->node_names[node_number];
}

int min_index(QVector<double>& v ){

    double min(v[0]);
    int index(0);

    for(auto i = 1; i < v.size(); i++){
        if(min > v[i]){
            min = v[i];
            index = i;
        }
    }

    return index;
}

int Graph::getNextNode(const QVector<double>& dists, QList<int>& not_visited){
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

void Graph::restoreShortestWay(int from, int to, QVector<int>& track, QVector<int>& way){

    for(int v = to; v != from; v = track[v]){
        if(v == -1){ // no way
            way.clear();
            return;
        }
        way.push_back(v);
    }
    way.push_back(from);
    std::reverse(way.begin(), way.end());
}

void Graph::getNeighbours(int node_number, QVector<int>& neighbours){
    for(auto i = 0; i < this->size(); i++){
        if(matrix[node_number][i] > 0){
            neighbours.push_back(i);
        }
    }
}

void Graph::findShortestWay(Graph& g, int start_node_number, int end_node_number, QVector<int>& way){

    QVector<int> track(g.size(), -1);
    QVector<double> shortest_dist(g.size(), std::numeric_limits<double>::infinity());
    QList<int> not_visited;
    for(auto i = 0; i < g.size(); i++)
        not_visited.push_back(i);

    shortest_dist[start_node_number] = 0;
    int curr = g.getNextNode(shortest_dist, not_visited);

    while(curr >= 0){

        QVector<int> neighbours;
        g.getNeighbours(curr, neighbours);

        for(auto i = 0; i < neighbours.size(); i++){
            if(_finite(shortest_dist[neighbours[i]])){

                double new_dist =  g.matrix[curr][neighbours[i]] + shortest_dist[curr];

                if(shortest_dist[neighbours[i]] > new_dist){
                    shortest_dist[neighbours[i]] = new_dist;
                    track[neighbours[i]] = curr;
                }
            }
            else{
                shortest_dist[neighbours[i]] = g.matrix[curr][neighbours[i]] + shortest_dist[curr];
                track[neighbours[i]] = curr;
            }
        }

        curr = g.getNextNode(shortest_dist, not_visited);
        neighbours.clear();
    }

    g.restoreShortestWay(start_node_number, end_node_number, track, way);
}

int Graph::size(){
    return this->node_names.size();
}

void Graph::printGraph(){

    std::cout << std::setw(5) << "" << "  ";
    for(auto i = 0; i < matrix.size(); i++){
        std::cout << std::setw(5) << node_names[i].toStdString() << "  ";
    }
    std::cout << std::endl << std::endl;

    for(auto i = 0; i < matrix.size(); i++){
        std::cout << std::setw(5) << node_names[i].toStdString() << "  ";
        for(auto j = 0; j < matrix[i].size(); j++){
            std::cout << std::setw(5) << matrix[i][j] << "  ";
        }
        std::cout << std::endl;
    }
}
