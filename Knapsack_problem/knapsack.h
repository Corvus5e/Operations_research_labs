#ifndef KNAPSACK
#define KNAPSACK

#include <QVector>
#include <QString>

namespace orl {

struct item {
    QString name;
    int weight;
    int price;
    int number; // maximum number of this item that can be put in knapsack

    item(){ }

    item(QString name, double weight, double price, int number): name(name), weight(weight), price(price), number(number){ }
};

void readTask(const QString& file, double& max_weight, QVector<item>& items);

void printTask(const double& max_weight, const QVector<item>& items);

// item_indexes : first - index, secon - number of this item
// return max price of knapsack
int findBestKnapsack(const QVector<item>& items, int max_weight, QVector<std::pair<int, int>>& items_indexes);

}

#endif // KNAPSACK

