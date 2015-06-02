/*
 * conductor.cpp
 *
 *  Created on: Jul 12, 2010
 *      Author: Leonard Harris
 */

#include <iostream>
#include "conductor.hh"

using namespace std;
using namespace MoMMA;

Conductor::Conductor(){
	if (MoMMA::debug)
		cout << "Conductor constructor called." << endl;
	this->globalTime = 0.0;
}

Conductor::~Conductor(){
	if (MoMMA::debug)
		cout << "Conductor destructor called." << endl;
}

void Conductor::go(double startTime, double endTime){
	cout << "Error in Conductor::go(): Must overload the base method. Exiting." << endl;
	exit(1);
}


