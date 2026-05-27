#include "Layer_descriptor.hpp"
#include <fstream>
#include <sstream>


Layer::Layer(int row,std::string name,context cont,layer_type lt,polarity pol):
	_row(row),
	_name(name),
	_cont(cont),
	_lt(lt),
	_pol(pol)
{}

int Layer::get_row(){
	return this->_row;
}

std::string Layer::get_name(){
	return this->_name;
}

context Layer::get_context(){
	return this->_cont;
}

layer_type Layer::get_layer_type(){
	return this->_lt;
}

polarity Layer::get_polarity(){
	return this->_pol;
}

int Layer::ParseFeatures(std::string const &path) {

    std::string filepath = path + "/designodb/steps/board1/layers/" + _name + "/features";
    std::fstream f;
    f.open(filepath);

    if (!f) {
        return 1;
    }

    std::string line;
    while(getline(f, line)) {
        // On vérifie que la ligne n'est pas vide
        if (line.empty() || line[0] == '#') continue;

        Form* nouvelle_forme = nullptr;

        // On vérifie la 1ère lettre (line)
        if (line.length() > 1) {
            if (line[0] == 'P' && line[1] == ' ') {
                nouvelle_forme = new Pad();
            } else if (line[0] == 'L' && line[1] == ' ') {
                nouvelle_forme = new Line();
            } else if (line[0] == 'A' && line[1] == ' ') {
                nouvelle_forme = new ArcForm();
            } else if (line[0] == 'T' && line[1] == ' ') {
                nouvelle_forme = new Text();
            }
        }

        // on remplit la forme et on la sauvegarde
        if (nouvelle_forme != nullptr) {
            nouvelle_forme->read_line(line);
            _forms.push_back(nouvelle_forme);
        }
    }
    return 0;
}