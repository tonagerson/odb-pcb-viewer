#include "Surface.hpp"
#include "Outline.hpp"

Surface::Surface(polarity const &p, std::vector<Outline> outlineArr):
	_polarity(p),
	_outlineArr(outlineArr)
{}

polarity Surface::get_polarity(){
	return this->_polarity;
}

std::vector<Outline> Surface::get_outlineArr(){
	return this->_outlineArr;
}
