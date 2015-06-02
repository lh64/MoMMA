/*
 * nested_gillespie.cpp
 *
 *  Created on: Nov 15, 2010
 *      Author: Leonard Harris
 */

#include "nested_gillespie.hh"

using namespace std;
using namespace MoMMA;

Nested_Gillespie::Nested_Gillespie(GillespieDM* gillespSim, vector<unsigned int> speciesIndex, bool fastest){
	this->gillespSim = gillespSim;
	this->fastest = fastest;

	// Initialize initial population parameters
	for (unsigned int i=0;i < speciesIndex.size();i++){
		this->X_init.insert( pair<unsigned int,double>(speciesIndex.at(i),
				this->gillespSim->species.at(speciesIndex.at(i))->population) );
	}

	// Initialize timecourses
	this->timecourse.push_back(vector<double>(1,2.0));  // Time first...
	for (unsigned int i=0;i < speciesIndex.size();i++){ // ...then species populations
		this->timecourse.push_back(vector<double>(1,this->gillespSim->species.at(speciesIndex.at(i))->population));
	}

	// Initialize lastState
/*	this->lastState.push_back(0.0); // tStart
	this->lastState.push_back(0.0); // tEnd
	for (unsigned int i=0;i < this->gillespSim->species.size();i++){
		this->lastState.push_back(this->gillespSim->species.at(i)->population);
	}
*/
}

void Nested_Gillespie::initialize(){
	// Initialize species populations for next run
	map<unsigned int,double>::iterator X_iter;
	for (X_iter = this->X_init.begin();X_iter != this->X_init.end();X_iter++){
		this->gillespSim->species.at((*X_iter).first)->population = (*X_iter).second;
	}
	// Recalculate sumRates
	this->gillespSim->initialize();
}

double Nested_Gillespie::run(double tStart, double tEnd){

	// Save current state
/*	this->lastState.at(0) = tStart;
	this->lastState.at(1) = tEnd;
	for (unsigned int i=0;i < this->gillespSim->species.size();i++){
		this->lastState.at(i+2) = this->gillespSim->species.at(i)->population;
	}
*/
	// Run simulation
	double tau = NAN;
	if (!this->fastest){ // Single step
//		tau = this->gillespSim->nextStep(tEnd-tStart);
		tau = this->gillespSim->run(1);
	}
	else{
		tau = this->gillespSim->run(tStart,tEnd);
	}

	// Set initial values for next run equal to final values of this run
	map<unsigned int,double>::iterator X_iter;
	for (X_iter = this->X_init.begin();X_iter != this->X_init.end();X_iter++){
		(*X_iter).second = this->gillespSim->species.at((*X_iter).first)->population;
	}

	if (MoMMA::isNAN(tau)){
		cout << "Error in Nested_Gillespie::run(): tau = NAN, shouldn't happen. Exiting." << endl;
		exit(1);
	}

	return tau;
}
/*
void PhoQ_PhoP_Gillespie::backtrack(double amount){
	// Reset species populations to previous values
	for (unsigned int i=0;i < this->lastState.size();i++){
		this->gillespSim->species.at(i)->population = this->lastState.at(i+2);
	}
	// Re-run simulation
	this->gillespSim->run(this->lastState.at(0),(this->lastState.at(1)-amount));
}
*/
