#include <string>
#include "Layer.hpp"
#include "Feature.hpp"
#include <fstream>
#include <sstream>

using namespace std;

Layer::Layer(std::string const &layerName, Feature const &feature):
    _layerName(layerName),
    _feature(feature)
{}

string Layer::get_layerName(){
    return this->_layerName;
}

Feature Layer::get_feature(){
    return this->_feature;
}

std::vector<Component> Layer::get_components() {
    return this->_components;
}

void Layer::parse_components(std::string const &filepath) {
    // On ouvre le fichier "components" situé dans le dossier de la couche
    std::ifstream f(filepath + "/components");

    // Si le fichier n'existe pas, on arrête tout simplement
    if (!f.is_open()) {
        return;
    }

    std::string line;
    while (std::getline(f, line)) {
        // On cherche les lignes qui commencent par "CMP "
        if (line.substr(0, 4) == "CMP ") {
            std::istringstream iss(line);
            std::string type, mirrorStr, compName, partName;
            int pkgRef;
            double x, y, rot;

            // Format ODB++ : CMP <pkg_ref> <x> <y> <rot> <mirror> <comp_name> <part_name>
            iss >> type >> pkgRef >> x >> y >> rot >> mirrorStr >> compName >> partName;

            bool isMirrored = (mirrorStr == "M");

            // On ajoute le composant à notre liste
            this->_components.push_back(Component(compName, partName, x, y, rot, isMirrored));
        }
    }
}
