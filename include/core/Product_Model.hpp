#pragma once

enum unit_measurement {MM,INCH};

//#include <filesystem>
#include <vector>
#include "Surface.hpp"

class Product_Model
{
	private:
		Surface _s;
		unit_measurement _unit;
		int _dcode;
	public:
		Product_Model() = default;
		Product_Model(unit_measurement const &unit,int const &dcode,Surface const &s);
		Surface get_surface();
		unit_measurement get_unit();
		int get_dcode();
        int Parse(std:: string const &p);
		void Print();
};
