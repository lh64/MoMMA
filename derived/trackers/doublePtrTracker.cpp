/*
 * doublePtrTracker.cpp
 *
 *  Created on: Apr 18, 2010
 *      Author: Leonard Harris
 */

#include "doublePtrTracker.hh"

using namespace std;
using namespace MoMMA;

DoublePtrTracker::DoublePtrTracker(){
	if (MoMMA::debug)
		cout << "DoublePtrTracker constructor called." << endl;
	this->d = NULL;
	this->epsilon = NAN;
	this->initial = this->current = NAN;
}

DoublePtrTracker::DoublePtrTracker(DoublePtrData* d, double epsilon){
	if (MoMMA::debug)
		cout << "DoublePtrTracker constructor called." << endl;
	this->addData(d,epsilon);
}

DoublePtrTracker::~DoublePtrTracker(){
	if (MoMMA::debug)
		cout << "DoublePtrTracker destructor called." << endl;
}

void DoublePtrTracker::addData(DoublePtrData* d, double epsilon){
	this->d = d;
	this->epsilon = epsilon;
	this->initial = this->current = *d->getDoublePtr();
}

bool DoublePtrTracker::exceeded(){
	this->current = *static_cast<DoublePtrData*>(this->d)->getDoublePtr();
	//
	cout << this->getName() << ": current = " << this->current << ", initial = " << this->initial
		 << ", delta = " << fabs((this->current-this->initial) / this->initial) << endl;
	//
	if ( fabs(this->current-this->initial) >= (this->epsilon*this->initial + MoMMA::TOL) ){
		return true;
	}
	return false;
}

bool DoublePtrTracker::changed(){
	this->current = *static_cast<DoublePtrData*>(this->d)->getDoublePtr();
	//
	cout << this->getName() << ": current = " << this->current << ", initial = " << this->initial
		 << ", delta = " << fabs((this->current-this->initial) / this->initial) << endl;
	//
	if ( fabs(this->current-this->initial) >= MoMMA::TOL ){
		return true;
	}
	return false;
}

void DoublePtrTracker::reset(){
	this->current = *static_cast<DoublePtrData*>(this->d)->getDoublePtr();
	//
//	cout << "initial = " << this->initial << endl;
//	cout << "current = " << this->current << endl;
	//
	double delta = fabs((this->current-this->initial)/this->initial);
	if (delta > MoMMA::TOL){
		cout << "\t***RESETTING " << this->d->getName() << " (" << delta << ")***" << endl;
		this->initial = this->current;
	}
}

bool DoublePtrTracker::synchronized(){
	double curr = *static_cast<DoublePtrData*>(this->d)->getDoublePtr();
	if ( fabs(curr-this->current) > MoMMA::TOL ){  // curr != this->current
		this->current = curr;
		this->initial = this->current;
		return false;
	}
	return true;
}
