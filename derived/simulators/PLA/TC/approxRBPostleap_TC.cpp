/*
 * approxRBPostleap_TC.cpp
 *
 *  Created on: Mar 5, 2011
 *      Author: Leonard Harris
 */

#include "approxPL_TC.hh"

using namespace std;
using namespace MoMMA;
/*
ApproxRBPostleap_TC::ApproxRBPostleap_TC() : preCalc(true), ptc(), sp(), rxn(){
	if (MoMMA::debug)
		cout << "ApproxRBPostleap_TC constructor called." << endl;
}
*/
ApproxRBPostleap_TC::ApproxRBPostleap_TC(double eps, double w, vector<SimpleSpecies*>& sp, vector<Reaction*>& rxn,
		Preleap_TC& ptc) : eps(eps), w(w), preCalc(true), ptc(ptc), sp(sp), rxn(rxn){
	if (MoMMA::debug)
		cout << "ApproxRBPostleap_TC constructor called." << endl;
	//
	// Rxns that species participate in
	this->spInRxn = new vector<int>[this->sp.size()];
	this->stoich = new vector<double>[this->sp.size()];
	map<SimpleSpecies*,int>::iterator it;
	for (unsigned int j=0;j < this->sp.size();j++){
		for (unsigned int v=0;v < this->rxn.size();v++){
			it = this->rxn[v]->stoichSpecies.find(this->sp[j]);
			if (it != this->rxn[v]->stoichSpecies.end()){ // Species j involved in Reaction v
				this->spInRxn[j].push_back(v);
				this->stoich[j].push_back(static_cast<double>((*it).second));
			}
		}
	}
	//
	// Species that contribute to rxn rates
	this->currRate = new double[this->rxn.size()];
	this->rateSp = new vector<int>[this->rxn.size()];
	for (unsigned int v=0;v < this->rxn.size();v++){
//		this->currRate[v] = this->rxn[v]->getRate();
		for (unsigned int i=0;i < this->rxn[v]->rateSpecies.size();i++){
			bool found = false;
			for (unsigned int j=0;j < this->sp.size() && !found;j++){
				if (this->rxn[v]->rateSpecies[i] == this->sp[j]){
					this->rateSp[v].push_back(j);
					found = true;
				}
			}
		}
	}
/*
	for (unsigned int j=0;j < this->sp.size();j++){
		cout << this->sp[j]->name << ": ";
		for (unsigned int v=0;v < this->spInRxn[j].size();v++){
			cout << "\t" << this->spInRxn[j][v] << " (" << this->stoich[j][v] << ")";
		}
		cout << endl;
	}
	cout << endl;
	for (unsigned int v=0;v < this->rxn.size();v++){
		cout << "Rxn_" << v << ":";
		for (unsigned int j=0;j < this->rateSp[v].size();j++){
			cout << "\t" << this->rateSp[v][j];
		}
		cout << endl;
	}
	cout << endl;
//*/
}

ApproxRBPostleap_TC::~ApproxRBPostleap_TC(){
	if (MoMMA::debug)
		cout << "ApproxRBPostleap_TC destructor called." << endl;
	delete[] this->spInRxn;
	delete[] this->stoich;
	delete[] this->currRate;
	delete[] this->rateSp;
}

void ApproxRBPostleap_TC::getNewTau(double& tau){

	if (this->preCalc){ // First step
		this->ptc.getNewTau(tau);
		this->preCalc = false;
	}

	// Collect current rates
	for (unsigned int v=0;v < this->rxn.size();v++){
		this->currRate[v] = this->rxn[v]->getRate();
	}

	bool found = false;
	bool gotMin = false, gotMax = false;
	double tau_min, tau_max;
	while (!found){

		// Calculate projected species populations
		double projPop[this->sp.size()];
		double mean, sdev;
		for (unsigned int j=0;j < this->sp.size();j++){
			projPop[j] = this->sp[j]->population;
			mean = 0.0;
			sdev = 0.0;
			int R_v;
			for (unsigned int v=0;v < this->spInRxn[j].size();v++){
				R_v = this->spInRxn[j][v];
				mean += this->stoich[j][v]*this->currRate[R_v];
				sdev += this->stoich[j][v]*sqrt(this->currRate[R_v]);
//				projPop[j] += this->stoich[j][v]*this->currRate[R_v]*tau;
			}
			mean *= tau;
			sdev *= sqrt(tau);
			if (mean >= 0.0){
				projPop[j] += (mean + 2.0*sdev);
			}
			else{
				projPop[j] += (mean - 2.0*sdev);
			}
		}

		// Calculate projected rxn rates
		double projRate[this->rxn.size()];
		vector<double> X;
		for (unsigned int v=0;v < this->rxn.size();v++){
			X.resize(this->rateSp[v].size());
			for (unsigned int j=0;j < this->rateSp[v].size();j++){
				X[j] = projPop[this->rateSp[v][j]];
			}
			projRate[v] = this->rxn[v]->re->getRate(X);
		}
/*
		cout << "Initial rxn rates" << endl;
		cout << "-------------------" << endl;
		for (unsigned int v=0;v < this->rxn.size();v++){
			cout << "R_" << v << ": " << currRate[v] << endl;
		}
		cout << endl;
		cout << "Projected #'s of firings" << endl;
		cout << "------------------------" << endl;
		for (unsigned int v=0;v < this->rxn.size();v++){
			cout << "R_" << v << ": " << currRate[v]*tau << endl;
		}
		cout << endl;
		cout << "Projected population changes" << endl;
		cout << "----------------------------" << endl;
		for (unsigned int j=0;j < this->sp.size();j++){
			cout << this->sp[j]->name << ": " << (projPop[j]-this->sp[j]->population) << endl;
		}
		cout << endl;
		cout << "Projected rxn rates" << endl;
		cout << "-------------------" << endl;
		for (unsigned int v=0;v < this->rxn.size();v++){
			cout << "R_" << v << ": " << projRate[v] << endl;
		}
		cout << endl;
		cout << "Projected rate changes" << endl;
		cout << "----------------------" << endl;
		for (unsigned int v=0;v < this->rxn.size();v++){
			cout << "R_" << v << ": " << (projRate[v]-currRate[v])/currRate[v]*100.0 << "_%" << endl;
		}
//*/
		// Check
		bool ok = true;
		//
		// First make sure species populations not projected to go negative
		for (unsigned int j=0;j < this->sp.size() && ok;j++){
			if (projPop[j] < 0.0){
				ok = false;
			}
		}
		//
		// Now check projected rate changes
		double maxDelta = 0.0;
		if (ok){
			// Loop over reactions
			for (unsigned int v=0;v < this->rxn.size() && ok;v++){
				// Calculate delta
				double delta = fabs(projRate[v] - this->currRate[v]);
				double f = delta/this->currRate[v];
				if (f > maxDelta){
					maxDelta = f;
				}
				bool skip = true; // Skip if projected population changes for all reactant species are <= 1.0
				// Loop over rate species of Reaction v
				for (unsigned int j=0;j < this->rateSp[v].size() && skip;j++){
					int rSp = this->rateSp[v][j];
					if ( fabs(projPop[rSp] - this->sp[rSp]->population) > 1.0 ){
						skip = false;
					}
				}
				if (!skip){
					if (delta > this->eps*this->currRate[v]){
						ok = false;
					}
				}
			}
		}
		//
//cout << "-----" << endl << "tau = " << tau << endl;
		if (!ok){ // Tau too big
//cout << "TOO BIG" << endl;
			tau_max = tau;
			gotMax = true;
			if (gotMin){
				tau -= 0.5*(tau_max-tau_min);
			}
			else{
				tau *= 0.5;
			}
		}
		else if (maxDelta < this->w*this->eps){ // Tau too small
//cout << "TOO SMALL" << endl;
//cout << "maxDelta = " << maxDelta << endl;
			tau_min = tau;
			gotMin = true;
			if (gotMax){
				tau += 0.5*(tau_max-tau_min);
			}
			else{
				tau *= 2.0;
			}
		}
		else{
//cout << "JUST RIGHT" << endl;
//if (maxDelta > this->eps){
//	cout << "maxDelta = " << maxDelta << endl;
//	for (unsigned int j=0;j < this->sp.size();j++){
//		cout << "\t" << this->sp[j]->name << ": (" << this->sp[j]->population << ", " << projPop[j] << ")" << endl;
//	}
//}
			found = true;
		}
	}
}
