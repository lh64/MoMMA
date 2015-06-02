/*
 * fastModel.cpp
 *
 *  Created on: Nov 15, 2010
 *      Author: Leonard Harris
 */

#include "models.hh"

using namespace std;
using namespace MoMMA;

FastModel::FastModel(bool printToScreen){

	// 8 species, 8 reactions
	// ----------------------
	// S1 <-> S2	kf,kr
	// S3 <-> S4	kf,kr
	// S5 <-> S6	kf,kr
	// S7 <-> S8	kf,kr

	// Parameters
	double kf = 2e12;
	double kr = 3e12;

	// Species
	this->species.push_back(new SimpleSpecies("S1",1.0));
	this->species.push_back(new SimpleSpecies("S2",0.0));
	this->species.push_back(new SimpleSpecies("S3",0.0));
	this->species.push_back(new SimpleSpecies("S4",0.0));
	this->species.push_back(new SimpleSpecies("S5",0.0));
	this->species.push_back(new SimpleSpecies("S6",0.0));
	this->species.push_back(new SimpleSpecies("S7",0.0));
	this->species.push_back(new SimpleSpecies("S8",0.0));

	// Rate expressions
//	RateElementary* re_f = new RateElementary(kf,RateElementary::UNIMOLECULAR);
//	RateElementary* re_r = new RateElementary(kr,RateElementary::UNIMOLECULAR);

	// Reactions
	// S1 <-> S2
	this->reaction.push_back(new ElementaryRxn(kf,this->species.at(0),-1,this->species.at(1),1));
	this->reaction.push_back(new ElementaryRxn(kr,this->species.at(1),-1,this->species.at(0),1));
	// S3 <-> S4
	this->reaction.push_back(new ElementaryRxn(kf,this->species.at(2),-1,this->species.at(3),1));
	this->reaction.push_back(new ElementaryRxn(kr,this->species.at(3),-1,this->species.at(2),1));
	// S5 <-> S6
	this->reaction.push_back(new ElementaryRxn(kf,this->species.at(4),-1,this->species.at(5),1));
	this->reaction.push_back(new ElementaryRxn(kr,this->species.at(5),-1,this->species.at(4),1));
	// S7 <-> S8
	this->reaction.push_back(new ElementaryRxn(kf,this->species.at(6),-1,this->species.at(7),1));
	this->reaction.push_back(new ElementaryRxn(kr,this->species.at(7),-1,this->species.at(6),1));

	// Print to screen
	if (printToScreen){
		cout << "Fast Model: " << endl;
		cout << "-----------" << endl << endl;
		for (unsigned int i=0;i < this->species.size();i++){
			cout << "[" << i << "]: " << this->species.at(i)->name << ", x = " << this->species.at(i)->population << endl;
		}
		cout << endl;
		for (unsigned int i=0;i < this->reaction.size();i++){
			cout << "[" << i << "]: " << this->reaction.at(i)->toString() << ", k = ";
			if (i == 0 || i == 2 || i == 4 || i == 6){
				cout << kf << endl;
			}
			else{
				cout << kr << endl;
			}
		}
		cout << endl;
	}
}

FastModel::~FastModel(){

}
