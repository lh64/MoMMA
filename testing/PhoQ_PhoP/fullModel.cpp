/*
 * fullModel.cpp
 *
 *  Created on: Oct 11, 2010
 *      Author: Leonard Harris
 */

#include <iostream>
#include <string>
#include <cmath>

#include "../../borrowed/util/util.hh"
#include "fullModel.hh"

using namespace std;
using namespace MoMMA;

FullModel::FullModel(double volume){

	cout << "Full PhoQ/PhoP Model (V = " << volume << ")\n--------------------\n";

	double Na_V = Util::NA*volume;

	// 4 species (RR,RRp,HK,HKp), 8 reactions
	// --------------------------------------
	//
	// Autoregulation
	// 0) * -> RR; 				rate = B
	// 1) RRp -> RRp + RR; 		rate = A*[RRp]/(D+[RRp])
	// 2) RR -> *; 				rate = 1/tau*[RR]
	// 3) RRp -> *; 			rate = 1/tau*[RRp]
	//
	// Phosphorylation
	// 4) HK -> HKp;			rate = kf*[HK]
	// 5) HKp -> HK; 			rate = kr*[HKp]
	// 6) RR + HKp -> RRp + HK; rate = kt/Kmt*[RR][HKp]
	// 7) RRp + HK -> RR + HK; 	rate = kp/Kmp*[RRp][HK]

	// Parameters
	//
	// Autoregulation (A*tau = 45 M, B*tau = 15 M, D = 40 M)
	double A = 45.0*Na_V;	// M/s
	double B = 15.0*Na_V;	// M/s
	double D = 40.0*Na_V;	// M
	double tau = 1.0;		// s
	//
	// Phosphorylation (Cp = kf*Kmp/kp = 30 M, Ct = kr*Kmt/kt = 1 M)
	double kf =  3e4;		// Rate of kinase activity (1/s)
	double Kmp = 1e3*Na_V;	// Michaelis constant for phosphotase activity (M)
	double kp =  1e6;		// Rate of reverse phosphotransfer activity (1/s)
	double kr =  1e4;		// Rate of phosphotase activity (1/s)
	double Kmt = 1e3*Na_V;	// Michaelis constant for phosphotransfer activity (M)
	double kt =  1e7;		// Rate of phosphotransfer activity (1/s)
	//
	double HK_init = floor(10.0*Na_V + 0.5);	// Initial concentration (M)

	// Species
	this->species.push_back(new SimpleSpecies("RR",0.0));  	  // RR
	this->species.push_back(new SimpleSpecies("RRp",0.0)); 	  // RRp
	this->species.push_back(new SimpleSpecies("HK",HK_init)); // HK
	this->species.push_back(new SimpleSpecies("HKp",0.0));	  // HKp

	for (unsigned int i=0;i < this->species.size();i++){
		cout << this->species.at(i)->name << ": " << this->species.at(i)->population << endl;
	}
	cout << endl;

	// Reactions
	//
	// Autoregulation
	// * -> RR
//	RateElementary* r_syn = new RateElementary(B,RateElementary::SYNTHESIS);
	this->reaction.push_back(new ElementaryRxn(B,vector<SimpleSpecies*>(),vector<int>(),this->species.at(0),1));
	//
	// RRp -> RRp + RR
	map<SimpleSpecies*,int> stoichSpecies;
	stoichSpecies.insert( pair<SimpleSpecies*,int>(this->species[0],1) );
	vector<SimpleSpecies*> rateSpecies;
	rateSpecies.push_back(this->species[1]);
	RateSaturation* r_sat = new RateSaturation(A,D,rateSpecies,vector<int>(1,-1));
//	this->reaction.push_back(new Reaction(this->species.at(1),-1,
//							 vector<SimpleSpecies*>(this->species.begin(),this->species.begin()+2),
//							 vector<int>(2,1),r_sat));
	this->reaction.push_back(new Reaction(stoichSpecies,rateSpecies,r_sat));
	//
	// RR -> *
//	RateElementary* r_lu = new RateElementary(1.0/tau,RateElementary::UNIMOLECULAR);
	this->reaction.push_back(new ElementaryRxn(1.0/tau,this->species.at(0),-1,vector<SimpleSpecies*>(),vector<int>()));
	//
	// RRp -> *
	this->reaction.push_back(new ElementaryRxn(1.0/tau,this->species.at(1),-1,vector<SimpleSpecies*>(),vector<int>()));
	//
	// Phosphorylation
	//
	// HK -> HKp
//	RateElementary* re0 = new RateElementary(kf,RateElementary::UNIMOLECULAR);
	this->reaction.push_back(new ElementaryRxn(kf,this->species.at(2),-1,this->species.at(3),1));
	//
	// HKp -> HK
//	RateElementary* re1 = new RateElementary(kr,RateElementary::UNIMOLECULAR);
	this->reaction.push_back(new ElementaryRxn(kr,this->species.at(3),-1,this->species.at(2),1));
	//
	// RR + HKp -> RRp + HK
//	RateElementary* re2 = new RateElementary(kt/Kmt,RateElementary::BIMOLECULAR_AB);
//	vector<SimpleSpecies*> r_vec2; r_vec2.push_back(this->species.at(0)); r_vec2.push_back(this->species.at(3));
//	vector<SimpleSpecies*> p_vec2; p_vec2.push_back(this->species.at(1)); p_vec2.push_back(this->species.at(2));
	stoichSpecies.clear();
	stoichSpecies.insert( pair<SimpleSpecies*,int>(this->species[0],-1) ); // RR
	stoichSpecies.insert( pair<SimpleSpecies*,int>(this->species[3],-1) ); // HKp
	stoichSpecies.insert( pair<SimpleSpecies*,int>(this->species[1],1) );  // RRp
	stoichSpecies.insert( pair<SimpleSpecies*,int>(this->species[2],1) );  // HK
	rateSpecies.clear();
	rateSpecies.push_back(this->species[0]);
	rateSpecies.push_back(this->species[3]);
	RateSaturation* re2 = new RateSaturation(kt,Kmt,rateSpecies,vector<int>(2,-1));
//	this->reaction.push_back(new Reaction(r_vec2,vector<int>(2,-1),p_vec2,vector<int>(2,1),re2));
	this->reaction.push_back(new Reaction(stoichSpecies,rateSpecies,re2));
	//
	// RRp + HK -> RR + HK
//	RateElementary* re3 = new RateElementary(kp/Kmp,RateElementary::BIMOLECULAR_AB);
//	vector<SimpleSpecies*> r_vec3; r_vec3.push_back(this->species.at(1)); r_vec3.push_back(this->species.at(2));
//	vector<SimpleSpecies*> p_vec3; p_vec3.push_back(this->species.at(0)); p_vec3.push_back(this->species.at(2));
	stoichSpecies.clear();
	stoichSpecies.insert( pair<SimpleSpecies*,int>(this->species[1],-1) ); // RRp
	stoichSpecies.insert( pair<SimpleSpecies*,int>(this->species[0],1) );  // RR
	rateSpecies.clear();
	rateSpecies.push_back(this->species[1]);
	rateSpecies.push_back(this->species[2]);
	RateSaturation* re3 = new RateSaturation(kp,Kmp,rateSpecies,vector<int>(2,-1));
//	this->reaction.push_back(new Reaction(r_vec3,vector<int>(2,-1),p_vec3,vector<int>(2,1),re3));
	this->reaction.push_back(new Reaction(stoichSpecies,rateSpecies,re3));

	for (unsigned int i=0;i < this->reaction.size();i++){
		cout << "(" << i << ") " << this->reaction.at(i)->toString() << ", rate = " << this->reaction.at(i)->getRate() << endl;
	}
}

FullModel::~FullModel(){
	for (unsigned int i=0;i < this->species.size();i++){
		delete this->species.at(i);
	}
	for (unsigned int i=0;i < this->reaction.size();i++){
		delete this->reaction.at(i);
	}
}
