#pragma once
#include <string>
#include <vector>
#include "Feature.hpp"

/* Represents a user-defined ODB++ symbol — associates a symbol name with its feature data */
class Symbol{
    private:
        std::string _symbolName; /* symbol name (e.g. "r120", "rect20x60") */
        Feature _feature;        /* geometric content of the symbol */
    public:
        Symbol() = default;
        Symbol(std::string const &symbolName, Feature const &featuresArr);
        std::string get_symbolName();
        Feature get_feature();
        std::vector<std::string> get_DirectoryNames(std::string const &path);
};
