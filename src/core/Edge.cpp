#include "Edge.hpp"

/* Edge, Segment and Arc implementation — see Edge.hpp for class descriptions */

Edge::Edge(edge_type const &st, float const &x, float const &y): 
    _st(st), 
    _x(x), 
    _y(y) 
{}

float Edge::get_x(){
    return this->_x;
}

float Edge::get_y(){
    return this->_y;
}

edge_type Edge::get_st(){
    return this->_st;
}

Segment::Segment(float const &x, float const &y):
    Edge(SEGMENT, x, y)
{}

Arc::Arc(float const &x, float const &y, float const &xc, float const &yc, direction const &wc):
    Edge(ARC, x, y), 
    _xc(xc), 
    _yc(yc),
    _wc(wc)
{}

float Arc::get_xc(){
    return this->_xc;
}

float Arc::get_yc(){
    return this->_yc;
}

direction Arc::get_wc(){
    return this->_wc;
}
