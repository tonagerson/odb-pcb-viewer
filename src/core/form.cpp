#include "Form.hpp"
#include <iomanip>
#include <string>
#include <vector>
#include <sstream>
#include <iostream>

Form::Form(polarity const &pol, int const &dcode, int const &id, std::vector<std::pair<int,int>> attributs):
    _pol(pol),
    _dcode(dcode),
    _id(id),
    _attributs(attributs)
{}

polarity Form::get_polarity(){
    return this->_pol;
}

int Form::get_dcode(){
    return this->_dcode;
}

int Form::get_id(){
    return this->_id;
}

std::vector<std::pair<int,int>> Form::get_attributs(){
    return this->_attributs;
}

Line::Line(
    polarity const &pol,
    int const &dcode,
    int const &id,
    std::vector<std::pair<int,int>> attributs,
    Point2D const &start,
    Point2D const &end,
    int const &symNum
):
    Form(pol, dcode, id, attributs),
    _start(start),
    _end(end),
    _symNum(symNum)
{}

int Line::Parse(std::string const &line){
    std::istringstream iss(line);
    std::string type;
    double xs, ys, xe, ye;
    int symNum, dcode;
    char pol;
    /* L <xs> <ys> <xe> <ye> <sym_num> <polarity> <dcode> */
    iss >> type >> xs >> ys >> xe >> ye >> symNum >> pol >> dcode;
    this->_start  = Point2D(xs, ys);
    this->_end    = Point2D(xe, ye);
    this->_symNum = symNum;
    this->_pol    = (pol == 'P') ? POSITIVE : NEGATIVE;
    this->_dcode  = dcode;
    return 0;
}

void Line::Print(std::ofstream &out){
    std::string pol = (this->_pol == POSITIVE) ? "P" : "N";
    out << std::fixed << std::setprecision(12);
    out << "L " << this->_start.get_x() << " " << this->_start.get_y()
        << " "  << this->_end.get_x()   << " " << this->_end.get_y()
        << " "  << this->_symNum
        << " "  << pol
        << " "  << this->_dcode
        << std::endl;
}
Point2D Line::get_start() { return this->_start; }
Point2D Line::get_end() { return this->_end; }

int Pad::Parse(std::string const &line) {
    std::istringstream iss(line);
    std::string type;
    double x, y;
    int symNum, dcode;
    char pol;
    // Format : P <x> <y> <apt_def> <polarity> <dcode>
    iss >> type >> x >> y >> symNum >> pol >> dcode;
    this->_position = Point2D(x, y);
    this->_symNum = symNum;
    this->_pol = (pol == 'P') ? POSITIVE : NEGATIVE;
    this->_dcode = dcode;
    return 0;
}
Point2D Pad::get_position() { return this->_position; }
void Pad::Print(std::ofstream &out) {
    // Fonction vide
}