#pragma once
#include <string>
#include <vector>
#include <fstream>
#include "Step_desc.hpp"
#include "Layer_desc.hpp"

/* Represents the ODB++ matrix file — defines the layer stackup and step structure */
class Matrix{
    private:
        std::vector<Step_desc> _stepsArr;   /* list of steps (e.g. board1) */
        std::vector<Layer_desc> _layersArr; /* list of layers */
    public:
        Matrix() = default;
        Matrix(std::vector<Step_desc> stepsArr, std::vector<Layer_desc> layersArr);
        std::vector<std::string> get_layersNames();
        int Parse(std::string const &path);
        void Print(std::ofstream &out);
        std::string get_layer_color(std::string const &name);
        layer_type get_layer_type(std::string const &name);


};
