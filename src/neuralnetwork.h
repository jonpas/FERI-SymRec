#pragma once

#include <QList>

#include "layer.h"

// Multi-Layer neural network
class NeuralNetwork {
public:
    NeuralNetwork(uint hiddenNeurons = 20, double learningRate = 0.25, double momentumConst = 0.5, uint epochs = 2000, double minError = 0.005);
    ~NeuralNetwork();

    void setData(Data);
    void addLayer(Layer layer);

    bool train(Data data, Data results);
    DataRow predict(Data data);

    DataRow feedForward(DataRow data);
    void backPropagate(DataRow data, DataRow results);

    bool trained() const;

private:
    uint _hiddenNeurons;
    double _learningRate;
    double _momentumConst; // Not implemented
    uint _epochs;
    double _minError;

    QList<Layer> _layers;
    bool _trained = false;
};
