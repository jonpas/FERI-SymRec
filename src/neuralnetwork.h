#pragma once

#include <QtGlobal>
#include <vector>

#include "neuron.h"

using Layer = std::vector<Neuron>;

// Multi-Layer neural network with 1 hidden layer
class NeuralNetwork {
public:
    NeuralNetwork(uint hiddenNeurons = 15, double learningRate = 0.25, double momentumConst = 0.5, uint epochs = 2000, double minError = 0.005);
    ~NeuralNetwork();

    void train();
    char recognize();

    bool isTrained() const;
    uint getSymbolsTrained() const;

private:
    uint hiddenNeurons;
    double learningRate;
    double momentumConst; // Not implemented
    uint epochs;
    double minError;

    Layer layerIn;
    Layer layerHidden;
    Layer layerOut;

    bool trained = false;
    uint symbolsTrained = 0;
};
