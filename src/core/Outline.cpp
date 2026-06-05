#include "Outline.hpp"
#include "Edge.hpp"

/* Outline implementation — represents a closed polygon boundary (OB...OE) within a surface.
 * Can be an island (external shape) or a hole (internal cutout). */

Outline::Outline(outline_type const &ot, std::vector<Edge*> edgeArr):
    _ot(ot),
    _edgeArr(edgeArr)
{}

outline_type Outline::get_ot(){
    return this->_ot;
}

std::vector<Edge*> Outline::get_edgeArr(){
    return this->_edgeArr;
}
