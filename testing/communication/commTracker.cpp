/*
 * commTracker.cpp
 *
 *  Created on: Apr 28, 2010
 *      Author: Leonard Harris
 */

#include <iostream>
#include <math.h>
#include "commTracker.hh"

using namespace std;
using namespace MoMMA;

CommTracker::CommTracker(){
	if (MoMMA::debug) cout << "CommTracker constructor called." << endl;
	this->maxIterations = NULL;
	this->iteration = NULL;
	this->pos = NULL;
}

CommTracker::CommTracker(StringPtrData* d, int maxIterations){
	if (MoMMA::debug) cout << "CommTracker constructor called." << endl;
	this->addData(d,maxIterations);
}

CommTracker::~CommTracker(){
	if (MoMMA::debug) cout << "CommTracker destructor called." << endl;
}

void CommTracker::addData(StringPtrData* d, int maxIterations){
	this->d = d;
	this->maxIterations = maxIterations;
	this->iteration = 0;
	this->pos = -1;
}

bool CommTracker::exceeded(){
	string dataString = *static_cast<StringPtrData*>(this->d)->getStringPtr();

	int n;
	while ( (n = dataString.find("_",this->pos+1)) != -1 ){
		this->pos = n;
		this->iteration++;
	}

	if (this->iteration >= this->maxIterations){
		return true;
	}
	return false;
}

void CommTracker::reset(){
	cout << "\t***RESETTING " << this->d->getName() << " (iter=" << this->iteration << ")***" << endl;
	this->iteration = 0;
}
