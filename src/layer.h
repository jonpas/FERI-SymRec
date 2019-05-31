#pragma once

#include <QList>

using Data = QList<QList<int>>;
using Results = QList<int>;

class Layer {
public:
    Layer(uint inputs, uint neurons);
    ~Layer();

    int activate(Data data);

    double sigmoid(double x);
    double sigmoidDerivative(double x);

    double error;
    double delta;

private:
    QList<QPointF> weights;
};
