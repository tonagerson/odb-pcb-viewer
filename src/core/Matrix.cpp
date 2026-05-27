#include <vector>
#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include "Matrix.hpp"
using namespace std;

Matrix::Matrix(vector<Step> stepsArr,vector<Layer> layersArr):
	_stepsArr(stepsArr),
	_layersArr(layersArr)
{}

int Matrix::Parse(std::string const &path){
	vector<Step> stepsArr;
	vector<Layer> layersArr;
    std::string filepath = path + "/designodb/matrix/matrix";
	fstream f;
	f.open(filepath);
	if (!f){
		cerr << "No such file found" << endl;
		return 1;
	}
	string line;
	int count;
	bool flag;
	/* step attributs */
	int col;
	string step_name;
	/* layer attributs */
	int row;
	string layer_name;
	context cont;
	layer_type lt;
	polarity pol;
	/*******************/
	while (getline(f,line)){
		istringstream iss(line);
		string word;
		iss >> word;
		if (word == "STEP"){
			/* start of the step field */
			flag = true;
			count = 0;
			while (getline(f,line) && flag){
				size_t pos = line.find('=');
				string value = line.substr(pos+1);
				if (pos != string::npos){
					if (count == 0){
						col = stoi(value);
						count += 1;
					}else{
						step_name = value;
					}
				}
				flag = (line != "}");
			}
			stepsArr.push_back(Step(col,step_name));
		}else if (word == "LAYER"){
			/* start of the layer field */
			flag = true;
			count = 0;
			while (getline(f,line) && flag){
				size_t pos = line.find('=');
				string value = line.substr(pos+1);
				if (pos != string::npos){
					if (count == 0){
						row = stoi(value);
						count += 1;
					}else if (count == 1){
						cont = (value == "BOARD") ? BOARD : MISC;
						count += 1;
					}else if (count == 2){
						if (value == "SIGNAL"){
							lt = SIGNAL;	
						}else if (value == "POWER_GROUND"){
							lt = POWER_GROUND;	
						}else if (value == "DIELECTRIC"){
							lt = DIELECTRIC;
						}else if (value == "MIXED"){
							lt = MIXED;
						}else if (value == "SOLDER_MASK"){
							lt = SOLDER_MASK;
						}else if (value == "SOLDER_PASTE"){
							lt = SOLDER_PASTE;
						}else if (value == "SILK_SCREEN"){
							lt = SILK_SCREEN;
						}else if (value == "DRILL"){
							lt = DRILL;
						}else if (value == "ROUT"){
							lt = ROUT;
						}else if (value == "DOCUMENT"){
							lt = DOCUMENT;
						}else if (value == "COMPONENT"){
							lt = COMPONENT;
						}else if (value == "MASK"){
							lt = MASK;
						}else if (value == "CONDUCTIVE_PASTE"){
							lt = CONDUCTIVE_PASTE;
						}
						count += 1;
					}else if (count == 3){
						layer_name = value;
						count += 1;
					}else if (count == 4){
						pol = (value == "POSITIVE") ? POSITIVE : NEGATIVE;
						count += 1;
					}
				}
				flag = (line != "}");
			}
			layersArr.push_back(Layer(row,layer_name,cont,lt,pol));
		}
	}
    for (auto &layer : layersArr) {
        layer.ParseFeatures(path);
    }
	this->_stepsArr = stepsArr;
	this->_layersArr = layersArr;
	return 0;
}

void Matrix::Print(){
	cout << "Matrix display ... " << endl;
	for (auto &step : this->_stepsArr){
		cout << "\n ---> Step " << step.get_col() << endl;
		cout << "Name : " << step.get_name() << endl;
	}
	for (auto &layer : this->_layersArr){
		string context = (layer.get_context() == BOARD) ? "BOARD" : "MISC";
		string polarity = (layer.get_polarity() == POSITIVE) ? "POSITIVE" : "NEGATIVE";
		string layer_type;
		if (layer.get_layer_type() == SIGNAL){
		    layer_type = "SIGNAL";
		}else if (layer.get_layer_type() == POWER_GROUND){
		    layer_type = "POWER_GROUND";
		}else if (layer.get_layer_type() == DIELECTRIC){
		    layer_type = "DIELECTRIC";
		}else if (layer.get_layer_type() == MIXED){
		    layer_type = "MIXED";
		}else if (layer.get_layer_type() == SOLDER_MASK){
		    layer_type = "SOLDER_MASK";
		}else if (layer.get_layer_type() == SOLDER_PASTE){
		    layer_type = "SOLDER_PASTE";
		}else if (layer.get_layer_type() == SILK_SCREEN){
		    layer_type = "SILK_SCREEN";
		}else if (layer.get_layer_type() == DRILL){
		    layer_type = "DRILL";
		}else if (layer.get_layer_type() == ROUT){
		    layer_type = "ROUT";
		}else if (layer.get_layer_type() == DOCUMENT){
		    layer_type = "DOCUMENT";
		}else if (layer.get_layer_type() == COMPONENT){
		    layer_type = "COMPONENT";
		}else if (layer.get_layer_type() == MASK){
		    layer_type = "MASK";
		}else if (layer.get_layer_type() == CONDUCTIVE_PASTE){
		    layer_type = "CONDUCTIVE_PASTE";
		}
		cout << "\n ---> Layer " << layer.get_row() << endl;
		cout << "Name : " << layer.get_name() << endl;
		cout << "Context : " << context << endl;
		cout << "Type : " << layer_type << endl;
		cout << "Polarity : " << polarity << endl;
	}
}
