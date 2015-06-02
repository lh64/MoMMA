/*
 * slowModel.cpp
 *
 *  Created on: Nov 15, 2010
 *      Author: Leonard Harris
 */

#include "models.hh"

using namespace std;
using namespace MoMMA;

SlowModel::SlowModel(bool printToScreen){

	// 2 species, 2 reactions
	// ----------------------
	// S3 <-> S6	kf,kr

	// Parameters
	double kf = 2.0;
	double kr = 3.0;

	// Species
	this->species.push_back(new SimpleSpecies("S3",0.0));
	this->species.push_back(new SimpleSpecies("S6",0.0));

	// Rate expressions
//	RateElementary* re_f = new RateElementary(kf,RateElementary::UNIMOLECULAR);
//	RateElementary* re_r = new RateElementary(kr,RateElementary::UNIMOLECULAR);

	// Reactions
	// S3 <-> S6
	this->reaction.push_back(new ElementaryRxn(kf,this->species.at(0),-1,this->species.at(1),1));
	this->reaction.push_back(new ElementaryRxn(kr,this->species.at(1),-1,this->species.at(0),1));

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

SlowModel::~SlowModel(){

}

