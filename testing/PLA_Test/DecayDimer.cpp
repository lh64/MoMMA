/*
 * DecayDimer.cpp
 *
 *  Created on: Feb 18, 2011
 *      Author: Leonard Harris
 */

#include "plaTest.hh"

using namespace std;
using namespace MoMMA;

DecayDimer::DecayDimer(){

	cout << "*** Decaying-Dimerizing reaction set ***" << endl << endl;

	// Decaying-Dimerizing rxn set
	// 3 species (S1,S2,S3), 4 reactions
	// -------------------------------
    // 0) S1 -> *		c0 = 1.0   (unitless)
    // 1) 2S1 -> S2		c1 = 0.002
    // 2) S2 -> 2S1 	c2 = 0.5
	// 3) S2 -> S3		c3 = 0.02

	// Parameters
	double c0 = 1.0;
	double c1 = 0.002;
	double c2 = 0.5;
	double c3 = 0.02;
	//
	double X1_init = 2921.0; // molecules
	double X2_init = 22064.0;
	double X3_init = 6771.0;

	// Species
	this->sp.push_back(new SimpleSpecies("S1",X1_init));
	this->sp.push_back(new SimpleSpecies("S2",X2_init));
	this->sp.push_back(new SimpleSpecies("S3",X3_init));

	for (unsigned int i=0;i < this->sp.size();i++){
		cout << this->sp[i]->name << ": " << this->sp[i]->population << endl;
	}
	cout << endl;

	// Reactions
	//
	// 0) S1 -> *
//	this->re.push_back(new RateElementary(c0,RateElementary::UNIMOLECULAR));
	this->rxn.push_back(new ElementaryRxn(c0,this->sp[0],-1,vector<SimpleSpecies*>(),vector<int>()));

	// 1) 2S1 -> S2
//	this->re.push_back(new RateElementary(c1,RateElementary::BIMOLECULAR_AA));
	this->rxn.push_back(new ElementaryRxn(c1,this->sp[0],-2,this->sp[1],1));

	// 2) S2 -> 2S1
//	this->re.push_back(new RateElementary(c2,RateElementary::UNIMOLECULAR));
	this->rxn.push_back(new ElementaryRxn(c2,this->sp[1],-1,this->sp[0],2));

	// 3) S2 -> S3
//	this->re.push_back(new RateElementary(c3,RateElementary::UNIMOLECULAR));
	this->rxn.push_back(new ElementaryRxn(c3,this->sp[1],-1,this->sp[2],1));

	for (unsigned int i=0;i < this->rxn.size();i++){
		cout << this->rxn[i]->toString() << ", rate = " << this->rxn[i]->getRate() << endl;
	}
	cout << endl;

}

DecayDimer::~DecayDimer(){
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
