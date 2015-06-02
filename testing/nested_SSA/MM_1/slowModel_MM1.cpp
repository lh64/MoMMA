/*
 * slowModel_MM1.cpp
 *
 *  Created on: Nov 24, 2010
 *      Author: Leonard Harris
 */

#include "models_MM1.hh"
#include "../../../borrowed/util/util.hh"

using namespace std;
using namespace MoMMA;

SlowModel_MM1::SlowModel_MM1(double E_tot, double V, bool printToScreen){

	// 3 species, 1 reaction
	// ----------------------
	// E_T -> E_T + P		kcat

	// Parameters
	double Na_V = Util::NA*V;	// M^-1
	//
	double kcat = 1.0;			// s^-1
	//
	double ET_init = floor(E_tot*Na_V + 0.5); // molecules
	double P_init  = 0.0;

	// Species
	this->species.push_back(new SimpleSpecies("E_T",ET_init));
	this->species.push_back(new SimpleSpecies("P",  P_init));

	// Rate expressions
//	this->re = new RateElementary(kcat,RateElementary::UNIMOLECULAR);

	// Reactions
	// E_T -> E_T + P
	this->reaction.push_back(new ElementaryRxn(kcat,this->species.at(0),-1,this->species,vector<int>(2,1)));

	// Print to screen
	if (printToScreen){
		cout << "Slow Model: " << endl;
		cout << "-----------" << endl << endl;
		for (unsigned int i=0;i < this->species.size();i++){
			cout << "[" << i << "]: " << this->species.at(i)->name << ", x = " << this->species.at(i)->population << endl;
		}
		cout << endl;
		for (unsigned int i=0;i < this->reaction.size();i++){
			cout << "[" << i << "]: " << this->reaction.at(i)->toString() << ", k = ";
			cout << re->c << endl;
		}
		cout << endl;
	}
}

SlowModel_MM1::~SlowModel_MM1(){
	// Species
	for (unsigned int i=0;i < this->species.size();i++){
		delete this->species.at(i);
	}
	// Reactions
	for (unsigned int i=0;i < this->reaction.size();i++){
		delete this->reaction.at(i);
	}
	// Rate Expression
	delete this->re;
}
