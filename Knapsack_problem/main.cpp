#include <QCoreApplication>
#include <iostream>
#include <iomanip>
#include <vector>
#include <knapsack.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QStringList args = QCoreApplication::arguments();
    if(args.size() < 2){
        std::cout << "Few arguments. Need file name." << std::endl;
        exit(EXIT_FAILURE);
    }


    try{
        const int column_width = 5;

        double max_weight = 0;
        QVector<orl::item> items;

        orl::readTask(args.back(), max_weight, items);
        orl::printTask(max_weight, items);

        QVector<std::pair<int,int>> answer; // item indexes
        int max_price = orl::findBestKnapsack(items, max_weight, answer);

        std::cout << "Max price: " << max_price << std::endl;
        std::cout << "Items in knapsack:" << std::endl;
        std::cout << std::setw(column_width) << "Name ";
        std::cout << std::setw(column_width) << "Number" << std::endl;
        for(auto i = 0; i < answer.size(); i++){
            std::cout << items[answer[i].first].name.toStdString() <<
                         std::setw(column_width) << answer[i].second <<
                         std::endl;
        }
        std::cout << std::endl;

    }
    catch(std::exception& e){
        std::cout << e.what() << std::endl;
    }

    return 0;//return a.exec();
}

