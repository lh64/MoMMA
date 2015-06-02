/*
 * slowTranslator_MM1.cpp
 *
 *  Created on: Dec 4, 2010
 *      Author: Leonard Harris
 */

#include "translators_MM1.hh"

using namespace std;
using namespace MoMMA;

SlowTranslator_MM1::SlowTranslator_MM1(){
	if (MoMMA::debug)
		cout << "SlowTranslator_MM1 constructor called.\n";
}

SlowTranslator_MM1::SlowTranslator_MM1(DoublePtrData* localData, double kcat){
	if (MoMMA::debug)
		cout << "SlowTranslator_MM1 constructor called.\n";
	this->localData = localData;
	this->kcat = kcat;
}

void SlowTranslator_MM1::translate(Data* inData){
	double f = *static_cast<DoublePtrData*>(inData)->getDoublePtr();
	if (!MoMMA::isNAN(f)){
		cout << "Translated value: " <<
		( *static_cast<DoublePtrData*>(this->localData)->getDoublePtr() = this->kcat*f )
		<< endl;
	}
	else{
		cout << "Error in SlowTranslator_MM1::translate(): f = NAN. Exiting." << endl;
		exit(1);
	}
}
