#include "core/Component.hpp"

Component::Component(std::string refDes, std::string partName, double x, double y, double rotation, bool isMirrored) :
    _refDes(refDes), _partName(partName), _x(x), _y(y), _rotation(rotation), _isMirrored(isMirrored) {}

std::string Component::get_refDes() {
    return this->_refDes;
}

std::string Component::get_partName() {
    return this->_partName;
}

double Component::get_x() {
    return this->_x;
}

double Component::get_y() {
    return this->_y;
}

double Component::get_rotation() {
    return this->_rotation;
}

bool Component::get_isMirrored() {
    return this->_isMirrored;
}