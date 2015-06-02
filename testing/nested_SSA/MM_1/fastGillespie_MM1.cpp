/*
 * fastGillespie_MM1.cpp
 *
 *  Created on: Dec 3, 2010
 *      Author: Leonard Harris
 */

#include "simulators_MM1.hh"

using namespace std;
using namespace MoMMA;

FastGillespie_MM1::FastGillespie_MM1(GillespieDM* gillespSim){
	if (MoMMA::debug)
		cout << "FastGillespie_MM1 constructor called." << endl;
	this->gillespSim = gillespSim;
	this->equil = false;
	this->E_T = this->gillespSim->species.at(0)->population;
	this->S_T = this->gillespSim->species.at(1)->population;
	this->f   = this->gillespSim->species.at(2)->population / this->E_T;
	this->dP = 0.0;
	this->P   = 0.0;
}

void FastGillespie_MM1::initialize(){
//	cout << "Delta_P = " << this->dP << endl;
	double ES_init = max((floor(this->f*this->E_T + 0.5) - this->dP),0.0);
	double E_init  = this->E_T - ES_init;
	double S_init  = this->S_T - ES_init - this->P;
	this->gillespSim->species.at(0)->setPopulation(E_init);
	this->gillespSim->species.at(1)->setPopulation(S_init);
	this->gillespSim->species.at(2)->setPopulation(ES_init);
	this->gillespSim->initialize();
	this->dP = 0.0;
	this->equil = false;
}

double FastGillespie_MM1::run(double tStart, double tEnd){
	double time = tStart;
	double tau;
	this->f = 0.0;
	//
//	cout << "equil = "; if (this->equil){ cout << "true" << endl; } else { cout << "false" << endl; }

	// No active reactions
	if (this->gillespSim->calcSumRates() < MoMMA::TOL){
		cout << "sumRates = " << this->gillespSim->calcSumRates() << endl;
		this->equil = true;
	}
	// Regular Gillespie simulation
	else{
		// Simulation loop
		double mult;
		while (time < tEnd){
			mult = this->gillespSim->species.at(2)->population;
			tau = this->gillespSim->nextStep(tEnd-time); // Single step
			this->f += mult*tau;
			time += tau;
		}
		this->f /= (time - tStart);
		this->f /= this->E_T;

		// Set equil = true ONLY if [S]+[ES] > 4 (equil initialized to false in initialize() method)
		if ( (this->gillespSim->species.at(1)->population + this->gillespSim->species.at(2)->population) > 4.0 ){
			this->equil = true;
		}
		//
//		cout << "f = " << this->f << endl;
//		cout << "equil = "; if (this->equil){ cout << "true" << endl; } else { cout << "false" << endl; }

		// Error check
		for (unsigned int i=0;i < this->gillespSim->species.size();i++){
			if (this->gillespSim->species.at(i)->population < 0.0){
				cout << "Error in FastGillespie_MM1::run(): Population of species = "
					 << this->gillespSim->species.at(i)->population << ". Exiting." << endl;
				exit(1);
			}
		}
	}
	return (time - tStart);
}

bool FastGillespie_MM1::checkForEquilibrium(){
	cout << "Equilibrium check: ";
	if (this->equil){ cout << "true." << endl; } else{ cout << "false." << endl; }
	return this->equil;
}
