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

#include <QDebug>
void NeuralNetwork::train(QList<Symbol> symbols) {
    _symbols = symbols;

    // Find out amount of out neurons (different possibilities)
    QList<char> characters;
    for (auto &symbol : symbols) {
        if (!characters.contains(symbol.symbol())) {
            characters.append(symbol.symbol());
        }
    }
    uint outsize = static_cast<uint>(characters.size());

    // Initialize layers
    layers.append(Layer(static_cast<uint>(symbolsTrained()), _hiddenNeurons));
    layers.append(Layer(_hiddenNeurons, outsize));

    // DEBUG
    double x = layers[1].activate(symbols[0].points());
    qDebug() << x;

    // Train
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
