#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include "Edge.hpp"
#include "Outline.hpp"
#include "Surface.hpp"
#include "Feature.hpp"
#include "Form.hpp"

using namespace std;

/* Feature implementation — parses and stores all graphic data from an ODB++ features file */

Feature::Feature(
    unit_measurement const &unit,
    int const &nbForms,
    vector<string> symbols,
    vector<string> attributs,
    vector<string> textValues,
    vector<Form*> forms,
    vector<Surface*> surfaces
):
    _unit(unit),
    _nbForms(nbForms),
    _symbols(symbols),
    _attributs(attributs),
    _textValues(textValues),
    _forms(forms),
    _surfaces(surfaces)
{}

unit_measurement Feature::get_unit(){
    return this->_unit;
}

int Feature::get_nbForms(){
    return this->_nbForms;
}

vector<string> Feature::get_symbols(){
    return this->_symbols;
}

vector<string> Feature::get_attributs(){
    return this->_attributs;
}

vector<string> Feature::get_textValues(){
    return this->_textValues;
}

vector<Form*> Feature::get_forms(){
    return this->_forms;
}

vector<Surface*> Feature::get_surfaces(){
    return this->_surfaces;
}

int Feature::Parse(std::string const &p){
    fstream f;
    std::string filepath = p + "/features";
    f.open(filepath);
    if (!f){
        cerr << "No such file found" << endl;
        return 1;
    }
    string line;
    int formCount = 0;
    bool inSurface = false;
    polarity pol;
    outline_type ot;
    int dcode = 0;
    vector<Edge*> edgeArr;
    vector<Outline> outlineArr;

    while(getline(f, line)){
        istringstream iss(line);
        vector<string> words;
        string word;
        while(iss >> word) words.push_back(word);
        if (words.empty() || words.at(0)[0] == '#') continue;

        /* lookup tables */
        if (words.at(0)[0] == '$'){
            this->_symbols.push_back(words.at(1));
        }else if (words.at(0)[0] == '@'){
            this->_attributs.push_back(words.at(1));
        }else if (words.at(0)[0] == '&'){
            this->_textValues.push_back(words.at(1));

        /* total number of forms — used to pre-allocate memory */
        }else if (words.at(0) == "F"){
            formCount = stoi(words.at(1));
            this->_forms.reserve(formCount);

        /* graphic forms */
        }else if (words.at(0) == "L"){
            Line* l = new Line();
            l->Parse(line);
            this->_forms.push_back(l);
        //Padd
        }else if (words.at(0) == "P"){
            Pad* p = new Pad();
            p->Parse(line);
            this->_forms.push_back(p);
        /*
        }else if (words.at(0) == "A"){
            Arc* a = new Arc();
            a->Parse(line);
            this->_forms.push_back(a);
        }else if (words.at(0) == "T"){
            Text* t = new Text();
            t->Parse(line);
            this->_forms.push_back(t);
        */

        /* surface parsing (S...SE) */
        }else if (words.at(0) == "S"){
            inSurface = true;
            pol = (words.at(1) == "P") ? POSITIVE : NEGATIVE;
            dcode = stoi(words.at(2));
            outlineArr.clear();
        }else if (inSurface && words.at(0) == "OB"){
            ot = (words.at(3) == "I") ? ISLAND : HOLE;
            edgeArr.clear();
        }else if (inSurface && words.at(0) == "OS"){
            edgeArr.push_back(new Segment(stof(words.at(1)), stof(words.at(2))));
        }else if (inSurface && words.at(0) == "OC"){
            edgeArr.push_back(new Arc(
                stof(words.at(1)), stof(words.at(2)),
                stof(words.at(3)), stof(words.at(4)),
                (words.at(5) == "Y") ? Y : N
            ));
        }else if (inSurface && words.at(0) == "OE"){
            outlineArr.push_back(Outline(ot, edgeArr));
        }else if (inSurface && words.at(0) == "SE"){
            inSurface = false;
            this->_surfaces.push_back(new Surface(pol, outlineArr));
        }
    }
    return 0;
}

/* Writes the feature back to a file in ODB++ format */
void Feature::Print(ofstream &out){
    for (size_t i = 0; i < this->_symbols.size(); i++)
        out << "$" << i << " " << this->_symbols.at(i) << endl;
    for (size_t i = 0; i < this->_attributs.size(); i++)
        out << "@" << i << " " << this->_attributs.at(i) << endl;
    for (size_t i = 0; i < this->_textValues.size(); i++)
        out << "&" << i << " " << this->_textValues.at(i) << endl;
    for (auto &form : this->_forms)
        form->Print(out);
    for (auto &surface : this->_surfaces)
        surface->Print(out);
}
