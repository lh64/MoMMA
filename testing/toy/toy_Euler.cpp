/*
 * toy_Euler.cpp
 *
 *  Created on: Nov 6, 2010
 *      Author: Leonard Harris
 */

#include "toy_Euler.hh"

using namespace std;
using namespace MoMMA;

Toy_Euler::Toy_Euler(SimpleEuler* eulerSim){
	this->eulerSim = eulerSim;
	this->X_init = this->eulerSim->species.at(2)->population;
	// Initialize lastState
//	this->lastState.push_back(0.0); // tStart
//	this->lastState.push_back(0.0); // tEnd
//	for (unsigned int i=0;i < this->eulerSim->species.size();i++){
//		this->lastState.push_back(this->eulerSim->species.at(i)->population);
//	}
}

void Toy_Euler::initialize(){
	// Initialize species populations for next run
	this->eulerSim->species.at(2)->population = this->X_init;
}

double Toy_Euler::run(double tStart, double tEnd){

	// Save current state
//	this->lastState.at(0) = tStart;
//	this->lastState.at(1) = tEnd;
//	for (unsigned int i=0;i < this->eulerSim->species.size();i++){
//		this->lastState.at(i+2) = this->eulerSim->species.at(i)->population;
//	}

	// Run simulation
	double tau = this->eulerSim->run(tStart,tEnd);

	// Set initial values for next run equal to final values of this run
	this->X_init = this->eulerSim->species.at(2)->population;

	return tau;
}
/*
void Toy_Euler::backtrack(double amount){
	// Reset species populations to previous values
	for (unsigned int i=0;i < this->lastState.size();i++){
		this->eulerSim->species.at(i)->population = this->lastState.at(i+2);
	}
	// Re-run simulation
	this->eulerSim->run(this->lastState.at(0),(this->lastState.at(1)-amount));
}
*/
