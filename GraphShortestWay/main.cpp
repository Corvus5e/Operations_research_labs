
#include <QCoreApplication>
#include <iostream>
#include <orl_algorithms.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QStringList args = QCoreApplication::arguments();
    if(args.size() < 5){
        std::cout << "Need more parameters." << std::endl;
        exit(EXIT_FAILURE);
    }

    QMap<QString, int> algo_map;
    algo_map.insert("Dijkstra", 1);
    algo_map.insert("Branch_and_bound", 2);

    const QString file = args.at(1);
    const QString start_node_name = args.at(2);
    const QString end_node_name = args.at(3);
    const QString algorithm_name = args.at(4);

    try{
        orl::Graph g;
        orl::Graph::readGraph(file, &g);
        g.printGraph();

        QVector<int> shortest_way;

        switch (algo_map[algorithm_name]) {
        case 1:
            orl::dijkstraShortestWay(g, g.nodeIndex(start_node_name), g.nodeIndex(end_node_name), shortest_way);
            break;
        case 2:
            orl::branchBoundShortestWay(g, g.nodeIndex(start_node_name), g.nodeIndex(end_node_name), shortest_way);
            break;
        default:
            std::cout << "Unknowk algorithm." << std::endl;
            exit(EXIT_FAILURE);
            break;
        }

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

