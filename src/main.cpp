#include "mainwindow.h"
#include <QApplication>

#include "neuralnetwork.h"

int main(int argc, char *argv[]) {
    // Binary AND - Neural Network testing
    /*
    NeuralNetwork nn = NeuralNetwork(0.3, 0, 290);
    nn.addLayer(Layer(2, 3, "tanh", {0.0, 0.5}, {0.0, 0.99}));
    nn.addLayer(Layer(3, 3, "sigmoid", {0.5, 0.99}, {0.0, 0.99}));
    nn.addLayer(Layer(3, 2, "sigmoid", {0.5, 0.99}, {0.0, 0.99}));

    Data data = {{0, 0}, {0, 1}, {1, 0}, {1, 1}};
    Data results = {{0}, {0}, {0}, {1}};

    if (!nn.train(data, results)) return 1;
    nn.predict(data);
    */

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
