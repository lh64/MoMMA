/*
 * translator.cpp
 *
 *  Created on: Feb 5, 2010
 *      Author: Leonard Harris
 */

#include <iostream>
#include "translator.hh"

using namespace std;
using namespace MoMMA;

Translator::Translator(){
	if (MoMMA::debug)
		cout << "Translator constructor called." << endl;
}

Translator::Translator(Data* localData){
	if (MoMMA::debug)
		cout << "Translator constructor called." << endl;
	this->localData = localData;
}

Translator::~Translator(){
	if (MoMMA::debug)
		cout << "Translator destructor called." << endl;
//	delete this->localData;
}

void Translator::translate(Data* inData){
	cout << "Error in Translator::translate(Data*): Must overload the base method. Exiting." << endl;
	exit(1);
}

void Translator::translate(Data inData){
	cout << "Error in Translator::translate(Data): Must overload the base method. Exiting." << endl;
	exit(1);
}
