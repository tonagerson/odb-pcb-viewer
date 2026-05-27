#include "core/form.hpp"
#include <sstream>

using namespace std;

//  read_line pour chaque forme

void Pad::read_line(const std::string& line) {

    istringstream iss(line);
    string type, pol_str, orient_def;
    int dcode;

    iss >> type >> x >> y >> sym_num >> pol_str >> dcode >> orient_def;

    polarity = (pol_str == "P") ? 1 : 0;
}

void Line::read_line(const std::string& line) {

    istringstream iss(line);
    string type, pol_str;
    int dcode;

    iss >> type >> xs >> ys >> xe >> ye >> sym_num >> pol_str >> dcode;

    polarity = (pol_str == "P") ? 1 : 0;
}

void ArcForm::read_line(const std::string& line) {

    istringstream iss(line);
    string type, pol_str, cw_str;
    int dcode;

    iss >> type >> xs >> ys >> xe >> ye >> xc >> yc >> sym_num >> pol_str >> dcode >> cw_str;

    polarity = (pol_str == "P") ? 1 : 0;

    clock_wise = (cw_str == "Y") ? true : false;
}

void Text::read_line(const std::string& line) {

    istringstream iss(line);
    string type, pol_str, orient_def;

    iss >> type >> x >> y >> font >> pol_str >> orient_def >> xsize >> ysize >> width >> content;

    polarity = (pol_str == "P") ? 1 : 0;
}