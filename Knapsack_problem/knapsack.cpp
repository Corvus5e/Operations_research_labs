
#include <knapsack.h>

#include <QFile>
#include <QTextStream>
#include <exception>
#include <iostream>
#include <iomanip>

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
