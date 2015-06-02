/*
 * trackTranslator.cpp
 *
 *  Created on: Apr 22, 2010
 *      Author: Leonard Harris
 */

#include <iostream>
#include <math.h>
#include "trackTranslator.hh"
#include "../../borrowed/primitiveData.hh"

using namespace std;
using namespace MoMMA;

TrackTranslator::TrackTranslator(Data* localData, double N, double M, double L) : Translator(localData){
	if (localData->getType().compare("DoublePtrType") != 0){
		cout << "Oops in TrackTranslator constructor: Data must be DoublePtrType. Exiting.\n";
		exit(1);
	}
	else{
		if (MoMMA::debug) cout << "TrackTranslator constructor called.\n";
//		this->localData = localData;
		this->N = N;
		this->M = M;
		this->L = L;
	}
}

TrackTranslator::~TrackTranslator(){
	if (MoMMA::debug) cout << "TrackTranslator destructor called.\n";
}

void TrackTranslator::translate(Data* inData){
	if (inData->getType().compare("DoublePtrType") != 0){
		cout << "Oops in TrackTranslator::translate(): Incoming Data must be DoublePtrType. Exiting.\n";
		exit(1);
	}
	else{
		double V_in = *static_cast<DoublePtrData*>(inData)->getDoublePtr();
		cout << "Translated value: " <<
				( *static_cast<DoublePtrData*>(this->localData)->getDoublePtr() = this->N + V_in/(this->M + V_in)*this->L ) << endl;
	}
}
