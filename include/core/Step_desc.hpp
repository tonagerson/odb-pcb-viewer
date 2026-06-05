#pragma once 
#include <string>

/* Describes a step entry as defined in the ODB++ matrix file */
class Step_desc{
    private:
        int _col;          /* step column index */
        std::string _name; /* step name (e.g. "board1") */
    public:
        Step_desc(int col, std::string name);
        int get_col();
        std::string get_name();
};
