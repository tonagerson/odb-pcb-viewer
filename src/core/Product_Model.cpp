#include <iostream>
//#include <filesystem>
#include <fstream>
#include <string>
#include <sstream>
#include <QDebug>
#include <memory>
#include <iomanip>
#include "Edge.hpp"
#include "Outline.hpp"
#include "Surface.hpp"
#include "Product_Model.hpp"
using namespace std;

Product_Model::Product_Model(unit_measurement const &unit,int const &dcode,Surface const &s):
	_s(s),
	_unit(unit),
	_dcode(dcode)
{}

Surface Product_Model::get_surface(){
	return this->_s;
}

unit_measurement Product_Model::get_unit(){
	return this->_unit;
}

int Product_Model::get_dcode(){
	return this->_dcode;
}
// souci de compilation donc j'utilise simplement std::string au lieu de filesystem::path
int Product_Model::Parse(std::string const &path){
    // chemin de base + la suite
    std::string filepath = path + "/designodb/steps/board1/profile";


	fstream f;
    f.open(filepath);
	if (!f){

        cerr << "No such file found:"<< filepath << endl;
		return 1;
	}

	string line;
	unit_measurement unit;
	int dcode;
	polarity pol;
	outline_type ot;
	vector<Edge> edgeArr;
	vector<Outline> outlineArr;
	Surface Srf;	
	while(getline(f,line)){
		istringstream iss(line);
		vector<string> words;
		string word;
		while (iss >> word){
			words.push_back(word);
		}
		if (words.at(0) == "U"){
			/* Units */
			unit = (words.at(1) == "INCH") ? INCH : MM;
		}else if (words.at(0) == "S"){
			/* Surface Begin */
			pol = (words.at(1) == "P") ? POSITIVE : NEGATIVE;
			dcode = stoi(words.at(2));
		}else if (words.at(0) == "OB"){
			/* Outline Begin */
			ot = (words.at(3) == "I") ? ISLAND : HOLE;
			edgeArr.clear();
		}else if (words.at(0) == "OS"){
			/* Outline Segment */
			Segment Seg(stof(words.at(1)),stof(words.at(2)));
			edgeArr.push_back(Seg);
		}else if (words.at(0) == "OE"){
			/* Outline End */
			outlineArr.push_back(Outline(ot,edgeArr));
		}else if (words.at(0) == "SE"){
			Srf = Surface(pol,outlineArr);
		}
	}
	this->_unit = unit;
	this->_dcode = dcode;
	this->_s = Srf;
	return 0;
}

void Product_Model::Print(){
	cout << "Affichage : ... " << endl;
	cout << "Le PCB est représnté par un rectangle dont les sommets sont les points suivant :\n " << endl;
	Surface Srf = this->_s;
	for (auto &outline : Srf.get_outlineArr()){
		for (auto &edge : outline.get_edgeArr()){
			cout << "(" << setprecision(12) << edge.get_x() << "," << edge.get_y() << ")" << endl;
		}
	}
}
