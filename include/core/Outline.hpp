#pragma once
#include <vector>
#include "Type.hpp"
#include "Edge.hpp" 

/* Represents a polygon boundary (island or hole) made of edges (segments and arcs) */
class Outline
{
    private:
        outline_type _ot;           /* ISLAND = filled area, HOLE = cutout */
        std::vector<Edge*> _edgeArr; /* ordered list of edges forming the closed polygon */
    public:
        Outline() = default;
        Outline(outline_type const &ot, std::vector<Edge*> edgeArr); 
        outline_type get_ot();
        std::vector<Edge*> get_edgeArr();
};
