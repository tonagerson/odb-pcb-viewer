#include "Step_desc.hpp"

Step_desc::Step_desc(int col, std::string name):
    _col(col),
    _name(name)
{}

int Step_desc::get_col(){
    return this->_col;
}

std::string Step_desc::get_name(){
    return this->_name;
}
