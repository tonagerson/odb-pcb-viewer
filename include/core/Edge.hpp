#pragma once 

#include <string>

enum edge_type {SEGMENT,ARC};
enum direction {Y,N}; /* Y <=> clockwise */

class Edge
{
	protected: 
		edge_type _st;
		float _x;
		float _y;
	public:
		Edge() = default;
		Edge(edge_type const &st,float const &x,float const &y);
		edge_type get_st();
		float get_x();
		float get_y();
};
class Segment : public Edge
{
	public:
		Segment(float const &x,float const &y);
};
class Arc : public Edge
{
	private:
		float _xc;
		float _yc;
		direction _wc;
	public:
		Arc(float const &x,float const &y,float const &xc,float const &yc,direction const &wc);
		float get_xc();
		float get_yc();
		/* direction get_wc(); */
};
