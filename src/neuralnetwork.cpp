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
bool NeuralNetwork::train(Data data, Data results) {
    // Verify
    if (data.size() != results.size()) {
        return false;
    }

    _symbols = data;

    // Train
    QList<double> mses;
    for (uint i = 0; i < _epochs; ++i) {
        for (int j = 0; j < data.size(); ++j) {
            backPropagation(data[j], results[j]);
        }

        if (i % 10 == 0) {
            double mse = 0.0; //mean(square(results - feedForward(data)));
            mses.append(mse);
            qDebug() << "Epoch" << i << ":" << "MSE:" << mse;
        }
    }

    _trained = true;
    return true;
}

DataRow NeuralNetwork::predict(Data data) {
    DataRow predictions;
    for (int i = 0; i < data.size(); ++i) {
        data[i] = feedForward(data[i]);

        qDebug() << i << data[i];

        double prediction = std::distance(data[i].begin(), std::max_element(data[i].begin(), data[i].end()));
        predictions.append(prediction);
    }

    return predictions;
}

DataRow NeuralNetwork::feedForward(DataRow data) {
    for (auto &layer : _layers) {
        data = layer.activate(data);
    }
    return data;
}

void NeuralNetwork::backPropagation(DataRow data, DataRow results) {
    DataRow output = feedForward(data);

    // Loop over layers backwards
    //for (auto layerIt = _layers.end() - 1; layerIt != _layers.begin(); --layerIt) {
    auto layerIt = _layers.end();
    while (layerIt != _layers.begin()) {
        --layerIt;

        qDebug() << "layer";
        // If output layer
        if (layerIt == _layers.end() - 1) {
            // Error
            for (int i = 0; i < output.size(); ++i) {
                int results_i = (results.size() == 1) ? 0 : i;
                layerIt->errors[i] = results[results_i] - output[i];
            }
            //qDebug() << "results" << results << "output" << output << "error" << layerIt->errors;

            // Delta
            for (int i = 0; i < layerIt->errors.size(); ++i) {
                layerIt->deltas[i] = layerIt->errors[i] * layerIt->sigmoidDerivative(output[i]);
            }
            //qDebug() << "results" << results << "output" << output << "deltas" << layerIt->deltas;
        } else {
            auto nextLayerIt = layerIt++;

            // Error (dot product)
            for (int j = 0; j < nextLayerIt->weights.size(); ++j) { // Column length
                layerIt->errors[j] = 0.0;
                for (int i = 0; i < nextLayerIt->deltas.size(); ++i) { // Row length
                    layerIt->errors[j] += nextLayerIt->deltas[i] * nextLayerIt->weights[j][i];
                }
            }
            qDebug() << "next weights" << nextLayerIt->weights << "next deltas" << nextLayerIt->deltas << "error" << layerIt->errors;

            // Delta
            for (int i = 0; i < layerIt->errors.size(); ++i) {
                layerIt->deltas[i] = layerIt->errors[i] * layerIt->sigmoidDerivative(layerIt->lastActivation[i]);
            }
            //qDebug() << "results" << results << "output" << output << "deltas" << layerIt->deltas;
        }
    }
    qDebug() << "OVER";
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
