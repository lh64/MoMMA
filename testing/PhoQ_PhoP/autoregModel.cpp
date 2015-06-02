/*
 * autoregModel.cpp
 *
 *  Created on: Aug 22, 2010
 *      Author: Leonard Harris
 */

#include <string>
#include "autoregModel.hh"
#include "../../borrowed/util/util.hh"

using namespace std;
using namespace MoMMA;

AutoregModel::AutoregModel(double volume){

	cout << "Autoregulation Module (V = " << volume << ")\n---------------------\n";

	double Na_V = Util::NA*volume;	// 1/M

	// 2 species (RR,RRp), 4 reactions
	// -------------------------------
	// 1) * -> RR; 			rate = B
	// 2) RRp -> RRp + RR; 	rate = A*[RRp]/(D+[RRp])
	// 3) RR -> *; 			rate = 1/tau*[RR]
	// 4) RRp -> *; 		rate = 1/tau*[RRp]

	// Parameters (A*tau = 45 M, B*tau = 15 M, D = 40 M)
	double A = 45.0*Na_V; 	// M/s
	double B = 15.0*Na_V;	// M/s
	double D = 40.0*Na_V;	// M/s
	double tau = 1.0;		// s

	// Species
	this->species.push_back(new SimpleSpecies("RR",0.0));  // RR
	this->species.push_back(new SimpleSpecies("RRp",0.0)); // RRp

	for (unsigned int i=0;i < this->species.size();i++){
		cout << this->species.at(i)->name << ": " << this->species.at(i)->population << endl;
	}
	cout << endl;

	// Reactions

	// * -> RR
//	RateElementary* r_syn = new RateElementary(B,RateElementary::SYNTHESIS);
	this->reaction.push_back(new ElementaryRxn(B,vector<SimpleSpecies*>(),vector<int>(),this->species.at(0),1));

	// RRp -> RRp + RR
	map<SimpleSpecies*,int> stoichSpecies;
	stoichSpecies.insert( pair<SimpleSpecies*,int>(this->species[0],1) );
	vector<SimpleSpecies*> rateSpecies;
	rateSpecies.push_back(this->species[1]);
	RateSaturation* r_sat = new RateSaturation(A,D,rateSpecies,vector<int>(1,-1));
//	this->reaction.push_back(new Reaction(this->species.at(1),-1,this->species,vector<int>(2,1),r_sat));
	this->reaction.push_back(new Reaction(stoichSpecies,rateSpecies,r_sat));

	// RR -> *
//	RateElementary* r_lu = new RateElementary(1.0/tau,RateElementary::UNIMOLECULAR);
	this->reaction.push_back(new ElementaryRxn(1.0/tau,this->species.at(0),-1,vector<SimpleSpecies*>(),vector<int>()));

	// RRp -> *
	this->reaction.push_back(new ElementaryRxn(1.0/tau,this->species.at(1),-1,vector<SimpleSpecies*>(),vector<int>()));

	for (unsigned int i=0;i < this->reaction.size();i++){
		cout << this->reaction.at(i)->toString() << ", rate = " << this->reaction.at(i)->getRate() << endl;
	}
}

AutoregModel::~AutoregModel(){
	for (unsigned int i=0;i < this->species.size();i++){
		delete this->species.at(i);
	}
	for (unsigned int i=0;i < this->reaction.size();i++){
		delete this->reaction.at(i);
	}
}
