#pragma once

#include <vector>

#include "neuron.h"

typedef std::vector<Neuron> Layer;

// Multi-Layer neural network with 1 hidden layer
class NeuralNetwork {
public:
    NeuralNetwork();
    ~NeuralNetwork();

    void learn();

private:
    Layer layerIn;
    Layer layerHidden;
    Layer layerOut;
};
