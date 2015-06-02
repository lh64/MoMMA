/*
 * trivialTranslator.cpp
 *
 *  Created on: Feb 13, 2010
 *      Author: Leonard Harris
 */

#include <string>
#include "../../borrowed/primitiveData.hh"
#include "../../testing/communication/stringData.hh"
#include "trivialTranslator.hh"

using namespace std;
using namespace MoMMA;

TrivialTranslator::TrivialTranslator(){
	if (MoMMA::debug)
		cout << "TrivialTranslator constructor called.\n";
}

TrivialTranslator::TrivialTranslator(Data* localData){
	if (MoMMA::debug)
		cout << "TrivialTranslator constructor called.\n";
	this->localData = localData;
}

void TrivialTranslator::translate(Data* inData){

	if (inData->getType() == "StringPtrType"){
		cout << "Translated value: " <<
		( *static_cast<StringPtrData*>(this->localData)->getStringPtr() =
				*static_cast<StringPtrData*>(inData)->getStringPtr() )
				<< endl;
	}
	else if(inData->getType() == "DoublePtrType"){
		cout << "Translated value: " <<
		( *static_cast<DoublePtrData*>(this->localData)->getDoublePtr() =
				*static_cast<DoublePtrData*>(inData)->getDoublePtr() )
				<< endl;
	}
	else if(inData->getType() == "IntPtrType"){
		cout << "Translated value: " <<
		( *static_cast<IntPtrData*>(this->localData)->getIntPtr() =
				*static_cast<IntPtrData*>(inData)->getIntPtr() )
				<< endl;
	}
	else if(inData->getType() == "DoublePtrVectorType"){
		cout << "Translated value(s): " << endl;
		for (int i=0;i < static_cast<DoublePtrVectorData*>(this->localData)->getNumElements();i++){
			cout <<
			( *static_cast<DoublePtrVectorData*>(this->localData)->getDoublePtr(i) =
					*static_cast<DoublePtrVectorData*>(inData)->getDoublePtr(i) )
					<< endl;
		}
	}
	// ...
	// ...
	// ...
	else{
		cout << "Error in TrivialTranslator::translate(): Data type " << inData->getType() <<  " not recognized."
			 << " Exiting." << endl;
		exit(1);
	}

}
