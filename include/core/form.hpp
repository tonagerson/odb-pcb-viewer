#pragma once
#include <string>

// CLASSE MÈRE (Abstraite)
class Form {
public:
    double x;
    double y;
    int polarity;
    int sym_num;

    Form() = default;
    virtual ~Form() = default;

    // Méthode virtuelle pure
    virtual void read_line(const std::string& line) = 0;
};

//  CLASSES FILLES

class Pad : public Form {
public:
    double rotation;
    bool mirror;

    Pad() = default;
    void read_line(const std::string& line) override;
};

class Line : public Form {
public:
    double xs;
    double ys;
    double xe;
    double ye;

    Line() = default;
    void read_line(const std::string& line) override;
};

class ArcForm : public Form {
public:
    double xs;
    double ys;
    double xe;
    double ye;
    double xc;
    double yc;
    bool clock_wise;

    ArcForm() = default;
    void read_line(const std::string& line) override;
};

class Text : public Form {
public:
    double xsize;
    double ysize;
    double width;
    std::string font;
    std::string content;

    Text() = default;
    void read_line(const std::string& line) override;
};