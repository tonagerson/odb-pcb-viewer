#pragma once
#include "core/form.hpp"
#include "Surface.hpp"
#include <string>
#include <vector>

enum context {BOARD,MISC};
enum layer_type {SIGNAL,POWER_GROUND,DIELECTRIC,MIXED,SOLDER_MASK,SOLDER_PASTE,SILK_SCREEN,DRILL,ROUT,DOCUMENT,COMPONENT,MASK,CONDUCTIVE_PASTE};

class Layer{
	private:
		int _row;
		std::string _name;
		context _cont;
		layer_type _lt;
		polarity _pol;
        std::vector<Form*> _forms;
	public:
		Layer(int row,std::string name,context cont,layer_type lt,polarity pol);
		int get_row();
		std::string get_name();
		context get_context();
		layer_type get_layer_type();
		polarity get_polarity();

        std::vector<Form*> get_forms() const { return _forms; }
        int ParseFeatures(std::string const &path);
};
