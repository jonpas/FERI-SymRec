#include "neuron.h"

#include <cmath>

Neuron::Neuron() {
}

Neuron::~Neuron() {
}

double Neuron::activate(double x) {
    return sigmoid(x);
}

void Neuron::sum() {
}

double Neuron::sigmoid(double x) {
    return 1 / (1 + exp(-x));
}

double Neuron::sigmoidPrime(double x) {
    return x * (1 - x);
}
