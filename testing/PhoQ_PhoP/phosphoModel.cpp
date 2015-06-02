/*
 * phosphoModel.cpp
 *
 *  Created on: Aug 22, 2010
 *      Author: Leonard Harris
 */

#include <iostream>
#include <string>
#include <cmath>

#include "phosphoModel.hh"
#include "../../borrowed/util/util.hh"

using namespace std;
using namespace MoMMA;

PhosphoModel::PhosphoModel(double volume){

	cout << "Phosphorylation Module: (";

	double Na_V = Util::NA*volume;

	// 4 species (RR,RRp,HK,HKp), 4 reactions
	// --------------------------------------
	// 1) HK -> HKp;			rate = kf*[HK]
	// 2) HKp -> HK; 			rate = kr*[HKp]
	// 3) RR + HKp -> RRp + HK; rate = kt/Kmt*[RR][HKp]
	// 4) RRp + HK -> RR + HK; 	rate = kp/Kmp*[RRp][HK]

	// Parameters
	// Cp = (kf*Kmp)/kp = 30 M, Ct = (kr*Kmt)/kt = 1 M
	double kf =  3e4;		// Rate of kinase activity (1/s)
	double Kmp = 1e3*Na_V;	// Michaelis constant for phosphotase activity (M)
	double kp =  1e6;		// Rate of reverse phosphotransfer activity (1/s)
	double kr =  1e4;		// Rate of phosphotase activity (1/s)
	double Kmt = 1e3*Na_V;	// Michaelis constant for phosphotransfer activity (M)
	double kt =  1e7;		// Rate of phosphotransfer activity (1/s)

	cout << "V = " << volume << ", ";
	cout << "Cp = " << (kf*Kmp/kp)/Na_V << ", ";
	cout << "Ct = " << (kr*Kmt/kt)/Na_V;
	cout << ")\n-----------------------" << endl;

	double HK_init = floor(10.0*Na_V + 0.5);	// Initial concentration (M)

	// Species
	this->species.push_back(new SimpleSpecies("RR",0.0));  // RR
	this->species.push_back(new SimpleSpecies("RRp",0.0)); 	   // RRp
	this->species.push_back(new SimpleSpecies("HK",HK_init));  // HK
	this->species.push_back(new SimpleSpecies("HKp",0.0));	   // HKp

	for (unsigned int i=0;i < this->species.size();i++){
		cout << this->species.at(i)->name << ": " << this->species.at(i)->population << endl;
	}
	cout << endl;

	// Reactions

	// HK -> HKp
//	RateElementary* re0 = new RateElementary(kf,RateElementary::UNIMOLECULAR);
	this->reaction.push_back(new ElementaryRxn(kf,this->species.at(2),-1,this->species.at(3),1));

	// HKp -> HK
//	RateElementary* re1 = new RateElementary(kr,RateElementary::UNIMOLECULAR);
	this->reaction.push_back(new ElementaryRxn(kr,this->species.at(3),-1,this->species.at(2),1));

	// RR + HKp -> RRp + HK
//	RateElementary* re2 = new RateElementary(kt/Kmt,RateElementary::BIMOLECULAR_AB);
//	vector<SimpleSpecies*> r_vec2; r_vec2.push_back(this->species.at(0)); r_vec2.push_back(this->species.at(3));
//	vector<SimpleSpecies*> p_vec2; p_vec2.push_back(this->species.at(1)); p_vec2.push_back(this->species.at(2));
	map<SimpleSpecies*,int> stoichSpecies;
	stoichSpecies.insert( pair<SimpleSpecies*,int>(this->species[0],-1) ); // RR
	stoichSpecies.insert( pair<SimpleSpecies*,int>(this->species[3],-1) ); // HKp
	stoichSpecies.insert( pair<SimpleSpecies*,int>(this->species[1],1) );  // RRp
	stoichSpecies.insert( pair<SimpleSpecies*,int>(this->species[2],1) );  // HK
	vector<SimpleSpecies*> rateSpecies;
	rateSpecies.push_back(this->species[0]);
	rateSpecies.push_back(this->species[3]);
	RateSaturation* re2 = new RateSaturation(kt,Kmt,rateSpecies,vector<int>(2,-1));
//	this->reaction.push_back(new Reaction(r_vec2,vector<int>(2,-1),p_vec2,vector<int>(2,1),re2));
	this->reaction.push_back(new Reaction(stoichSpecies,rateSpecies,re2));

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
		cout << this->reaction.at(i)->toString() << ", rate = " << this->reaction.at(i)->getRate() << endl;
	}
}

PhosphoModel::~PhosphoModel(){
	for (unsigned int i=0;i < this->species.size();i++){
		delete this->species.at(i);
	}
	for (unsigned int i=0;i < this->reaction.size();i++){
		delete this->reaction.at(i);
	}
}
