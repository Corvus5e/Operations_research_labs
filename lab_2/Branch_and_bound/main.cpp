
#include <QCoreApplication>
#include <iostream>
#include "graph.h"
#include <orl_algorithms.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    try{
        orl::Graph g;
        orl::Graph::readGraph("1.txt", &g);
        g.printGraph();

        QVector<int> shortest_way;
        orl::branchBoundShortestWay(g, g.nodeIndex("A"), g.nodeIndex("G"), shortest_way);

        for(auto i = 0 ; i < shortest_way.size(); i++){
            std::cout << g.nodeName(shortest_way[i]).toStdString() << " <-- ";
        }

    }
    catch(std::exception& e){
        std::cout << e.what() << std::endl;
    }

    return 0;//a.exec();
}

