/*
 * tauCalculator.cpp
 *
 *  Created on: Feb 7, 2011
 *      Author: Leonard Harris
 */

#include "tauCalculator.hh"

using namespace std;
using namespace MoMMA;

TauCalculator::TauCalculator(){
	if (MoMMA::debug)
		cout << "TauCalculator constructor called.\n";
}

TauCalculator::TauCalculator(const TauCalculator& tc){
	if (MoMMA::debug)
		cout << "TauCalculator copy constructor called.\n";
}

TauCalculator::~TauCalculator(){
	if (MoMMA::debug)
		cout << "TauCalculator destructor called.\n";
}

void TauCalculator::getNewTau(double& tau){
	cout << "Error in TauCalculator::getNewTau(): Cannot use base method, must overload. Exiting." << endl;
	exit(1);
}
