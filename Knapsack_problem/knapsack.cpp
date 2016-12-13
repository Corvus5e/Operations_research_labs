
#include <knapsack.h>

#include <QFile>
#include <QTextStream>
#include <exception>
#include <iostream>
#include <iomanip>
#include <utility>

void orl::readTask(const QString& file, double &max_weight, QVector<item> &items)
{
    QFile f(file);
    if(!f.open(QIODevice::ReadOnly | QIODevice::Text)){
        std::string msg("Failed to open file ");
        msg.append(file.toStdString());
        throw std::exception(msg.c_str());
    }

    QTextStream in(&f);

    if(!in.atEnd()){
        QString first_line = in.readLine();
        QStringList max_weight_line = first_line.split(QRegExp("\\s+"), QString::SkipEmptyParts);

        if(max_weight_line.size() >= 2)
            max_weight = max_weight_line[1].toDouble();
        else
            max_weight = 0.0; // default value
    }

    int row_number = 1;

    while(!in.atEnd()){
        QString line = in.readLine();
        if(row_number >= 2){
            QStringList values = line.split(QRegExp("\\s+"), QString::SkipEmptyParts);
            if(values.size() == 4){
                double weight = values[1].toDouble();
                double price = values[2].toDouble();
                int number = values[3].toInt();
                items.push_back(item(values[0], weight, price, number));
            }
            else{
                throw std::exception("File has wrong format");
            }
        }
        row_number++;
    }

}

void orl::printTask(const double &max_weight, const QVector<item> &items)
{
    std::cout << "Max weight: " << max_weight << std::endl;

    std::cout << std::setw(5) << "Name ";
    std::cout << std::setw(5) << "Weight ";
    std::cout << std::setw(5) << "Price ";
    std::cout << std::setw(5) << "Number " << std::endl;

    for(auto it = items.begin(); it != items.end(); ++it){
        std::cout << std::setw(5) << it->name.toStdString() << " ";
        std::cout << std::setw(5) << it->weight << " ";
        std::cout << std::setw(5) << it->price << " ";
        std::cout << std::setw(5) << it->number << " " << std::endl;
    }
    std::cout << std::endl;
}

void restoreItemIndexes(int item, int weight, const QVector<QVector<int>>& prices, QVector<int>& items_number, const QVector<orl::item>& items, QVector<std::pair<int, int>>& items_indexes)
{
    if(prices[item][weight] == 0)
        return;

    if(prices[item-1][weight] == prices[item][weight]){
        restoreItemIndexes(item-1, weight, prices, items_number, items, items_indexes);
    }
    else{
        restoreItemIndexes(item-1, weight - items[item-1].weight*items_number[item-1], prices, items_number, items, items_indexes);
        items_indexes.push_back(std::make_pair(item-1, items_number[item-1]));

    }
}

int orl::findBestKnapsack(const QVector<item> &items, int max_weight, QVector<std::pair<int, int>>& items_indexes)
{
    int items_rows = items.size() + 1;

    QVector<QVector<int>> prices(items_rows); // shoud be zero line

    // construct matrix of prices
    for(auto i = 0; i < items_rows; i++){
        prices[i].resize(max_weight + 1);
    }

    //stores number of each item, that have been put into knapsack
    QVector<int> items_number(items.size(), 1);

    // Bounded knapsack solving
    for(auto i = 1; i < items_rows; i++){
        const item& curr_item = items[i-1];
        for(auto c = 1; c <= max_weight; c++){
            prices[i][c] = prices[i-1][c];
            for(int l = std::min(curr_item.number, c/curr_item.weight); l >= 1; l--){
                int new_price = prices[i-1][c-l*curr_item.weight] + l*curr_item.price;
                if( new_price > prices[i][c]){
                    prices[i][c] = new_price;
                    items_number[i-1] = l;
                }
            }
        }
    }

    restoreItemIndexes(items_rows-1, max_weight, prices, items_number, items, items_indexes);

    return prices[items_rows-1][max_weight];
}
