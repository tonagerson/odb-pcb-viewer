#include "Type.hpp"

Point2D::Point2D(double const &x, double const &y):
    _x(x),
    _y(y)
{}

double Point2D::get_x(){
    return this->_x;
}

double Point2D::get_y(){
    return this->_y;
}
