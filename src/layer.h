#pragma once

#include <QList>

class Layer {
public:
    Layer(uint inputs, uint neurons);
    ~Layer();

    double activate(QList<QPointF> points);

    double sigmoid(double x);
    double sigmoidDerivative(double x);

private:
    QList<QList<QPointF>> weights;
};
