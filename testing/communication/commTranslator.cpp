/*
 * commTranslator.cpp
 *
 *  Created on: Feb 13, 2010
 *      Author: Leonard Harris
 */

#include <iostream>
#include <string>

#include "commTranslator.hh"
#include "stringData.hh"

using namespace std;
using namespace MoMMA;

CommTranslator::CommTranslator(Data* localData){
	if (MoMMA::debug) cout << "CommTranslator constructor called.\n";
	this->localData = localData;
}

CommTranslator::~CommTranslator(){
	if (MoMMA::debug) cout << "CommTranslator destructor called.\n";
}

void CommTranslator::translate(Data* inData){

	if (inData->getType().compare("StringPtrType") == 0){
		cout << "Translated value: " << (
				*static_cast<StringPtrData*>(this->localData)->getStringPtr()
				= "tr(" + *static_cast<StringPtrData*>(inData)->getStringPtr() + ")"
				) << endl;
	}
	else if (inData->getType().compare("StringType") == 0){
		cout << "Translated value: " << (
				*static_cast<StringPtrData*>(this->localData)->getStringPtr()
				= "tr(" + static_cast<StringData*>(inData)->getString() + ")"
				) << endl;
	}
	else{
		cout << "Oops in CommTranslator::translate(): Incoming data must be StringPtrType or StringType.\n";
	}
}
