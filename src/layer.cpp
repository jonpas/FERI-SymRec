#include "layer.h"

#include <cmath>
#include <random>
#include <numeric>

Layer::Layer(uint inputs, uint neurons) {
    std::default_random_engine generator;
    std::uniform_real_distribution<double> distribution(0.0, 1.0);

    // TODO Generate weights
    weights.reserve(static_cast<int>(inputs));
    /*for (uint i = 0; i < inputs; ++i) {
        QList<QPointF> points;
        for (uint j = 0; j < neurons; ++j) {
            points.append(QPointF(distribution(generator), distribution(generator)));
        }
        weights.append(points);
    }*/
}

Layer::~Layer() {
}

int Layer::activate(Data data) {
    // calculate dot product points and weights
    //double x = std::inner_product(points.begin(), points.end(), weights.begin(), 0.0, std::plus<double>(), QPointF::dotProduct);

    // apply activation function
    //return sigmoid(x);

    return sigmoid(1);
}

double Layer::sigmoid(double x) {
    return 1 / (1 + exp(-x));
}

double Layer::sigmoidDerivative(double x) {
    return x * (1 - x);
}
