/*
 * PhoQ_PhoP_Gillespie.cpp
 *
 *  Created on: Oct 15, 2010
 *      Author: Leonard Harris
 */

#include "PhoQ_PhoP_Gillespie.hh"

using namespace std;
using namespace MoMMA;

PhoQ_PhoP_Gillespie::PhoQ_PhoP_Gillespie(GillespieDM* gillespSim){
	this->gillespSim = gillespSim;
	this->RR_init = this->gillespSim->species.at(0)->population;
	this->RRp_init = this->gillespSim->species.at(1)->population;
	// Initialize lastState
	this->lastState.push_back(0.0); // tStart
	this->lastState.push_back(0.0); // tEnd
	for (unsigned int i=0;i < this->gillespSim->species.size();i++){
		this->lastState.push_back(this->gillespSim->species.at(i)->population);
	}
}

void PhoQ_PhoP_Gillespie::initialize(){
	// Initialize species populations for next run
	this->gillespSim->species.at(0)->population = this->RR_init;
	this->gillespSim->species.at(1)->population = this->RRp_init;
}

double PhoQ_PhoP_Gillespie::run(double tStart, double tEnd){

	// Save current state
	this->lastState.at(0) = tStart;
	this->lastState.at(1) = tEnd;
	for (unsigned int i=0;i < this->gillespSim->species.size();i++){
		this->lastState.at(i+2) = this->gillespSim->species.at(i)->population;
	}

	// Run simulation
	double tau = this->gillespSim->run(tStart,tEnd);

	// Set initial values for next run equal to final values of this run
	this->RR_init = this->gillespSim->species.at(0)->population;
	this->RRp_init = this->gillespSim->species.at(1)->population;

	return tau;
}

void PhoQ_PhoP_Gillespie::rollBack(double amount){
	// Reset species populations to previous values
	for (unsigned int i=0;i < this->lastState.size();i++){
		this->gillespSim->species.at(i)->population = this->lastState.at(i+2);
	}
	// Re-run simulation
	this->gillespSim->run(this->lastState.at(0),(this->lastState.at(1)-amount));
}
