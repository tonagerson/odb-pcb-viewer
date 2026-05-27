#pragma once 

#include <string>

class Step{
	private:
		int _col;
		std::string _name;
	public:
		Step(int col,std::string name);
		int get_col();
		std::string get_name();
};
