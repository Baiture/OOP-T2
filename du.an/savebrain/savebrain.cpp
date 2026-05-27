#include <iostream>
#include "neuralnetwork.h"
#include "linearlayer.h"
#include "activationlayer.h"
#include "lossfunction.h"

int main() {
    std::cout << "=== Neural Network Demo ===\n\n";

    // ── XOR dataset ────────────────────────────────────────────────────────
    // Input: 4 samples x 2 features
    Matrix X(4, 2);
    X.at(0,0)=0; X.at(0,1)=0;
    X.at(1,0)=0; X.at(1,1)=1;
    X.at(2,0)=1; X.at(2,1)=0;
    X.at(3,0)=1; X.at(3,1)=1;

    // Labels: XOR output
    Matrix y(4, 1);
    y.at(0,0)=0;
    y.at(1,0)=1;
    y.at(2,0)=1;
    y.at(3,0)=0;

    // ── Build network ───────────────────────────────────────────────────────
    NeuralNetwork net(0.1);
    net.add_layer(std::make_unique<LinearLayer>(2, 4));
    net.add_layer(std::make_unique<SigmoidLayer>());
    net.add_layer(std::make_unique<LinearLayer>(4, 1));
    net.add_layer(std::make_unique<SigmoidLayer>());

    // ── Train ───────────────────────────────────────────────────────────────
    std::cout << "Training on XOR (5000 epochs)...\n";
    net.train(X, y, 5000);

    // ── Predict ─────────────────────────────────────────────────────────────
    std::cout << "\n=== Predictions ===\n";
    Matrix preds = net.predict(X);
    for (int i = 0; i < preds.get_rows(); ++i)
        std::cout << "Input [" << X.at(i,0) << "," << X.at(i,1) << "]"
                  << "  Expected: " << y.at(i,0)
                  << "  Predicted: " << preds.at(i,0) << "\n";

    // ── Save brain ──────────────────────────────────────────────────────────
    net.save("brain.txt");
    std::cout << "\n=== Loading brain into new network ===\n";
    NeuralNetwork net2(0.1);
    net2.add_layer(std::make_unique<LinearLayer>(2, 4));
    net2.add_layer(std::make_unique<SigmoidLayer>());
    net2.add_layer(std::make_unique<LinearLayer>(4, 1));
    net2.add_layer(std::make_unique<SigmoidLayer>());
    net2.load("brain.txt");

    Matrix preds2 = net2.predict(X);
    std::cout << "\n=== Predictions after reload ===\n";
    for (int i = 0; i < preds2.get_rows(); ++i)
        std::cout << "Input [" << X.at(i,0) << "," << X.at(i,1) << "]"
                  << "  Predicted: " << preds2.at(i,0) << "\n";

    return 0;
}
