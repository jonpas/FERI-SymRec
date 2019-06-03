#pragma once

#include <QList>
#include <QDebug>

#include "layer.h"

using ResultRow = QList<int>;
using Result = QList<ResultRow>;

// Flexible multi-Layer neural network
class NeuralNetwork {
public:
    NeuralNetwork(double learningRate = 0.25, double momentumConst = 0.5, uint maxEpochs = 2000, double minError = 0.005);
    ~NeuralNetwork();

    void addLayer(Layer layer);

    bool train(Data data, Result results);
    Result predict(Data data);

    DataRow feedForward(DataRow data);
    void backPropagate(DataRow data, ResultRow results);

    bool trained() const;

private:
    uint _hiddenNeurons;
    double _learningRate;
    double _momentumConst; // Not implemented
    uint _maxEpochs;
    double _minError;

    QList<Layer> _layers;
    bool _trained = false;
};
