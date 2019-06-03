#pragma once

#include <QList>

using DataRow = QList<double>;
using Data = QList<DataRow>;

class Layer {
public:
    Layer(uint inputs, uint neurons, QString activation = "sigmoid", QList<double> weightRandBound = {-0.5, 0.5}, QList<double> biasBounds = {0.0, 0.0});

    DataRow activate(DataRow data);

    double applyActivation(double x);
    double applyActivationDerivative(double x);

    // Modified by Neural Network
    Data weights;
    DataRow errors;
    DataRow deltas;
    DataRow lastActivation;

private:
    uint _inputs;
    uint _neurons;

    DataRow _biases;
    QString _activation;
};
