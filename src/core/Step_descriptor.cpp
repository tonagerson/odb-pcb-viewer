#include "Step_descriptor.hpp"

Step::Step(int col,std::string name):
	_col(col),
	_name(name)
{}

int Step::get_col(){
	return this->_col;
}

std::string Step::get_name(){
	return this->_name;
}
