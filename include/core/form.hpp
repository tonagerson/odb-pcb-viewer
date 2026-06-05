#pragma once
#include "Type.hpp"
#include <string>
#include <vector>
#include <fstream>

/* Abstract base class for all ODB++ graphic features */
class Form{
    protected:
        polarity _pol;
        int _dcode;
        int _id;
        std::vector<std::pair<int,int>> _attributs; /* list of (attrIndex, valueIndex) pairs */
    public:
        Form() = default;
        Form(polarity const &pol, int const &dcode, int const &id, std::vector<std::pair<int,int>> attributs);
        polarity get_polarity();
        int get_dcode();
        int get_id();
        std::vector<std::pair<int,int>> get_attributs();
        virtual void Print(std::ofstream &out) = 0;
        Point2D get_start();
        Point2D get_end();
};

/* Line feature (L) — straight line between two points with a symbol defining its width */
class Line : public Form{
    private:
        Point2D _start;
        Point2D _end;
        int _symNum; /* index in the feature symbols table ($) */
    public:
        Line() = default;
        Line(
            polarity const &pol,
            int const &dcode,
            int const &id,
            std::vector<std::pair<int,int>> attributs,
            Point2D const &start,
            Point2D const &end,
            int const &symNum
        );
        Point2D get_start() const { return _start; }
        Point2D get_end() const { return _end; }
        int Parse(std::string const &l);
        void Print(std::ofstream &out) override;
        Point2D get_start();
        Point2D get_end();
};
//Pad
class Pad : public Form {
private:
    Point2D _position;
    int _symNum;
public:
    Pad() = default;
    int Parse(std::string const &l);
    void Print(std::ofstream &out) override;
    Point2D get_position();
};
/*


class Arc : public Form{
    private:
        Point2D _start;
        Point2D _end;
        Point2D _center;
        int _symNum;
        bool cw;
}

class Text : public Form {
    private:
        Point2D position;
        std::string font;
        OrientDef orientDef;
        float xsize;
        float ysize;
        float widthFactor;
        std::string text;
        int version;
};
*/
