/*
 * fastTranslator_MM1.cpp
 *
 *  Created on: Dec 10, 2010
 *      Author: Leonard Harris
 */

#include "translators_MM1.hh"

using namespace std;
using namespace MoMMA;

FastTranslator_MM1::FastTranslator_MM1(){
	if (MoMMA::debug)
		cout << "FastTranslator_MM1 constructor called.\n";
}

FastTranslator_MM1::FastTranslator_MM1(DoublePtrVectorData* localData){
	if (MoMMA::debug)
		cout << "FastTranslator_MM1 constructor called.\n";
	this->localData = localData;
}

void FastTranslator_MM1::translate(Data* inData){
	double P_new = *static_cast<DoublePtrData*>(inData)->getDoublePtr();
	double dP    = P_new - *static_cast<DoublePtrVectorData*>(this->localData)->getDoublePtr(0);
	cout << "Translated value [0]: "
		 << ( *static_cast<DoublePtrVectorData*>(this->localData)->getDoublePtr(0) = P_new )
		 << endl;
	cout << "Translated value [1]: "
		 << ( *static_cast<DoublePtrVectorData*>(this->localData)->getDoublePtr(1) = dP )
		 << endl;
}
