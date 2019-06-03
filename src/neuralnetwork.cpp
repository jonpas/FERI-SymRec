#include "neuralnetwork.h"

#include <cmath>

NeuralNetwork::NeuralNetwork(double learningRate,
                             double momentumConst,
                             uint maxEpochs,
                             double minError)
        : _learningRate(learningRate)
        , _momentumConst(momentumConst)
        , _maxEpochs(maxEpochs)
        , _minError(minError) {
}

NeuralNetwork::~NeuralNetwork() {
}

void NeuralNetwork::addLayer(Layer layer) {
    _layers.append(layer);
}

bool NeuralNetwork::train(Data data, Result results) {
    // Verify
    if (data.size() != results.size()) {
        return false;
    }

    // Train
    for (uint i = 0; i < _maxEpochs; ++i) {
        for (int j = 0; j < data.size(); ++j) {
            backPropagate(data[j], results[j]);
        }

        // Calculate mean squared error (MSE) every 10th epoch
        // Exit training if minimal error reached before max epochs
        if (i % 10 == 0) {
            DataRow outputsFlat;
            for (int j = 0; j < data.size(); ++j) {
                DataRow row = feedForward(data[j]);
                for (int k = 0; k < row.size(); ++k) {
                    int resultIndex = std::min(k, results[j].size() - 1);
                    row[k] = pow(results[j][resultIndex] - row[k], 2);
                }
                outputsFlat.append(row);
            }

            double sum = std::accumulate(outputsFlat.begin(), outputsFlat.end(), 0.0);
            double mse = sum / outputsFlat.size();
            qInfo() << "MSE" << i << "=" << mse;

            if (mse <= _minError) {
                break;
            }
        }
    }

    _trained = true;
    return true;
}

Result NeuralNetwork::predict(Data data) {
    Result predictions;

    for (auto &dataRow : data) {
        dataRow = feedForward(dataRow);
        qInfo() << "Probabilities:" << dataRow;

        int predictionIndex = static_cast<int>(std::distance(dataRow.begin(), std::max_element(dataRow.begin(), dataRow.end())));

        ResultRow prediction;
        for (int i = 0; i < dataRow.size(); ++i) {
            prediction.append(i == predictionIndex ? 1 : 0);
        }
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

void NeuralNetwork::backPropagate(DataRow data, ResultRow results) {
    DataRow output = feedForward(data);

    // Loop over layers backwards
    auto layerIt = _layers.end();
    while (layerIt != _layers.begin()) {
        --layerIt;

        // If output layer
        if (layerIt == _layers.end() - 1) {
            // Error
            for (int i = 0; i < output.size(); ++i) {
                int resultIndex = std::min(i, results.size() - 1);
                layerIt->errors[i] = results[resultIndex] - output[i];
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
