/*
 * approxSBPostleap_TC.cpp
 *
 *  Created on: Mar 5, 2011
 *      Author: Leonard Harris
 */

#include "approxPL_TC.hh"

using namespace std;
using namespace MoMMA;
/*
ApproxSBPostleap_TC::ApproxSBPostleap_TC() : preCalc(true), ptc(), sp(), rxn(){
	if (MoMMA::debug)
		cout << "ApproxSBPostleap_TC constructor called." << endl;
}
*/
ApproxSBPostleap_TC::ApproxSBPostleap_TC(double eps, double w, vector<SimpleSpecies*>& sp, vector<Reaction*>& rxn,
		Preleap_TC& ptc) : fEulerPreleapSB_TC(eps,sp,rxn), w(w), preCalc(true), ptc(ptc), sp(sp), rxn(rxn){
	if (MoMMA::debug)
		cout << "ApproxSBPostleap_TC constructor called." << endl;
	this->currRate = new double[this->rxn.size()];
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
/*
	for (unsigned int j=0;j < this->sp.size();j++){
		cout << this->sp[j]->name << ": ";
		for (unsigned int v=0;v < this->spInRxn[j].size();v++){
			cout << "\t" << this->spInRxn[j][v] << " (" << this->stoich[j][v] << ")";
		}
		cout << endl;
	}
	cout << endl;
//*/
}

ApproxSBPostleap_TC::~ApproxSBPostleap_TC(){
	if (MoMMA::debug)
		cout << "ApproxSBPostleap_TC destructor called." << endl;
	delete[] this->spInRxn;
	delete[] this->stoich;
	delete[] this->currRate;
}

void ApproxSBPostleap_TC::getNewTau(double& tau){

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
		cout << "Projected species populations" << endl;
		cout << "-----------------------------" << endl;
		for (unsigned int j=0;j < this->sp.size();j++){
			cout << this->sp[j]->name << ": " << projPop[j] << endl;
		}
		cout << endl;
		cout << "Projected population changes" << endl;
		cout << "----------------------------" << endl;
		for (unsigned int j=0;j < this->sp.size();j++){
			cout << this->sp[v]->name << ": " << (projPop[j]-this->sp[j]->population)/this->sp[j]->population << endl;
		}
*/
		// Check
		bool ok = true;
		double maxDelta = 0.0;
		for (unsigned int j=0;j < this->sp.size() && ok;j++){
			if (projPop[j] < 0.0){
				ok = false;
			}
			else{
				double delta = fabs(projPop[j] - this->sp[j]->population);
				double g_j = this->gGet->get_g(j);
				double f = delta/this->sp[j]->population*g_j;
				if (f > maxDelta){
					maxDelta = f;
				}
				if ( delta > 1.0 && delta > this->eps*this->sp[j]->population/g_j ){
					ok = false;
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
//		cout << this->sp[j]->name << ": (" << this->sp[j]->population << ", " << projPop[j] << ")" << endl;
//	}
//}
			found = true;
		}
	}
}
