#pragma once
#include <string>
#include "Feature.hpp"

/* Represents a PCB layer — associates a layer name with its parsed feature data */
class Layer{
    private:
        std::string _layerName; /* layer name as defined in the matrix (e.g. "assemb") */
        Feature _feature;       /* geometric content of the layer */
    public:
        Layer() = default;
        Layer(std::string const &layerName, Feature const &featureArr);
        std::string get_layerName();
        Feature get_feature();
};
