#pragma once
#include <vector>
#include "Type.hpp"
#include "Outline.hpp"

/* Represents a surface feature (S...SE) made of one or more outlines (islands and holes) */
class Surface
{
    private:
        polarity _polarity;              /* P = positive (adds material), N = negative */
        std::vector<Outline> _outlineArr; /* list of outlines (at least one island) */
    public:
        Surface() = default;
        Surface(polarity const &p, std::vector<Outline> outlineArr);
        polarity get_polarity();
        std::vector<Outline> get_outlineArr();
        void Print(std::ofstream &out);
};
