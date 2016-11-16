#include <QCoreApplication>
#include <iostream>
#include <exception>

#include <graph.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QString file(argv[1]);
    std::cout << file.toStdString() << std::endl;
    Graph g;

    try{
        Graph::readGraph(file, &g);
        std::cout << "Graph has been read." << std::endl;
        g.printGraph();
        QVector<int> shortest_way;
        Graph::findShortestWay(g, 0, 5, shortest_way);

        std::cout << "Shortest way:" << std::endl;
        for(auto i = 0; i < shortest_way.size(); i++){
            std::cout << g.getNodeName(shortest_way[i]).toStdString() << " --> ";
        }
        std::cout << std::endl;
    }
    catch(std::exception& e){
        std::cerr << e.what() << std::endl;
    }

    return 0;//a.exec();
}

