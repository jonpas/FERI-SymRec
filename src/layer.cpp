#include "layer.h"

#include <cmath>
#include <random>
#include <numeric>

Layer::Layer(uint inputs, uint neurons) : _inputs(inputs), _neurons(neurons) {
    std::default_random_engine generator;
    std::uniform_real_distribution<double> distribution(0.0, 1.0);

    // Generate weights
    weights.reserve(static_cast<int>(inputs));
    for (uint i = 0; i < _inputs; ++i) {
        QList<double> row;
        row.reserve(static_cast<int>(neurons));
        for (uint j = 0; j < _neurons; ++j) {
            row.append(distribution(generator));
        }
        weights.append(row);
    }

    // Initialize errors and deltas (for easier re-assignment)
    for (uint i = 0; i < _neurons; ++i) {
        errors.append(0.0);
        deltas.append(0.0);
    }

    /*weights = {
        {0.54340494, 0.27836939, 0.42451759},
        {0.84477613, 0.00471886, 0.12156912}
    };
    activate({0, 0, 0});*/

    /*weights = {
        {0.57509333, 0.89132195},
        {0.20920212, 0.18532822},
        {0.10837689, 0.21969749}
    };
    activate({0.5, 0.5, 0.5});*/
}

Layer::~Layer() {
}

DataRow Layer::activate(DataRow data) {
    // Calculate dot product of data and weights
    DataRow products;
    for (int i = 0; i < static_cast<int>(_neurons); ++i) { // Row length
        double product = 0.0;
        for (int j = 0; j < static_cast<int>(_inputs); ++j) { // Column length
            product += data[j] * weights[j][i];
        }

        // Apply activation function
        product = sigmoid(product);
        products.append(product);
    }

    lastActivation = products;
    return products;
}

double Layer::sigmoid(double x) {
    return 1 / (1 + exp(-x));
}

double Layer::sigmoidDerivative(double x) {
    return x * (1 - x);
}
