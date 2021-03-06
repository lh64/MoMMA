/*
 * eRungeKutta_FG.cpp
 *
 *  Created on: Mar 4, 2011
 *      Author: Leonard Harris
 */

#include "eRungeKutta.hh"
#include "../../../../borrowed/util/util.hh"

using namespace std;
using namespace MoMMA;
/*
eRungeKutta_FG::eRungeKutta_FG(){
	if (MoMMA::debug)
		cout << "eRungeKutta_FG constructor called." << endl;
}
*/
eRungeKutta_FG::eRungeKutta_FG(ButcherTableau bt, vector<SimpleSpecies*>& sp, vector<Reaction*>& rxn){
	if (MoMMA::debug)
		cout << "eRungeKutta_FG constructor called." << endl;
	// Error check
	if (!bt.isExplicit()){
		cout << "Error in eRungeKutta_FG constructor: Butcher tableu must be explicit. Exiting." << endl;
		exit(1);
	}
	this->fg = new eRK_FG(rxn);
	this->aCalc = new aEff_Calculator(bt,sp,rxn);
}

eRungeKutta_FG::eRungeKutta_FG(ButcherTableau bt, vector<SimpleSpecies*>& sp, vector<Reaction*>& rxn, bool round){
	if (MoMMA::debug)
		cout << "eRungeKutta_FG constructor called." << endl;
	// Error check
	if (!bt.isExplicit()){
		cout << "Error in eRungeKutta_FG constructor: Butcher tableu must be explicit. Exiting." << endl;
		exit(1);
	}
	this->fg = new eRK_FG(rxn,round);
	this->aCalc = new aEff_Calculator(bt,sp,rxn);
}

eRungeKutta_FG::eRungeKutta_FG(const eRungeKutta_FG& fg) : FiringGenerator(fg){
	if (MoMMA::debug)
		cout << "eRungeKutta_FG copy constructor called." << endl;
	this->fg = new eRK_FG(*fg.fg);
	this->aCalc = new aEff_Calculator(*fg.aCalc);
}

eRungeKutta_FG::~eRungeKutta_FG(){
	if (MoMMA::debug)
		cout << "eRungeKutta_FG destructor called." << endl;
	delete this->fg;
	delete this->aCalc;
}

void eRungeKutta_FG::fireRxns(vector<double>& k, vector<int>& classif, double tau){
	this->aCalc->calc_aEff(tau);
	this->fg->fireRxns(k,classif,tau,this->aCalc->a_eff);
}
