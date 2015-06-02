/*
 * cellTranslator.cpp
 *
 *  Created on: Feb 5, 2010
 *      Author: Leonard Harris
 */

#include "cellTranslator.hh"
#include "../../borrowed/primitiveData.hh"
#include "../../borrowed/util/util.hh"

using namespace std;
using namespace MoMMA;

CellTranslator::CellTranslator(){
	if (MoMMA::debug) cout << "CellTranslator constructor called." << endl;
}

CellTranslator::CellTranslator(Data* localData){
	if (MoMMA::debug) cout << "CellTranslator constructor called." << endl;
	this->localData = localData;
}

CellTranslator::~CellTranslator(){
	if (MoMMA::debug) cout << "CellTranslator destructor called.\n";
}

void CellTranslator::translate(Data* inData){

	cout << "'" << inData->getName() <<"' is being translated..." << endl;
	//
	int ligLevel = *(static_cast<IntPtrData*>(inData)->getIntPtr());
	cout << "Ligand level = " << ligLevel << endl;
	double ligPop;
	if (ligLevel == 0){
		ligPop = 250.0 + sqrt(25.0)*Util::RANDOM_GAUSSIAN();
	}
	else if (ligLevel == 1){
		ligPop = 750.0 + sqrt(75.0)*Util::RANDOM_GAUSSIAN();
	}
	else if (ligLevel == 2){
		ligPop = 1250.0 + sqrt(125.0)*Util::RANDOM_GAUSSIAN();
	}
	else {
		cout << "Oops in CellTranslator::translate()" << endl;
	}
	if (ligPop < 0.0){ ligPop = 0.0; }
	else{ // Round
		ligPop = floor(ligPop + 0.5);
	}
	*(static_cast<DoublePtrData*>(this->localData)->getDoublePtr()) = ligPop;
	//
	cout << "Translated value = " << *(static_cast<DoublePtrData*>(this->localData)->getDoublePtr()) << endl;
}
