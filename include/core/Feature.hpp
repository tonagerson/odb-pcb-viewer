#pragma once
#include "Form.hpp"
#include "Surface.hpp"
#include <fstream>
#include <vector>
#include <string>



/* Represents an ODB++ features file — contains lookup tables and a list of graphic forms.
 * Used by both layers (steps/board1/layers/<name>/features)
 * and symbols (symbols/<name>/features). */
class Feature {
    private:
        unit_measurement _unit;
        int _nbForms;                          /* total number of forms (F directive) */
        std::vector<std::string> _symbols;     /* symbol name lookup table ($) */
        std::vector<std::string> _attributs;   /* attribute name lookup table (@) */
        std::vector<std::string> _textValues;  /* attribute text value lookup table (&) */
        std::vector<Form*> _forms;             /* list of graphic forms (L, P, A, T) */
        std::vector<Surface*> _surfaces;       /* list of surface forms (S...SE) */
    public:
        Feature() = default;
        Feature(
            unit_measurement const &unit,
            int const &nbForms,
            std::vector<std::string> symbols,
            std::vector<std::string> attributs,
            std::vector<std::string> textValues,
            std::vector<Form*> forms,
            std::vector<Surface*> surfaces
        );
        unit_measurement get_unit();
        int get_nbForms();
        std::vector<std::string> get_symbols();
        std::vector<std::string> get_attributs();
        std::vector<std::string> get_textValues();
        std::vector<Form*> get_forms();
        std::vector<Surface*> get_surfaces();
        int Parse(std::string const &p);
        void Print(std::ofstream &out);
};
