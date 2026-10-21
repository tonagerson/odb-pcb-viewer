#pragma once
#include <string>
#include "core/Component.hpp"
#include "Feature.hpp"

/* Represents a PCB layer — associates a layer name with its parsed feature data */
class Layer{
    private:
        std::string _layerName; /* layer name as defined in the matrix (e.g. "assemb") */
        Feature _feature;       /* geometric content of the layer */
         std::vector<Component> _components;
    public:
        Layer() = default;
        Layer(std::string const &layerName, Feature const &featureArr);
        std::string get_layerName();
        Feature get_feature();
         void parse_components(std::string const &filepath);
        std::vector<Component> get_components();
};
