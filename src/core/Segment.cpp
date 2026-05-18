#include "Segment.hpp"

Segment::Segment(segment_type const &st, int const &x, int const &y): 
	_st(st), 
	_x(x), 
	_y(y) 
{}
StraightSegment::StraightSegment(std::string const &st,int const &x,int const &y):
	Segment(STRAIGHT,x,y)
{}
CurveSegment::CurveSegment(std::string const &st,int const &x,int const &y,int const &xc,int const &yc,char const &wc):
	Segment(CURVE,x,y), 
	_xc(xc), 
	_yc(yc)
{
	this->_wc = (wc == 'Y') ? Y : N;
}
