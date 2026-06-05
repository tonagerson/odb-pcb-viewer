#include <vector>
#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include "Matrix.hpp"

using namespace std;

Matrix::Matrix(vector<Step_desc> stepsArr, vector<Layer_desc> layersArr):
    _stepsArr(stepsArr),
    _layersArr(layersArr)
{}

vector<string> Matrix::get_layersNames(){
    vector<string> layersNames;
    for (auto &x : this->_layersArr){
        layersNames.push_back(x.get_name());
    }
    return layersNames;
}

int Matrix::Parse(std::string const &path){
    vector<Step_desc> stepsArr;
    vector<Layer_desc> layersArr;
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
    while (getline(f, line)){
        istringstream iss(line);
        string word;
        iss >> word;
        if (word == "STEP"){
            /* start of the step field */
            flag = true;
            count = 0;
            while (getline(f, line) && flag){
                size_t pos = line.find('=');
                string value = line.substr(pos + 1);
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
            stepsArr.push_back(Step_desc(col, step_name));
        }else if (word == "LAYER"){
            /* start of the layer field */
            flag = true;
            count = 0;
            string color = "999900";
            while (getline(f, line) && flag){
                size_t pos = line.find('=');
                string value = line.substr(pos + 1);

                if (pos != string::npos){
                    //couleur
                    if (line.find("COLOR=") != string::npos) {
                        color = value;
                    }

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
            layersArr.push_back(Layer_desc(row, layer_name, cont, lt, pol, color));
        }
    }
    this->_stepsArr = stepsArr;
    this->_layersArr = layersArr;
    return 0;
}

void Matrix::Print(ofstream &out){
    out << "Matrix display ... " << endl;
    for (auto &step : this->_stepsArr){
        out << "\n ---> Step " << step.get_col() << endl;
        out << "Name : " << step.get_name() << endl;
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
        out << "\n ---> Layer " << layer.get_row() << endl;
        out << "Name : " << layer.get_name() << endl;
        out << "Context : " << context << endl;
        out << "Type : " << layer_type << endl;
        out << "Polarity : " << polarity << endl;
    }
}
string Matrix::get_layer_color(std::string const &name){
    for (auto &layer : this->_layersArr){
        if (layer.get_name() == name){
            return layer.get_color();
        }
    }
    return "999900"; // Jaune par défaut si non trouvé
}
layer_type Matrix::get_layer_type(std::string const &name){
    for (auto &layer : this->_layersArr){
        if (layer.get_name() == name){
            return layer.get_layer_type();
        }
    }
    return SIGNAL;
}
