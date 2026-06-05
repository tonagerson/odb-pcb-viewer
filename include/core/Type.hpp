#pragma once

enum edge_type    { SEGMENT, ARC };
enum direction    { Y, N };          /* Y <=> clockwise */
enum context      { BOARD, MISC };
enum outline_type { ISLAND, HOLE };
enum unit_measurement { MM, INCH };
enum polarity     { POSITIVE, NEGATIVE };

enum layer_type {
    SIGNAL,
    POWER_GROUND,
    DIELECTRIC,
    MIXED,
    SOLDER_MASK,
    SOLDER_PASTE,
    SILK_SCREEN,
    DRILL,
    ROUT,
    DOCUMENT,
    COMPONENT,
    MASK,
    CONDUCTIVE_PASTE
};

class Point2D{
    private:
        double _x;
        double _y;
    public:
        Point2D() = default;
        Point2D(double const &x, double const &y);
        double get_x();
        double get_y();
};
