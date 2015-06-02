/*
 * worldTracker.cpp
 *
 *  Created on: Apr 26, 2010
 *      Author: Leonard Harris
 */

#include "worldTracker.hh"
#include "../../borrowed/primitiveData.hh"

using namespace std;
using namespace MoMMA;

WorldTracker::WorldTracker(){
	if (MoMMA::debug) cout << "WorldTracker constructor called." << endl;
	this->d = NULL;
}

WorldTracker::WorldTracker(Data* d){
	if (MoMMA::debug) cout << "WorldTracker constructor called." << endl;
	this->addData(d);
}

WorldTracker::~WorldTracker(){
	if (MoMMA::debug) cout << "WorldTracker destructor called." << endl;
}

void WorldTracker::addData(Data* d){
	// Error check
	if (d->getType().compare("IntPtrType") == 0){
		this->d = d;
		this->initial = *static_cast<IntPtrData*>(this->d)->getIntPtr();
	}
	else{
		cout << "Oops, data element passed to WorldTracker not IntPtrType. Exiting." << endl;
		exit(1);
	}
}

bool WorldTracker::exceeded(){
	this->current = *static_cast<IntPtrData*>(this->d)->getIntPtr();
	if (this->current != this->initial){
		return true;
	}
	return false;
}

void WorldTracker::reset(){
	cout << "\t***RESETTING " << this->d->getName() << " (" << this->initial << "->" << this->current << ")***" << endl;
	this->initial = this->current;
}
