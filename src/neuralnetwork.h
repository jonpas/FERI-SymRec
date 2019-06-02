#pragma once

#include <QList>

#include "layer.h"
#include "symbol.h"

// Multi-Layer neural network
class NeuralNetwork {
public:
    NeuralNetwork(uint symbolPoints = 15, uint hiddenNeurons = 15, double learningRate = 0.25, double momentumConst = 0.5, uint epochs = 2000, double minError = 0.005);
    ~NeuralNetwork();

    void addLayer(Layer layer);

    bool train(Data data, Data results);
    DataRow predict(Data data);

    DataRow feedForward(DataRow data);
    void backPropagate(DataRow data, DataRow results);

    uint symbolPoints() const;
    bool trained() const;
    int symbolsTrained() const;

private:
    uint _symbolPoints;
    uint _hiddenNeurons;
    double _learningRate;
    double _momentumConst; // Not implemented
    uint _epochs;
    double _minError;

    QList<Layer> _layers;

    Data _symbols;
    bool _trained = false;
};
