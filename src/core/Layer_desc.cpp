#include "Layer_desc.hpp"

Layer_desc::Layer_desc(int row, std::string name, context cont, layer_type lt, polarity pol, std::string color):
    _row(row),
    _name(name),
    _cont(cont),
    _lt(lt),
    _pol(pol),
    _color(color)
{}

int Layer_desc::get_row(){
    return this->_row;
}

std::string Layer_desc::get_name(){
    return this->_name;
}

context Layer_desc::get_context(){
    return this->_cont;
}

layer_type Layer_desc::get_layer_type(){
    return this->_lt;
}

polarity Layer_desc::get_polarity(){
    return this->_pol;
}
std::string Layer_desc::get_color(){
    return this->_color;
}
