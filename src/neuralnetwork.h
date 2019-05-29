#pragma once

#include <vector>

#include "neuron.h"

using Layer = std::vector<Neuron>;

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
