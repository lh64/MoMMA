/*
 * doublePtrVectorTracker.cpp
 *
 *  Created on: Dec 8, 2010
 *      Author: Leonard Harris
 */

#include "doublePtrVectorTracker.hh"

using namespace std;
using namespace MoMMA;

DoublePtrVectorTracker::DoublePtrVectorTracker(){
	if (MoMMA::debug)
		cout << "DoublePtrVectorTracker constructor called." << endl;
	this->d = NULL;
}

DoublePtrVectorTracker::DoublePtrVectorTracker(DoublePtrVectorData* d, vector<double> epsilon){
	if (MoMMA::debug)
		cout << "DoublePtrVectorTracker constructor called." << endl;
	this->addData(d,epsilon);
}

DoublePtrVectorTracker::~DoublePtrVectorTracker(){
	if (MoMMA::debug)
		cout << "DoublePtrVectorTracker destructor called." << endl;
}

void DoublePtrVectorTracker::addData(DoublePtrVectorData* d, vector<double> epsilon){
	// Error check
	if (d->getNumElements() != (int)epsilon.size()){
		cout << "Error in DoublePtrVectorTracker::addData(): Number of pointers (" << d->getNumElements()
			 << ") not equal to number of epsilon values (" << epsilon.size() << "). Exiting." << endl;
		exit(1);
	}
	this->d = d;
	this->numElements = d->getNumElements();
	this->epsilon = epsilon;
	this->initial.resize(this->numElements); // Don't forget to resize the vectors
	this->current.resize(this->numElements);
	for (int i=0;i < this->numElements;i++){
		this->initial[i] = this->current[i] = *d->getDoublePtr(i);
	}
}

bool DoublePtrVectorTracker::exceeded(){

	for (int i=0;i < this->numElements;i++){
		this->current[i] = *static_cast<DoublePtrVectorData*>(this->d)->getDoublePtr(i);
		//
		cout << this->getName() << "[" << i << "]: current = " << this->current[i] << ", initial = " << this->initial[i]
			 << ", delta = " << fabs((this->current[i]-this->initial[i]) / this->initial[i]) << endl;
		//
		if ( fabs(this->current[i]-this->initial[i]) >= (this->epsilon[i]*this->initial[i] + MoMMA::TOL) ){
			return true;
		}
	}
	return false;
}

bool DoublePtrVectorTracker::changed(){

	for (int i=0;i < this->numElements;i++){
		this->current[i] = *static_cast<DoublePtrVectorData*>(this->d)->getDoublePtr(i);
		//
		cout << this->getName() << "[" << i << "]: current = " << this->current[i] << ", initial = " << this->initial[i]
			 << ", delta = " << fabs((this->current[i]-this->initial[i]) / this->initial[i]) << endl;
		//
		if ( fabs(this->current[i]-this->initial[i]) >= MoMMA::TOL ){
			return true;
		}
	}
	return false;
}

void DoublePtrVectorTracker::reset(){
	for (int i=0;i < this->numElements;i++){
		this->current[i] = *static_cast<DoublePtrVectorData*>(this->d)->getDoublePtr(i);
		double delta = fabs((this->current[i]-this->initial[i])/this->initial[i]);
		if (delta > MoMMA::TOL){
			cout << "\t***RESETTING " << this->d->getName() << "[" << i << "] (" << delta << ")***" << endl;
			this->initial[i] = this->current[i];
		}
	}
}

bool DoublePtrVectorTracker::synchronized(){
	bool synch = true;
	double curr;
	for (int i=0;i < this->numElements;i++){
		curr = *static_cast<DoublePtrVectorData*>(this->d)->getDoublePtr(i);
		if ( fabs(curr-this->current[i]) > MoMMA::TOL ){  // curr != this->current
			this->current[i] = curr;
			this->initial[i] = this->current[i];
			synch = false;
		}
	}
	return synch;

}
