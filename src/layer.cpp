#include "layer.h"

#include <cmath>
#include <random>
#include <numeric>

Layer::Layer(uint inputs, uint neurons, QString activation) : _inputs(inputs) , _neurons(neurons) , _activation(activation) {
    std::default_random_engine generator;
    std::uniform_real_distribution<double> distribution(0.0, 1.0);

    // Generate weights
    weights.reserve(static_cast<int>(_inputs));
    for (uint i = 0; i < _inputs; ++i) {
        QList<double> row;
        row.reserve(static_cast<int>(_neurons));
        for (uint j = 0; j < _neurons; ++j) {
            row.append(distribution(generator));
        }
        weights.append(row);
    }

    // Generate biases
    biases.reserve(static_cast<int>(neurons));
    for (uint i = 0; i < _neurons; ++i) {
        biases.append(distribution(generator));
    }

    // Initialize errors and deltas (for easier re-assignment)
    for (uint i = 0; i < _neurons; ++i) {
        errors.append(0.0);
        deltas.append(0.0);
    }

    if (true /*debug*/) {
        if (inputs == 2 && neurons == 3) {
            weights = {
                {0.54340494, 0.27836939, 0.42451759},
                {0.84477613, 0.00471886, 0.12156912}
            };
            //activate({0, 0, 0});
        }

        if (inputs == 3 && neurons == 3) {
            /*weights = {
                {0.57509333, 0.89132195},
                {0.20920212, 0.18532822},
                {0.10837689, 0.21969749}
            };*/
            weights = {
                {0.57509333, 0.89132195, 0.20920212},
                {0.18532822, 0.10837689, 0.21969749},
                {0.97862378, 0.81168315, 0.17194101}
            };
            //activate({0.5, 0.5, 0.5});
        }

        if (inputs == 3 && neurons == 2) {
            weights = {
                {0.94002982, 0.81764938},
                {0.33611195, 0.17541045},
                {0.37283205, 0.00568851}
            };
        }
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
        //product += biases[i];

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
