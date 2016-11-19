
#include <QCoreApplication>
#include <iostream>
#include <orl_algorithms.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QStringList args = QCoreApplication::arguments();
    if(args.size() < 3){
        std::cout << "Need more parameters." << std::endl;
        exit(EXIT_FAILURE);
    }
    const QString file = args.at(1);
    const QString start_node_name = args.at(2);
    const QString end_node_name = args.at(3);

    try{
        orl::Graph g;
        orl::Graph::readGraph(file, &g);
        g.printGraph();

        QVector<int> shortest_way;
        //orl::branchBoundShortestWay(g, g.nodeIndex(start_node_name), g.nodeIndex(end_node_name), shortest_way);
        orl::dijkstraShortestWay(g, g.nodeIndex(start_node_name), g.nodeIndex(end_node_name), shortest_way);

        if(shortest_way.size() > 0){
            std::cout << "Shortest way : " << std::endl;
            for(auto i = 0 ; i < shortest_way.size(); i++){
                std::cout << g.nodeName(shortest_way[i]).toStdString() << " --> ";
            }
        }
        else {
            std::cout << "No way " << std::endl;
        }

    }
    catch(std::exception& e){
        std::cout << e.what() << std::endl;
    }

    return 0;//a.exec();
}

