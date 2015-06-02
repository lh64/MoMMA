/*
 * intPtrTracker.cpp
 *
 *  Created on: Apr 18, 2010
 *      Author: Leonard Harris
 */

#include "intPtrTracker.hh"

using namespace std;
using namespace MoMMA;

IntPtrTracker::IntPtrTracker(){
	if (MoMMA::debug)
		cout << "IntPtrTracker constructor called." << endl;
	this->d = NULL;
	this->epsilon = NAN;
	this->initial = this->current = NULL;
}

IntPtrTracker::IntPtrTracker(IntPtrData* d, double epsilon){
	if (MoMMA::debug)
		cout << "IntPtrTracker constructor called." << endl;
	this->addData(d,epsilon);
}

IntPtrTracker::~IntPtrTracker(){
	if (MoMMA::debug)
		cout << "IntPtrTracker destructor called." << endl;
}

void IntPtrTracker::addData(IntPtrData* d, double epsilon){
	this->d = d;
	this->epsilon = epsilon;
	this->initial = this->current = *d->getIntPtr();
}

bool IntPtrTracker::exceeded(){
	this->current = *static_cast<IntPtrData*>(this->d)->getIntPtr();
	//
	cout << this->getName() << ": current = " << this->current << ", initial = " << this->initial
		 << ", delta = " << fabs(((double)this->current - (double)this->initial) / (double)this->initial) << endl;
	//
	if ( (double)fabs(this->current-this->initial) >= (this->epsilon*(double)this->initial + MoMMA::TOL) ){
		return true;
	}
	return false;
}

bool IntPtrTracker::changed(){
	this->current = *static_cast<IntPtrData*>(this->d)->getIntPtr();
	//
	cout << this->getName() << ": current = " << this->current << ", initial = " << this->initial
		 << ", delta = " << fabs(((double)this->current-(double)this->initial) / (double)this->initial) << endl;
	//
	if ( (double)fabs(this->current-this->initial) >= MoMMA::TOL ){
		return true;
	}
	return false;
}

void IntPtrTracker::reset(){
	this->current = *static_cast<IntPtrData*>(this->d)->getIntPtr();
	double delta = fabs(((double)this->current-(double)this->initial) / (double)this->initial);
	if (delta > MoMMA::TOL){
		cout << "\t***RESETTING " << this->d->getName() << " (" << delta << ")***" << endl;
		this->initial = this->current;
	}
}

bool IntPtrTracker::synchronized(){
	double curr = *static_cast<IntPtrData*>(this->d)->getIntPtr();
	if ( (double)fabs(curr-this->current) > MoMMA::TOL ){  // curr != this->current
		this->current = curr;
		this->initial = this->current;
		return false;
	}
	return true;
}
