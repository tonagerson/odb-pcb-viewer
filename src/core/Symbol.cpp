#include <string> 
#include <vector>
#include <dirent.h>
#include "Symbol.hpp"
#include "Feature.hpp"

using namespace std;

Symbol::Symbol(std::string const &symbolName, Feature const &feature):
    _symbolName(symbolName),
    _feature(feature)
{}

string Symbol::get_symbolName(){
    return this->_symbolName;
}

Feature Symbol::get_feature(){
    return this->_feature;
}

vector<string> Symbol::get_DirectoryNames(std::string const &path){
    std::string symbolsPath = path + "/designodb/symbols";
    vector<string> symbolNames;

    DIR *dir = opendir(symbolsPath.c_str());
    if (dir != nullptr) {
        struct dirent *entry;
        while ((entry = readdir(dir)) != nullptr) {
            std::string dirName = entry->d_name;
            // On ignore les dossiers cachés du système
            if (dirName != "." && dirName != "..") {
                symbolNames.push_back(dirName);
            }
        }
        closedir(dir);
    }
    return symbolNames;
}