/*

#include <iostream>
#include <string>
#include "Product_Model.hpp"
#include "Matrix.hpp"
#include "Feature.hpp"
using namespace std;

int main(int argc, char** argv){
	if (argc != 2){
		cerr << "Usage: " << argv[0] << " <ODB_file>" << endl;
		return 1;
	}
	Product_Model Pcb;
    std::string p = argv[1];
	int res;

	res = Pcb.Parse(p);
	if (res == 1){
		cerr << "Error in parsing" << endl;
		return 1;
	}
	cout << "*******************************************************" << endl;
	Pcb.Print();
	
	/*
	Matrix M = Pcb.get_matrix();
	cout << "*******************************************************" << endl;
	M.Print();
	*/
