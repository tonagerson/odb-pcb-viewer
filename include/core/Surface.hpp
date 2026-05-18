#pragma once

#include <vector>
#include "Outline.hpp"

enum polarity {POSITIVE, NEGATIVE};

class Surface
{
	private:
        	polarity _polarity;
        	std::vector<Outline> _outlineArr;
    	public:
		Surface() = default;
        	Surface(polarity const &p, std::vector<Outline> outlineArr);
		polarity get_polarity();
		std::vector<Outline> get_outlineArr();
};
