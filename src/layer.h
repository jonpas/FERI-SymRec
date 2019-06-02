#pragma once

#include <QList>

using Data = QList<QList<double>>;
using DataRow = QList<double>;

class Layer {
public:
    Layer(uint inputs, uint neurons);
    ~Layer();

    DataRow activate(DataRow data);

    double sigmoid(double x);
    double sigmoidDerivative(double x);

    // TODO privatize (?)
    Data weights;

    DataRow errors;
    DataRow deltas;
    DataRow lastActivation;

private:
    uint _inputs;
    uint _neurons;
};
