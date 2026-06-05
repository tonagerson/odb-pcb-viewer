#pragma once
#include <string>
#include <vector>
#include "Type.hpp"
#include "Surface.hpp"
#include "Matrix.hpp"
#include "Symbol.hpp"
#include "Layer.hpp"

class Product_Model
{
private:
    unit_measurement _unit;
    int _dcode;
    Surface _PCB_Surface;
    Matrix _mat;
    std::vector<Symbol> _symbols;
    std::vector<Layer> _layers;
public:
    Product_Model() = default;
    Product_Model(
        unit_measurement const &unit,
        int const &dcode,
        Surface const &PCB_Surface,
        Matrix const &mat,
        std::vector<Symbol> &symbols,
        std::vector<Layer> &layers
        );
    unit_measurement get_unit();
    int get_dcode();
    Surface get_surface();
    Matrix get_matrix();
    std::vector<Symbol> get_symbols();
    std::vector<Layer> get_layers();
    int Parse(std::string const &p);
    void Print();
};