#pragma once

#include "core/Axis.hpp"
#include "core/Product_Model.hpp"

class ApplicationModel {
  public:
  ApplicationModel();
  ~ApplicationModel();

  Axis * getAxis() const {return _axis;}
  Product_Model* getProductModel() const { return _product_model; }
  void setProductModel(Product_Model* pcb) { _product_model = pcb; }
  bool hasProductModel() const { return _product_model != nullptr; }

  private:
  Axis * _axis;
  Product_Model* _product_model = nullptr;

};
