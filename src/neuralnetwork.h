#pragma once

#include <QtGlobal>
#include <vector>

#include "neuron.h"
#include "symbol.h"

using Layer = std::vector<Neuron>;

// Multi-Layer neural network with 1 hidden layer
class NeuralNetwork {
public:
    NeuralNetwork(uint symbolPoints = 15, uint hiddenNeurons = 15, double learningRate = 0.25, double momentumConst = 0.5, uint epochs = 2000, double minError = 0.005);
    ~NeuralNetwork();

    void train(QList<Symbol> symbols);
    char recognize(QList<QPointF> points);

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

    Layer layerIn;
    Layer layerHidden;
    Layer layerOut;

    QList<Symbol> _symbols;
    bool _trained = false;
};
