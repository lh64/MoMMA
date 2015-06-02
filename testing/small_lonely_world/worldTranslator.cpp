/*
 * worldTranslator.cpp
 *
 *  Created on: Feb 8, 2010
 *      Author: Leonard Harris
 */

#include "worldTranslator.hh"
#include "../../borrowed/primitiveData.hh"
#include "../../borrowed/util/util.hh"

using namespace std;
using namespace MoMMA;

WorldTranslator::WorldTranslator(){
	if (MoMMA::debug) cout << "WorldTranslator constructor called." << endl;
}

WorldTranslator::WorldTranslator(Data* localData){
	if (MoMMA::debug) cout << "WorldTranslator constructor called." << endl;
	this->localData = localData;
}

WorldTranslator::~WorldTranslator(){ cout << "WorldTranslator destructor called.\n"; }

void WorldTranslator::translate(Data* inData){

	cout << "'" << inData->getName() <<"' is being translated..." << endl;
	//
	double Yp = *(static_cast<DoublePtrData*>(inData)->getDoublePtr());
	double c1 = 1.0;
	double c2 = 100.0;
	double c3 = 0.5;
	int h = 2; // Hill coefficient

	double Yph = Yp;
	double c2h = c2;
	for (int i=1;i<h;i++){
		Yph *= Yp;
		c2h *= c2;
	}

	// kf = c1*Yp^(-h)/(c2^(-h)+Yp^(-h)) + c3
	double kf = c1*(1.0/Yph)/(1.0/c2h + 1.0/Yph) + c3;
	// kr = c1*Yp^h/(c2^h+Yp^h) + c3
	double kr = c1*Yph/(c2h + Yph) + c3;
	//
	for (int i=0;i<6;i++){
		*(static_cast<DoublePtrMatrixData*>(this->localData)->getDoublePtr(0,i)) = kf;
	}
	for (int i=0;i<6;i++){
		*(static_cast<DoublePtrMatrixData*>(this->localData)->getDoublePtr(1,i)) = kr;
	}
	//
	cout << "Yp = " << Yp << endl;
	cout << "Translated values: " << endl;
	cout << "  kf = " << *(static_cast<DoublePtrMatrixData*>(this->localData)->getDoublePtr(0,0)) << endl;
	cout << "  kr = " << *(static_cast<DoublePtrMatrixData*>(this->localData)->getDoublePtr(1,0)) << endl;
}
