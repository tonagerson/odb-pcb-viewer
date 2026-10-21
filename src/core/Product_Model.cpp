#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <iomanip>
#include <dirent.h>
#include "Edge.hpp"
#include "Outline.hpp"
#include "Surface.hpp"
#include "Matrix.hpp"
#include "Symbol.hpp"
#include "Layer.hpp"
#include "Product_Model.hpp"

using namespace std;

/* Product_Model implementation — top-level parser for the ODB++ product model */

Product_Model::Product_Model(
    unit_measurement const &unit,
    int const &dcode,
    Surface const &PCB_Surface,
    Matrix const &mat,
    vector<Symbol> &symbols,
    vector<Layer> &layers
):
    _unit(unit),
    _dcode(dcode),
    _PCB_Surface(PCB_Surface),
    _mat(mat),
    _symbols(symbols),
    _layers(layers)
{}

unit_measurement Product_Model::get_unit(){
    return this->_unit;
}

int Product_Model::get_dcode(){
    return this->_dcode;
}

Surface Product_Model::get_surface(){
    return this->_PCB_Surface;
}

Matrix Product_Model::get_matrix(){
    return this->_mat;
}

vector<Symbol> Product_Model::get_symbols(){
    return this->_symbols;
}

vector<Layer> Product_Model::get_layers(){
    return this->_layers;
}

int Product_Model::Parse(std::string const &path){
     _mat.Parse(path);
    std::string filepath = path + "/designodb/steps/board1/profile";
    fstream f;
    f.open(filepath.c_str());
    if (!f){
        cerr << "No such file found" << endl;
        return 1;
    }
    string line;
    unit_measurement unit;
    int dcode;
    polarity pol;
    outline_type ot;
    vector<Edge*> edgeArr;
    vector<Outline> outlineArr;
    Surface Srf;

    /* parse PCB profile (steps/board1/profile) */
    while(getline(f, line)){
        istringstream iss(line);
        vector<string> words;
        string word;
        while (iss >> word) words.push_back(word);
        if (words.empty() || words.at(0)[0] == '#') continue;

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
            edgeArr.push_back(new Segment(stof(words.at(1)), stof(words.at(2))));
        }else if (words.at(0) == "OE"){
            /* Outline End */
            outlineArr.push_back(Outline(ot, edgeArr));
        }else if (words.at(0) == "SE"){
            Srf = Surface(pol, outlineArr);
        }
    }
    this->_unit = unit;
    this->_dcode = dcode;
    this->_PCB_Surface = Srf;
    this->_mat.Parse(path);

    /* Symbols Parsing */
    std::string symbolsPath = path + "/designodb/symbols";
    DIR *dir = opendir(symbolsPath.c_str());
    if (dir != nullptr) {
        struct dirent *entry;
        while ((entry = readdir(dir)) != nullptr) {
            std::string dirName = entry->d_name;
            if (dirName != "." && dirName != "..") {
                Feature feat;
                feat.Parse(symbolsPath + "/" + dirName);
                _symbols.push_back(Symbol(dirName, feat));
            }
        }
        closedir(dir);
    }

    vector<string> layerNames = _mat.get_layersNames();
    for (size_t i = 0; i < layerNames.size(); i++) {
        std::string layerName = layerNames[i];
        Feature feat;
        std::string layerPath = path + "/designodb/steps/board1/layers/" + layerName;
        feat.Parse(layerPath);
       // _layers.push_back(Layer(layerName, feat));
        //  On crée la couche
        Layer currentLayer(layerName, feat);

        //  lire les composants
        currentLayer.parse_components(layerPath);

        //  On l'ajoute au vecteur
        _layers.push_back(currentLayer);
    }
    return 0;
}

void Product_Model::Print(){
    Surface Srf = this->_PCB_Surface;
    string unit = (this->_unit == INCH) ? "INCH" : "MM";
    int dcode = this->_dcode;
    cout << "PCB display ...\n" << endl;
    cout << "Unit : " << unit << endl;
    cout << "Dcode : " << dcode << endl;
    for (auto &outline : Srf.get_outlineArr()){
        cout << "\n --> Outline Begin \n" << endl;
        for (auto &edge : outline.get_edgeArr()){
            cout << "(" << setprecision(12) << edge->get_x() << "," << edge->get_y() << ")" << endl;
        }
        cout << "\n --> Outline End \n" << endl;
    }

    /* display one of the layers feature */
    cout << "\n ---> Layers (" << this->_layers.size() << ")" << endl;
    for (auto &layer : this->_layers){
        cout << "Layer : " << layer.get_layerName() << endl;
    }
    if (!this->_layers.empty()){
        ofstream outLayer("output/file_layer.txt");
        if (outLayer){
            this->_layers.at(0).get_feature().Print(outLayer);
            outLayer.close();
        }else{
            cerr << "Cannot create file_layer.txt" << endl;
        }
    }

    /* display one of the symbols feature */
    cout << "\n ---> Symbols (" << this->_symbols.size() << ")" << endl;
    for (auto &symbol : this->_symbols){
        cout << "Symbol : " << symbol.get_symbolName() << endl;
    }
    if (!this->_symbols.empty()){
        ofstream outSymbol("output/file_symbol.txt");
        if (outSymbol){
            this->_symbols.at(0).get_feature().Print(outSymbol);
            outSymbol.close();
        }else{
            cerr << "Cannot create file_symbol.txt" << endl;
        }
    }

    /* display the matrix file */
    ofstream outMatrix("output/matrix.txt");
    if (outMatrix){
    	this->_mat.Print(outMatrix);
    	outMatrix.close();
    }else{
    	cerr << "Cannot create matrix.txt" << endl; 
    }
}
