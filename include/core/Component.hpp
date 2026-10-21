#pragma once
#include <string>

class Component {
private:
    std::string _refDes;    // Le nom sur la carte
    std::string _partName;  // La référence de la pièce
    double _x;              // Position X
    double _y;              // Position Y
    double _rotation;       // Rotation en degrés
    bool _isMirrored;       // Si le composant est en miroir (N ou M)

public:
    Component() = default;
    Component(std::string refDes, std::string partName, double x, double y, double rotation, bool isMirrored);

    std::string get_refDes();
    std::string get_partName();
    double get_x();
    double get_y();
    double get_rotation();
    bool get_isMirrored();
};