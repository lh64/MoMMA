/*
 * PhoQ_PhoP_Euler.cpp
 *
 *  Created on: Nov 4, 2010
 *      Author: Leonard Harris
 */

#include "PhoQ_PhoP_Euler.hh"

using namespace std;
using namespace MoMMA;

PhoQ_PhoP_Euler::PhoQ_PhoP_Euler(SimpleEuler* eulerSim){
	this->eulerSim = eulerSim;
	this->RR_init = this->eulerSim->species.at(0)->population;
	this->RRp_init = this->eulerSim->species.at(1)->population;
	// Initialize lastState
	this->lastState.push_back(0.0); // tStart
	this->lastState.push_back(0.0); // tEnd
	for (unsigned int i=0;i < this->eulerSim->species.size();i++){
		this->lastState.push_back(this->eulerSim->species.at(i)->population);
	}
}

void PhoQ_PhoP_Euler::initialize(){
	// Initialize species populations for next run
	this->eulerSim->species.at(0)->population = this->RR_init;
	this->eulerSim->species.at(1)->population = this->RRp_init;
}

double PhoQ_PhoP_Euler::run(double tStart, double tEnd){

	// Save current state
	this->lastState.at(0) = tStart;
	this->lastState.at(1) = tEnd;
	for (unsigned int i=0;i < this->eulerSim->species.size();i++){
		this->lastState.at(i+2) = this->eulerSim->species.at(i)->population;
	}

	// Run simulation
	double tau = this->eulerSim->run(tStart,tEnd);

	// Set initial values for next run equal to final values of this run
	this->RR_init = this->eulerSim->species.at(0)->population;
	this->RRp_init = this->eulerSim->species.at(1)->population;

	return tau;
}

void PhoQ_PhoP_Euler::backtrack(double amount){
	// Reset species populations to previous values
	for (unsigned int i=0;i < this->lastState.size();i++){
		this->eulerSim->species.at(i)->population = this->lastState.at(i+2);
	}
	// Re-run simulation
	this->eulerSim->run(this->lastState.at(0),(this->lastState.at(1)-amount));
}
