/*
 * fullModel_MM1.cpp
 *
 *  Created on: Nov 30, 2010
 *      Author: Leonard Harris
 */

#include "models_MM1.hh"
#include "../../../borrowed/util/util.hh"

using namespace std;
using namespace MoMMA;

FullModel_MM1::FullModel_MM1(double E_tot, double S_tot, double V, bool printToScreen){

	// 4 species, 3 reactions
	// ----------------------
	// E + S <-> ES		kf,kr
	// ES -> E + P		kcat

	// Parameters
	double Na_V = Util::NA*V;	// M^-1
	//
	double kf = 1e4;			// M^-1 s^-1
	double kr = 1e4;			// s^-1
	double kcat = 1.0;			// s^-1
	//
	double E_init  = floor(E_tot*Na_V + 0.5); // molecules
	double S_init  = floor(S_tot*Na_V + 0.5); // molecules
	double ES_init = 0.0;
	double P_init  = 0.0;

	// Species
	this->species.push_back(new SimpleSpecies("E", E_init));
	this->species.push_back(new SimpleSpecies("S", S_init));
	this->species.push_back(new SimpleSpecies("ES",ES_init));
	this->species.push_back(new SimpleSpecies("P", P_init));

	// Rate expressions
//	this->re_f   = new RateElementary(kf/Na_V,RateElementary::BIMOLECULAR_AB);
//	this->re_r   = new RateElementary(kr,RateElementary::UNIMOLECULAR);
//	this->re_cat = new RateElementary(kcat,RateElementary::UNIMOLECULAR);

	// Reactions
	// E + S -> ES
	this->reaction.push_back(new ElementaryRxn(
							 kf/Na_V,
							 vector<SimpleSpecies*>(this->species.begin(),this->species.begin()+2),vector<int>(2,-1),
							 this->species.at(2),1));
	// ES -> E + S
	this->reaction.push_back(new ElementaryRxn(
							 kr,
							 this->species.at(2),-1,
							 vector<SimpleSpecies*>(this->species.begin(),this->species.begin()+2),vector<int>(2,1)));

	// ES -> E + P
	vector<SimpleSpecies*> pCat; pCat.push_back(this->species.at(0)); pCat.push_back(this->species.at(3));
	this->reaction.push_back(new ElementaryRxn(
							 kcat,
							 this->species.at(2),-1,
							 pCat,vector<int>(2,1)));

	// Print to screen
	if (printToScreen){
		cout << "Full Model: " << endl;
		cout << "-----------" << endl << endl;
		for (unsigned int i=0;i < this->species.size();i++){
			cout << "[" << i << "]: " << this->species.at(i)->name << ", x = " << this->species.at(i)->population << endl;
		}
		cout << endl;
		for (unsigned int i=0;i < this->reaction.size();i++){
			cout << "[" << i << "]: " << this->reaction.at(i)->toString() << ", k = ";
			if (i == 0){
				cout << this->re_f->c << endl;
			}
			else if (i==1){
				cout << this->re_r->c << endl;
			}
			else{
				cout << this->re_cat->c << endl;
			}
		}
		cout << endl;
	}
}

FullModel_MM1::~FullModel_MM1(){
	// Species
	for (unsigned int i=0;i < this->species.size();i++){
		delete this->species.at(i);
	}
	// Reactions
	for (unsigned int i=0;i < this->reaction.size();i++){
		delete this->reaction.at(i);
	}
	// Rate Expressions
	delete this->re_f;
	delete this->re_r;
	delete this->re_cat;
}
