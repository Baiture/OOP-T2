#include "neuralnetwork.h"
#include "linearlayer.h"
#include "lossfunction.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>

NeuralNetwork::NeuralNetwork(double lr) : learning_rate(lr) {}

void NeuralNetwork::add_layer(std::unique_ptr<Layer> layer) {
    pipeline.push_back(std::move(layer));
}

Matrix NeuralNetwork::forward(const Matrix& input) {
    Matrix current = input;
    for (auto& layer : pipeline)
        current = layer->forward(current);
    return current;
}

void NeuralNetwork::backward(const Matrix& loss_grad) {
    Matrix grad = loss_grad;
    for (int i = (int)pipeline.size() - 1; i >= 0; --i)
        grad = pipeline[i]->backward(grad);
}

void NeuralNetwork::train(const Matrix& X, const Matrix& y, int epochs) {
    MSELoss loss_fn;
    for (int epoch = 0; epoch < epochs; ++epoch) {
        Matrix pred = forward(X);
        double loss = loss_fn.compute(pred, y);
        Matrix grad = loss_fn.gradient(pred, y);
        backward(grad);
        for (auto& layer : pipeline)
            layer->update_parameters(learning_rate);

        if ((epoch + 1) % 100 == 0)
            std::cout << "[Epoch " << epoch + 1 << "/" << epochs
                      << "] Loss: " << loss << "\n";
    }
}

Matrix NeuralNetwork::predict(const Matrix& X) {
    return forward(X);
}

// ── Save brain ──────────────────────────────────────────────────────────────
// Format per layer (LinearLayer only – activation layers have no weights):
//   LAYER <type>
//   ROWS <r> COLS <c>
//   <w00> <w01> ...
//   BIAS ROWS 1 COLS <c>
//   <b0> <b1> ...
//   END
void NeuralNetwork::save(const std::string& path) const {
    std::ofstream ofs(path);
    if (!ofs.is_open())
        throw std::runtime_error("Cannot open file for writing: " + path);

    ofs << "NEURAL_NETWORK_BRAIN v1.0\n";
    ofs << "LEARNING_RATE " << learning_rate << "\n";
    ofs << "NUM_LAYERS " << pipeline.size() << "\n";

    for (const auto& layer : pipeline) {
        ofs << "LAYER " << layer->get_type_name() << "\n";

        // Only LinearLayer has learnable parameters
        auto* ll = dynamic_cast<LinearLayer*>(layer.get());
        if (ll) {
            // Weights
            ofs << "WEIGHTS ROWS " << ll->weights.get_rows()
                << " COLS " << ll->weights.get_cols() << "\n";
            for (int i = 0; i < ll->weights.get_rows(); ++i) {
                for (int j = 0; j < ll->weights.get_cols(); ++j)
                    ofs << ll->weights.at(i, j) << " ";
                ofs << "\n";
            }
            // Biases
            ofs << "BIASES COLS " << ll->biases.get_cols() << "\n";
            for (int j = 0; j < ll->biases.get_cols(); ++j)
                ofs << ll->biases.at(0, j) << " ";
            ofs << "\n";
        }
        ofs << "END\n";
    }
    std::cout << "[NeuralNetwork] Brain saved to: " << path << "\n";
}

// ── Load brain ──────────────────────────────────────────────────────────────
void NeuralNetwork::load(const std::string& path) {
    std::ifstream ifs(path);
    if (!ifs.is_open())
        throw std::runtime_error("Cannot open file for reading: " + path);

    std::string token;
    ifs >> token; // NEURAL_NETWORK_BRAIN
    ifs >> token; // v1.0

    ifs >> token >> learning_rate;         // LEARNING_RATE <val>
    int num_layers;
    ifs >> token >> num_layers;            // NUM_LAYERS <n>

    // We just update weights of existing layers in order
    int layer_idx = 0;
    while (ifs >> token && token == "LAYER") {
        std::string type;
        ifs >> type;

        if (type == "LinearLayer") {
            // Read weights
            int r, c;
            ifs >> token >> token >> r >> token >> c; // WEIGHTS ROWS r COLS c
            auto* ll = dynamic_cast<LinearLayer*>(pipeline[layer_idx].get());
            if (!ll)
                throw std::runtime_error("Layer type mismatch at index " +
                                         std::to_string(layer_idx));
            for (int i = 0; i < r; ++i)
                for (int j = 0; j < c; ++j)
                    ifs >> ll->weights.at(i, j);

            // Read biases
            ifs >> token >> token >> c;    // BIASES COLS c
            for (int j = 0; j < c; ++j)
                ifs >> ll->biases.at(0, j);
        }
        ifs >> token; // END
        ++layer_idx;
    }
    std::cout << "[NeuralNetwork] Brain loaded from: " << path << "\n";
}
