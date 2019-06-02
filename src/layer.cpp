#include "layer.h"

#include <cmath>
#include <random>
#include <numeric>

Layer::Layer(uint inputs, uint neurons, QString activation, QList<double> weightBounds, QList<double> biasBounds)
        : _inputs(inputs), _neurons(neurons), _activation(activation) {
    std::default_random_engine generator;
    std::uniform_real_distribution<double> distWeight(weightBounds[0], weightBounds[1]);
    std::uniform_real_distribution<double> distBias(biasBounds[0], biasBounds[1]);

    // Generate weights
    weights.reserve(static_cast<int>(_inputs));
    for (uint i = 0; i < _inputs; ++i) {
        QList<double> row;
        row.reserve(static_cast<int>(_neurons));
        for (uint j = 0; j < _neurons; ++j) {
            row.append(distWeight(generator));
        }
        weights.append(row);
    }

    // Generate biases
    biases.reserve(static_cast<int>(_neurons));
    for (uint i = 0; i < _neurons; ++i) {
        biases.append(distBias(generator));
    }

    // Initialize errors and deltas (for easier re-assignment)
    for (uint i = 0; i < _neurons; ++i) {
        errors.append(0.0);
        deltas.append(0.0);
    }
}

DataRow Layer::activate(DataRow data) {
    DataRow products;
    for (int i = 0; i < static_cast<int>(_neurons); ++i) { // Row length
        // Calculate dot product of data and weights
        double product = 0.0;
        for (int j = 0; j < static_cast<int>(_inputs); ++j) { // Column length
            product += data[j] * weights[j][i];
        }

        // Bias
        product += biases[i];

        // Apply activation function
        product = applyActivation(product);

        products.append(product);
    }

    lastActivation = products;
    return products;
}

double Layer::applyActivation(double x) {
    if (_activation == "sigmoid") {
        return 1 / (1 + exp(-x));
    } else if (_activation == "tanh") {
        return tanh(x);
    }
    return x;
}

double Layer::applyActivationDerivative(double x) {
    if (_activation == "sigmoid") {
        return x * (1 - x);
    } else if (_activation == "tanh") {
        return 1 - pow(x, 2);
    }
    return x;
}
