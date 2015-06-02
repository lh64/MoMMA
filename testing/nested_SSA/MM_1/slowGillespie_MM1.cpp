/*
 * slowGillespie_MM1.cpp
 *
 *  Created on: Dec 2, 2010
 *      Author: Leonard Harris
 */

#include "simulators_MM1.hh"
#include "../../../model_spec/rateExpression.hh"

using namespace std;
using namespace MoMMA;

SlowGillespie_MM1::SlowGillespie_MM1(GillespieDM* gillespSim, double fastTau){
	if (MoMMA::debug)
		cout << "SlowGillespie_MM1 constructor called." << endl;
	this->gillespSim = gillespSim;
	this->equil = false;
	this->fastTau = fastTau;
	this->P = &this->gillespSim->species.at(1)->population; // P
	this->kcat = &static_cast<RateElementary*>(this->gillespSim->reaction.at(0)->re)->c;
}

double SlowGillespie_MM1::run(double tStart, double tEnd){
	double tau;
	// If no active reactions, set tau = (tEnd - tStart) and equil = true
	if (this->gillespSim->calcSumRates() < MoMMA::TOL){
		cout << "sumRates = " << this->gillespSim->calcSumRates() << endl;
		tau = tEnd - tStart;
		this->equil = true;
	}
	else{
		if ( (tEnd - tStart) > this->fastTau ){ // Single step
			tau = this->gillespSim->run(tStart,1);
		}
		else{
			tau =  this->gillespSim->run(tStart,tEnd);
		}
		// Set equil = TRUE if sumRates = 0.0
		if (this->gillespSim->calcSumRates() < MoMMA::TOL){
			cout << "sumRates = " << this->gillespSim->calcSumRates() << endl;
			this->equil = true;
		}
		else{
			this->equil = false;
		}
	}
	return tau;
}

bool SlowGillespie_MM1::checkForEquilibrium(){
	cout << "Equilibrium check: ";
	if (this->equil){ cout << "true." << endl; } else{ cout << "false." << endl; }
	return this->equil;
}
