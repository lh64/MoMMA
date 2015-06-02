/*
 * CaOscillate.cpp
 *
 *  Created on: Feb 18, 2011
 *      Author: Leonard Harris
 */

#include "plaTest.hh"

using namespace std;
using namespace MoMMA;

CaOscillate::CaOscillate(double V){

	cout << "*** Calcium Oscillations - Kummer et al. core model ***" << endl << endl;

	// ***** Calcium Oscillations - Kummer et al. Core Model *****

	// 3 species, 8 reactions:
	// --------------------
	// (0)  * -> Ga				(simple synthesis)
	// (1)  Ga -> 2Ga 			(autocatalytic)
	// (2)  Ga + PLC -> PLC 	(2nd order Sat)
	// (3)  Ga + Ca  -> Ca  	(2nd order Sat)
	// (4)  Ga -> PLC + Ga  	(simple catalytic)
	// (5)  PLC -> *			(1st order Sat)
	// (6)  Ga -> Ca + Ga   	(simple catalytic)
	// (7)  Ca  -> *			(1st order Sat)

	// Parameters
	double Na    = 6.022e23;	// Avogadro's # [mol^-1]
	double Na_V  = Na*V;		// [M^-1]
	//
	double k0	= 0.212*Na_V; 	// [M s^-1]
	double k1  	= 2.85;			// [s^-1]
	double k2_c = 1.52;			// [s^-1]
	double k2_m = 0.19*Na_V;	// [M]
	double k3_c = 4.88;			// [s^-1]
	double k3_m = 1.18*Na_V;	// [M]
	double k4 	= 1.24;			// [s^-1]
	double k5_c = 32.24*Na_V;	// [M s^-1]
	double k5_m = 29.09*Na_V;	// [M]
	double k6 	= 13.58;		// [s^-1]
	double k7_c = 153.0*Na_V;	// [M s^-1]
	double k7_m = 0.16*Na_V;	// [M]
	//
	double Ga_0  = 0.01*Na_V; 	// [M]
	double PLC_0 = 0.01*Na_V; 	// [M]
	double Ca_0  = 0.01*Na_V; 	// [M]

	// Species
	this->sp.push_back(new SimpleSpecies("Ga", floor(Ga_0 + 0.5)));
	this->sp.push_back(new SimpleSpecies("PLC",floor(PLC_0 + 0.5)));
	this->sp.push_back(new SimpleSpecies("Ca", floor(Ca_0 + 0.5)));

	for (unsigned int i=0;i < sp.size();i++){
		cout << sp[i]->name << ": " << sp[i]->population << endl;
	}
	cout << endl;

	// Reactions
	//
	// (0)  * -> Ga			(simple synthesis)
//	this->re.push_back(new RateElementary(k0,RateElementary::SYNTHESIS));
	this->rxn.push_back(new ElementaryRxn(k0,vector<SimpleSpecies*>(),vector<int>(),this->sp[0],1));

	// (1)  Ga -> 2Ga 		(autocatalytic)
//	this->re.push_back(new RateElementary(k1,RateElementary::UNIMOLECULAR));
	this->rxn.push_back(new ElementaryRxn(k1,this->sp[0],-1,this->sp[0],2));

	// (2)  Ga + PLC -> PLC (2nd order Sat)
	map<SimpleSpecies*,int> stoichSpecies;
	stoichSpecies.insert( pair<SimpleSpecies*,int>(this->sp[0],-1) );
	vector<SimpleSpecies*> rateSpecies; rateSpecies.push_back(this->sp[0]); rateSpecies.push_back(this->sp[1]);
	this->re.push_back(new RateSaturation(k2_c,k2_m,rateSpecies,vector<int>(2,-1)));
//	this->rxn.push_back(new Reaction(this->sp[0],-1,vector<SimpleSpecies*>(this->sp.begin(),this->sp.end()-1),this->re[this->re.size()-1]));
	this->rxn.push_back(new Reaction(stoichSpecies,rateSpecies,this->re[this->re.size()-1]));

	// (3)  Ga + Ca  -> Ca  (2nd order Sat)
	stoichSpecies.clear();
	stoichSpecies.insert( pair<SimpleSpecies*,int>(this->sp[0],-1) );
	rateSpecies.clear(); rateSpecies.push_back(this->sp[0]); rateSpecies.push_back(this->sp[2]);
	this->re.push_back(new RateSaturation(k3_c,k3_m,rateSpecies,vector<int>(2,-1)));
//	this->rxn.push_back(new Reaction(this->sp[0],-1,rateSp3,this->re[this->re.size()-1]));
	this->rxn.push_back(new Reaction(stoichSpecies,rateSpecies,this->re[this->re.size()-1]));

	// (4)  Ga -> PLC + Ga  (simple catalytic)
//	this->re.push_back(new RateElementary(k4,RateElementary::UNIMOLECULAR));
	vector<SimpleSpecies*> prod; prod.push_back(this->sp[0]); prod.push_back(this->sp[1]);
	this->rxn.push_back(new ElementaryRxn(k4,this->sp[0],-1,prod,vector<int>(2,1)));

	// (5)  PLC -> *		(1st order Sat)
	stoichSpecies.clear();
	stoichSpecies.insert( pair<SimpleSpecies*,int>(this->sp[1],-1) );
	rateSpecies.clear(); rateSpecies.push_back(this->sp[1]);
	this->re.push_back(new RateSaturation(k5_c,k5_m,rateSpecies,vector<int>(1,-1)));
//	this->rxn.push_back(new Reaction(this->sp[1],-1,this->sp[1],this->re[this->re.size()-1]));
	this->rxn.push_back(new Reaction(stoichSpecies,rateSpecies,this->re[this->re.size()-1]));

	// (6)  Ga -> Ca + Ga   (simple catalytic)
//	this->re.push_back(new RateElementary(k6,RateElementary::UNIMOLECULAR));
	prod.clear(); prod.push_back(this->sp[0]); prod.push_back(this->sp[2]);
	this->rxn.push_back(new ElementaryRxn(k6,this->sp[0],-1,prod,vector<int>(2,1)));

	// (7)  Ca  -> *		(1st order Sat)
	stoichSpecies.clear();
	stoichSpecies.insert( pair<SimpleSpecies*,int>(this->sp[2],-1) );
	rateSpecies.clear(); rateSpecies.push_back(this->sp[2]);
	this->re.push_back(new RateSaturation(k7_c,k7_m,rateSpecies,vector<int>(1,-1)));
//	this->rxn.push_back(new Reaction(this->sp[2],-1,this->sp[2],this->re[this->re.size()-1]));
	this->rxn.push_back(new Reaction(stoichSpecies,rateSpecies,this->re[this->re.size()-1]));

	for (unsigned int i=0;i < this->rxn.size();i++){
		cout << this->rxn[i]->toString();
		if (this->rxn[i]->rateSpecies.size() > 0){
			cout << ", rateSp = " << this->rxn[i]->rateSpecies[0]->name;
			for (unsigned int j=1;j < this->rxn[i]->rateSpecies.size();j++){
				cout << ", " << this->rxn[i]->rateSpecies[j]->name;
			}
		}
		cout << endl;
	}
	cout << endl;
}

CaOscillate::~CaOscillate(){
	// Species
	for (unsigned int j=0;j < this->sp.size();j++){
		delete this->sp[j];
	}
	// Reactions and rate expressions
	for (unsigned int v=0;v < this->rxn.size();v++){
		delete this->rxn[v];
		delete this->re[v];
	}
}
