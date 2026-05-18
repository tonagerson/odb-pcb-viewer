#include "Outline.hpp"
#include "Edge.hpp"

Outline::Outline(outline_type const &ot,std::vector<Edge> edgeArr):
	_ot(ot),
	_edgeArr(edgeArr)
{}

outline_type Outline::get_ot(){
	return this->_ot;
}

std::vector<Edge> Outline::get_edgeArr(){
	return this->_edgeArr;
}
