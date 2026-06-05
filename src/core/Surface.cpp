#include "Surface.hpp"
#include "Outline.hpp"
#include "Edge.hpp"
#include <iomanip>
#include <iostream>
#include <fstream>

/* Surface implementation — represents a filled area (S...SE) in the ODB++ features file.
 * A surface contains one or more outlines : at least one island (external boundary)
 * and optionally holes (internal cutouts). */

Surface::Surface(polarity const &p, std::vector<Outline> outlineArr):
    _polarity(p),
    _outlineArr(outlineArr)
{}

polarity Surface::get_polarity(){
    return this->_polarity;
}

std::vector<Outline> Surface::get_outlineArr(){
    return this->_outlineArr;
}

/* Writes the surface back to a file in ODB++ format (S...OB...OS/OC...OE...SE).
 * Each outline is written as a closed polygon of segments and arcs. */
void Surface::Print(std::ofstream &out){
    std::string pol = (this->_polarity == POSITIVE) ? "P" : "N";
    out << std::fixed << std::setprecision(12);
    out << "S " << pol << " 0" << std::endl;
    for (auto &outline : this->_outlineArr){
        std::string ot = (outline.get_ot() == ISLAND) ? "I" : "H";
        std::vector<Edge*> edges = outline.get_edgeArr();
        if (edges.empty()){ 
            continue;
        }
        /* OB : outline begin — first edge point is the start point */
        out << "OB " << edges.at(0)->get_x() << " " << edges.at(0)->get_y() << " " << ot << std::endl;
        for (size_t i = 1; i < edges.size(); i++){
            if (edges.at(i)->get_st() == SEGMENT){
                out << "OS " << edges.at(i)->get_x() << " " << edges.at(i)->get_y() << std::endl;
            }else{
                Arc* a = dynamic_cast<Arc*>(edges.at(i));
                std::string cw = (a->get_wc() == Y) ? "Y" : "N";
                out << "OC " << a->get_x()  << " " << a->get_y()
                    << " "   << a->get_xc() << " " << a->get_yc()
                    << " "   << cw << std::endl;
            }
        }
        out << "OE" << std::endl;
    }
    out << "SE" << std::endl;
}
