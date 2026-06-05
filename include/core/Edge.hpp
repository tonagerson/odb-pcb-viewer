#pragma once 
#include <string>
#include "Type.hpp"

/* Base class representing an edge (segment or arc) within an outline */
class Edge
{
    protected: 
        edge_type _st;  /* edge type : SEGMENT or ARC */
        float _x;       /* x coordinate of the end point */
        float _y;       /* y coordinate of the end point */
    public:
        Edge() = default;
        Edge(edge_type const &st, float const &x, float const &y);
        edge_type get_st();
	virtual ~Edge() = default;  /* virtual destructor required for dynamic_cast */
        float get_x();
        float get_y();
};

/* Straight segment — start point is implicit (previous point in the outline) */
class Segment : public Edge
{
    public:
        Segment(float const &x, float const &y);
};

/* Arc — start point is implicit, defined by a center point and a rotation direction */
class Arc : public Edge
{
    private:
        float _xc;      /* x coordinate of the center */
        float _yc;      /* y coordinate of the center */
        direction _wc;  /* rotation direction : Y = clockwise, N = counter-clockwise */
    public:
        Arc(float const &x, float const &y, float const &xc, float const &yc, direction const &wc);
        float get_xc();
        float get_yc();
        direction get_wc();
};
