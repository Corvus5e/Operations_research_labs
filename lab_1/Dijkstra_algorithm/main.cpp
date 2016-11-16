#include <QCoreApplication>
#include <iostream>
#include <exception>

#include <graph.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    try{
        QStringList args = QCoreApplication::arguments();

        QString file(args.at(1));

        Graph g;
        Graph::readGraph(file, &g);

        std::cout << std::endl << "Graph has been read from \"" << file.toStdString() << "\" successfully." << std::endl;
        g.printGraph();        

        bool start_ok = false;
        bool end_ok = false;

        int start_node = args.at(2).toInt(&start_ok);
        int end_node = args.at(3).toInt(&end_ok);

        if( !(start_ok && end_ok) ){
            std::cout << std::endl << " Invalid node numbers." << std::endl;
            exit(EXIT_FAILURE);
        }

        if( (start_node >= g.size()) || (start_node < 0) || (end_node >= g.size()) || (end_node < 0)){
            std::cout << std::endl << "Node number out of range." << std::endl;
            exit(EXIT_FAILURE);
        }

        std::cout << "Startig node: " << start_node << std::endl;
        std::cout << "End node: " << end_node << std::endl;

        QVector<int> shortest_way;
        Graph::findShortestWay(g, start_node, end_node, shortest_way);

        std::cout << std::endl << "Shortest way:" << std::endl;
        for(auto i = 0; i < shortest_way.size(); i++){
            std::cout << g.getNodeName(shortest_way[i]).toStdString() << " --> ";
        }
        std::cout << std::endl;
    }
    catch(std::exception& e){
        std::cerr << e.what() << std::endl;
        exit(EXIT_FAILURE);
    }

    return 0;//a.exec();
}

