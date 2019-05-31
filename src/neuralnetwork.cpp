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

void NeuralNetwork::addLayer(Layer layer) {
    _layers.append(layer);
}

#include <QDebug>
void NeuralNetwork::train(QList<Symbol> symbols) {
    _symbols = symbols;

    // Find out amount of out neurons (different possibilities)
    /*QList<char> characters;
    for (auto &symbol : symbols) {
        if (!characters.contains(symbol.symbol())) {
            characters.append(symbol.symbol());
        }
    }
    uint outsize = static_cast<uint>(characters.size());

    // Initialize layers
    _layers.append(Layer(static_cast<uint>(symbolsTrained()), _hiddenNeurons));
    _layers.append(Layer(_hiddenNeurons, outsize));
    */

    // DEBUG
    //double x = layers[1].activate(symbols[0].points());
    //qDebug() << x;

    // Train
    for (uint i = 0; i < _epochs; ++i) {
        // feedforward();
        // backpropagation();
    }

    _trained = true;
}

char NeuralNetwork::predict(Data data) {
    // TODO
    data = feedForward(data);

    qDebug() << "predictions:" << data;


    return '2';
}

int NeuralNetwork::feedForward(Data data) {
    int output;
    for (auto &layer : _layers) {
        output = layer.activate(data);
    }

    return output;
}

void NeuralNetwork::backPropagation(Data data, Results results) {
    int output = feedForward(data);

    // Loop over layers backwards
    for (auto layerIt = _layers.end() - 1; layerIt != _layers.begin(); --layerIt) {
        // If output layer
        if (layerIt == _layers.end() - 1) {
            layerIt->error = 0;//results - output;
            layerIt->delta = layerIt->error * layerIt->sigmoidDerivative(output);
        }
    }
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
