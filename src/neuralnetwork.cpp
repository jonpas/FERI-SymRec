#include "neuralnetwork.h"

NeuralNetwork::NeuralNetwork(uint symbolPoints,
                             uint hiddenNeurons,
                             double learningRate,
                             double momentumConst,
                             uint epochs,
                             double minError)
        : _symbolPoints(symbolPoints)
        , _hiddenNeurons(hiddenNeurons)
        , _learningRate(learningRate)
        , _momentumConst(momentumConst)
        , _epochs(epochs)
        , _minError(minError) {
}

NeuralNetwork::~NeuralNetwork() {
}

void NeuralNetwork::train(QList<Symbol> symbols) {
    _symbols = symbols;

    for (uint i = 0; i < _epochs; ++i) {
        // feedforward();
        // backpropagation();
    }

    _trained = true;
}

char NeuralNetwork::recognize(QList<QPointF> points) {
    // TODO

    return '2';
}

uint NeuralNetwork::symbolPoints() const {
    return _symbolPoints;
}

bool NeuralNetwork::trained() const {
    return _trained;
}

int NeuralNetwork::symbolsTrained() const {
    return _symbols.size();
}
