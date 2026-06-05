#include <string>
#include "Layer.hpp"
#include "Feature.hpp"

using namespace std;

Layer::Layer(std::string const &layerName, Feature const &feature):
    _layerName(layerName),
    _feature(feature)
{}

string Layer::get_layerName(){
    return this->_layerName;
}

Feature Layer::get_feature(){
    return this->_feature;
}
