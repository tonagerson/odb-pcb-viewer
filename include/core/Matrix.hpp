#pragma once

#include <vector>
#include <string>
#include <Step_descriptor.hpp>
#include <Layer_descriptor.hpp>

class Matrix{
	private:
		std::vector<Step> _stepsArr;
		std::vector<Layer> _layersArr;
	public:
		Matrix() = default;
		Matrix(std::vector<Step> stepsArr,std::vector<Layer> layesrArr);
        int Parse(std::string const &path);
		void Print();
        std::vector<Layer>& get_layersArr() { return _layersArr; }

};
