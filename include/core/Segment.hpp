#pragma once 

#include <string>

enum segment_type {STRAIGHT,CURVE};
enum direction {Y,N}; /* Y <=> clockwise */

class Segment
{
	protected: 
		segment_type _st;
		int _x;
		int _y;
		Segment() = default;
		Segment(segment_type const &st,int const &x,int const &y);
};
class StraightSegment : public Segment
{
	public:
		StraightSegment(std::string const &st,int const &x,int const &y);
};
class CurveSegment : public Segment
{
	private:
		int _xc;
		int _yc;
		direction _wc;
	public:
		CurveSegment(std::string const &st,int const &x,int const &y,int const &xc,int const &yc,char const &wc);
};
