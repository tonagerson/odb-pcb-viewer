#pragma once

#include <vector>
#include "Edge.hpp" 

enum outline_type {ISLAND,HOLE};

class Outline{
	private:
		outline_type _ot;
		std::vector<Edge> _edgeArr;
	public:
		Outline() = default;
		Outline(outline_type const &ot,std::vector<Edge> edgeArr); 
		outline_type get_ot();
		std::vector<Edge> get_edgeArr();
};
