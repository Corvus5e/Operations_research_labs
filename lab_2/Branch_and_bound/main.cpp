
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
        orl::branchBoundShortestWay(g, 1, 1, shortest_way);
        std::cout << shortest_way.back() << std::endl;

    }
    catch(std::exception& e){
        std::cout << e.what() << std::endl;
    }

    return 0;//a.exec();
}

