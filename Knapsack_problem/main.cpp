#include <QCoreApplication>
#include <iostream>
#include <vector>
#include <knapsack.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    double max_weight = 0;
    QVector<orl::item> items;

    try{
        orl::readTask("tasks\\task_1.txt", max_weight, items);
        std::cout << "File opened" << std::endl;
        orl::printTask(max_weight, items);
    }
    catch(std::exception& e){
        std::cout << e.what() << std::endl;
    }

    return 0;//return a.exec();
}

