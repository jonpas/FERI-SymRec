#include "neuralnetwork.h"

NeuralNetwork::NeuralNetwork(double learningRate,
                             double momentumConst,
                             uint epochs,
                             double minError)
        : _learningRate(learningRate)
        , _momentumConst(momentumConst)
        , _epochs(epochs)
        , _minError(minError) {
}

NeuralNetwork::~NeuralNetwork() {
}

void NeuralNetwork::addLayer(Layer layer) {
    _layers.append(layer);
}

bool NeuralNetwork::train(Data data, Data results) {
    // Verify
    if (data.size() != results.size()) {
        return false;
    }

    // Train
    for (uint i = 0; i < _epochs; ++i) {
        for (int j = 0; j < data.size(); ++j) {
            backPropagate(data[j], results[j]);
        }
    }

    _trained = true;
    return true;
}

DataRow NeuralNetwork::predict(Data data) {
    DataRow predictions;

    for (auto &dataRow : data) {
        dataRow = feedForward(dataRow);
        qInfo() << "Probabilities:" << dataRow;

        double prediction = std::distance(dataRow.begin(), std::max_element(dataRow.begin(), dataRow.end()));
        predictions.append(prediction);
    }

    qInfo() << "-> Predictions:" << predictions;

    return predictions;
}

DataRow NeuralNetwork::feedForward(DataRow data) {
    for (auto &layer : _layers) {
        data = layer.activate(data);
    }
    return data;
}

void NeuralNetwork::backPropagate(DataRow data, DataRow results) {
    DataRow output = feedForward(data);

    // Loop over layers backwards
    auto layerIt = _layers.end();
    while (layerIt != _layers.begin()) {
        --layerIt;

        // If output layer
        if (layerIt == _layers.end() - 1) {
            // Error
            for (int i = 0; i < output.size(); ++i) {
                int resultsIndex = (results.size() == 1) ? 0 : i;
                layerIt->errors[i] = results[resultsIndex] - output[i];
            }

            // Delta
            for (int i = 0; i < layerIt->errors.size(); ++i) {
                layerIt->deltas[i] = layerIt->errors[i] * layerIt->applyActivationDerivative(output[i]);
            }
        } else {
            auto nextLayerIt = layerIt + 1;

            // Error (dot product)
            for (int j = 0; j < nextLayerIt->weights.size(); ++j) { // Column length
                layerIt->errors[j] = 0.0;
                for (int i = 0; i < nextLayerIt->deltas.size(); ++i) { // Row length
                    layerIt->errors[j] += nextLayerIt->deltas[i] * nextLayerIt->weights[j][i];
                }
            }

            // Delta
            for (int i = 0; i < layerIt->errors.size(); ++i) {
                layerIt->deltas[i] = layerIt->errors[i] * layerIt->applyActivationDerivative(layerIt->lastActivation[i]);
            }
        }
    }

    for (int i = 0; i < _layers.size(); ++i) {
        DataRow inputToUse = data;
        if (i != 0) {
            inputToUse = _layers[i - 1].lastActivation;
        }

        for (int j = 0; j < _layers[i].weights.size(); ++j) {
            for (int k = 0; k < _layers[i].weights[j].size(); ++k) {
                _layers[i].weights[j][k] += _layers[i].deltas[k] * inputToUse[j] * _learningRate;
            }
        }
    }
}

bool NeuralNetwork::trained() const {
    return _trained;
}
