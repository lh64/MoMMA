/*
 * fSimulator.cpp
 *
 *  Created on: Oct 27, 2009
 *      Author: Leonard Harris
 */

#include "fSimulator.hh"

using namespace std;
using namespace MoMMA;

fSimulator::fSimulator(){
	if (MoMMA::debug)
		cout << "fSimulator constructor called.\n";
}

fSimulator::~fSimulator(){
	if (MoMMA::debug)
		cout << "fSimulator destructor called.\n";
}

void fSimulator::initialize(){
	cout << "Default fSimulator initialization: Do nothing." << endl;
}

double fSimulator::run(double t){
	cout << "Error in fSimulator.run(): Must overload the base method. Exiting." << endl;
	exit(1);
	return NAN;
}

double fSimulator::run(double tStart, double tEnd){
	cout << "Error in fSimulator.run(): Must overload the base method. Exiting." << endl;
	exit(1);
	return NAN;
}

void fSimulator::rollBack(double amount){
	cout << "Error in fSimulator.rollBack(): Must overload the base method. Exiting." << endl;
	exit(1);
}

bool fSimulator::checkForEquilibrium(){
	cout << "Default equilibrium check: Always false." << endl;
	return false;
}
