#ifndef KNAPSACK
#define KNAPSACK

#include <QVector>
#include <QString>

namespace orl {

struct item {
    QString name;
    double weight;
    double price;
    int number; // maximum number of this item that can be put in knapsack

    item(){ }

    item(QString name, double weight, double price, int number): name(name), weight(weight), price(price), number(number){ }
};

void readTask(const QString& file, double& max_weight, QVector<item>& items);

void printTask(const double& max_weight, const QVector<item>& items);

}

#endif // KNAPSACK

