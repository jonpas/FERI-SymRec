#include "mainwindow.h"
#include <QApplication>

#include <QDebug>
#include "neuralnetwork.h"

int main(int argc, char *argv[]) {
    /*NeuralNetwork nn = NeuralNetwork(0, 3, 0.3, 0, 290);
    nn.addLayer(Layer(2, 3));
    nn.addLayer(Layer(3, 2));

    Data data = {{0, 0}, {0, 1}, {1, 0}, {1, 1}};
    Data results = {{0}, {0}, {0}, {1}};

    bool trained = nn.train(data, results);
    if (!trained) {
        qDebug() << "error training!";
        return 1;
    }

    //nn.predict({0, 1});
    DataRow predictions = nn.predict(data);
    qDebug() << "predictions:" << predictions;
    */

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
