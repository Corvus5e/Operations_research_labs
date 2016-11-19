#ifndef GRAPH_H
#define GRAPH_H

#include <QVector>
#include <QMap>
#include <QString>

namespace orl { // operations research labs


    class Graph
    {
    private:

        QVector<QVector<double>> adjacency_matrix;

        QMap<QString, int>  node_name_index;        

    public:

        Graph();

        int nodeIndex(const QString& node_name);

        const QString& nodeName(int index);

        double  weight(int start_node_index, int end_node_index);

        void neighbours(int node_index, QVector<int>& neighbours_indexes);

        void printGraph();

        int size();

        static void readGraph(const QString& file, Graph* graph);

    private:

        void setWeight(int start_node_index, int end_node_index, double weight);

        void initNodesNames(const QStringList& names);

        void initMatrixSize(int size);
    };
}
#endif // GRAPH_H
