#pragma once

#include <QList>

using Data = QList<QList<double>>;
using DataRow = QList<double>;

class Layer {
public:
    Layer(uint inputs, uint neurons, QString activation = "sigmoid", QList<double> weightRandBound = {-0.5, 0.5}, QList<double> biasBounds = {0.0, 0.0});

    DataRow activate(DataRow data);

    double applyActivation(double x);
    double applyActivationDerivative(double x);

    // TODO privatize (?)
    Data weights;
    DataRow biases;

    DataRow errors;
    DataRow deltas;
    DataRow lastActivation;

private:
    uint _inputs;
    uint _neurons;

    QString _activation;
};
