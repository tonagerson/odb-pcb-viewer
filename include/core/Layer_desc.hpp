#pragma once
#include "Type.hpp"
#include <string>

/* Describes a layer entry as defined in the ODB++ matrix file */
class Layer_desc{
private:
    int _row;
    std::string _name;
    context _cont;
    layer_type _lt;
    polarity _pol;
    std::string _color;

public:
    //
    Layer_desc(int row, std::string name, context cont, layer_type lt, polarity pol, std::string color);
    int get_row();
    std::string get_name();
    context get_context();
    layer_type get_layer_type();
    polarity get_polarity();
    std::string get_color();
};