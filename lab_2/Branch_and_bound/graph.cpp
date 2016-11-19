
#include "graph.h"

#include <QFile>
#include <QTextStream>
#include <exception>
#include <iostream>
#include <iomanip>

using namespace orl;

Graph::Graph()
{

}

void Graph::readGraph(const QString &file, Graph *graph)
{
    QFile f(file);
    if(!f.open(QIODevice::ReadOnly | QIODevice::Text)){
        std::string msg("Failed to open file ");
        msg.append(file.toStdString());

        throw std::exception(msg.c_str());
    }

    QTextStream in(&f);

    // reads 1st line as list of nodes names and init adjacency_matrix size of corresponding size
    if(!in.atEnd()){
        QString line =  in.readLine();
        QStringList names = line.split(QRegExp("\\s+"), QString::SkipEmptyParts);

        graph->initNodesNames(names);
        graph->initMatrixSize(names.size());
    }

    int row_number = 0;

    // parse each row
    while(!in.atEnd()){
      QString line =  in.readLine();
      QStringList values = line.split(QRegExp("\\s+"), QString::SkipEmptyParts);
      if(values.size() != graph->node_name_index.size())
          throw std::exception("Number of nodes names and connection are not equal");

      //converst each value as weight between nodes.
      //0.0 if convertion fails(no connection between nodes)
      for(auto i = 0; i < values.size(); i++){
          graph->setWeight(row_number, i, values[i].toDouble());
      }
      row_number++;
    }
}

int Graph::nodeIndex(const QString &node_name)
{
    if(node_name_index.contains(node_name))
        return node_name_index[node_name];
    throw std::exception("Invalid node name");
}

const QString& Graph::nodeName(int index){
    return (this->node_name_index.begin()+index).key();
}

void Graph::printGraph()
{
    std::cout << std::endl;
    std::cout << std::setw(5) << "" << "  ";
    for(auto i = 0; i < adjacency_matrix.size(); i++){
        std::cout << std::setw(5) << nodeName(i).toStdString() << "  ";
    }
    std::cout << std::endl << std::endl;

    for(auto i = 0; i < adjacency_matrix.size(); i++){
        std::cout << std::setw(5) << nodeName(i).toStdString() << "  ";
        for(auto j = 0; j < adjacency_matrix[i].size(); j++){
            std::cout << std::setw(5) << adjacency_matrix[i][j] << "  ";
        }
        std::cout << std::endl;
    }
}

double Graph::weight(int start_node_index, int end_node_index){
    return adjacency_matrix[start_node_index][end_node_index];
}

int Graph::size(){
    return this->node_name_index.size();
}

void Graph::neighbours(int node_index, QVector<int> &neighbours_indexes)
{
    for(auto i = 0; i < this->size(); i++){
        if(adjacency_matrix[node_index][i] != 0){
            neighbours_indexes.push_back(i);
        }
    }
}

// private

void Graph::initNodesNames(const QStringList &names)
{
    for(auto i = 0; i < names.size(); i++){
        this->node_name_index[names[i]] = i;
    }
}

void Graph::initMatrixSize(int size){
    this->adjacency_matrix.resize(size);
    for(auto i = this->adjacency_matrix.begin(); i != this->adjacency_matrix.end(); ++i){
        i->resize(size);
    }
}

void Graph::setWeight(int start_node_index, int end_node_index, double weight)
{
    this->adjacency_matrix[start_node_index][end_node_index] = weight;
}

