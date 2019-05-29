#include "neuralnetwork.h"

NeuralNetwork::NeuralNetwork(uint hiddenNeurons, double learningRate, double momentumConst, uint epochs, double minError) {
}

NeuralNetwork::~NeuralNetwork() {
}

void NeuralNetwork::train() {
    // TODO

    trained = true;
}

bool NeuralNetwork::isTrained() const {
    return trained;
}

uint NeuralNetwork::getSymbolsTrained() const {
    return symbolsTrained;
}
