/*
 * nullTranslator.cpp
 *
 *  Created on: Nov 6, 2010
 *      Author: Leonard Harris
 */

#include "nullTranslator.hh"

using namespace std;
using namespace MoMMA;

NullTranslator::NullTranslator(string name){
	if (MoMMA::debug)
		cout << "NullTranslator constructor called.\n";
	this->localData = new Data(name,"NullType");
}

NullTranslator::~NullTranslator(){
	delete this->localData;
}

void NullTranslator::translate(Data* inData){
	cout << "Null translator: Do nothing." << endl;
}
