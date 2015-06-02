/*
 * commSimulator.cpp
 *
 *  Created on: Feb 12, 2010
 *      Author: Leonard Harris
 */

#include <iostream>
#include "commSimulator.hh"

using namespace std;
using namespace MoMMA;

CommSimulator::CommSimulator(string module_name){
	if (MoMMA::debug) cout << "CommSimulator constructor called." << endl;
	this->module_name = module_name;
	this->sim_data = ".";
}

CommSimulator::~CommSimulator(){
	if (MoMMA::debug) cout << "CommSimulator destructor called.\n";
}

double CommSimulator::run(double t){
	this->sim_data += this->module_name + "_";
	return t;
}

void CommSimulator::backtrack(double amount){
	cout << "Backtracking by " << amount << " time units." << endl;
}
