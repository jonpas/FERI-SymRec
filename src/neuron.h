#pragma once

class Neuron {
public:
    Neuron();
    ~Neuron();

    double activate(double x);
    void sum();

    double sigmoid(double x);
    double sigmoidPrime(double x);
};
