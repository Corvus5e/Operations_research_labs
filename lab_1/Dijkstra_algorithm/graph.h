#ifndef GRAPH_H
#define GRAPH_H

#include <QString>
#include <QVector>

class Graph
{
private:

    QVector<QString> node_names;
    QVector<QVector<double>> matrix; // connection matrix

    void initNodeNames(const QStringList& list);
    void addMatrixRow(const QStringList& values);
    void getNeighbours(int node_number, QVector<int>& neighbours);
    int getNextNode(const QVector<double>& dists, QList<int>& not_visited);
    void restoreShortestWay(int from, int to, QVector<int>& track, QVector<int>& way);

public:

    Graph();    
    void printGraph();    
    QString& getNodeName(int node_number);
    int size();

    static void readGraph(const QString& file, Graph* graph);
    static void findShortestWay(Graph& graph, int start_node_nuber, int end_node_number, QVector<int>& way);
};

#endif // GRAPH_H
