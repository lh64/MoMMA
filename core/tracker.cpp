/*
 * tracker.cpp
 *
 *  Created on: Apr 18, 2010
 *      Author: Leonard Harris
 */

#include <iostream>
#include "tracker.hh"

using namespace std;
using namespace MoMMA;

Tracker::Tracker(){
	if (MoMMA::debug)
		cout << "Tracker constructor called." << endl;
}

Tracker::Tracker(Data* d){
	if (MoMMA::debug)
		cout << "Tracker constructor called." << endl;
	this->d = d;
}

Tracker::~Tracker(){
	if (MoMMA::debug)
		cout << "Tracker destructor called." << endl;
}

bool Tracker::exceeded(){
	cout << "Error in Tracker::exceeded(): Cannot use base method, must overload in a derived class. Exiting." << endl;
	exit(1);
	return false;
}

bool Tracker::changed(){
	cout << "Error in Tracker::changed(): Cannot use base method, must overload in a derived class. Exiting." << endl;
	exit(1);
	return false;
}

void Tracker::reset(){
	cout << "Error in Tracker::reset(): Cannot use base method, must overload in a derived class. Exiting." << endl;
	exit(1);
}


bool Tracker::synchronized(){
	cout << "Error in Tracker::synchronized(): Cannot use base method, must overload in a derived class. Exiting." << endl;
	exit(1);
}
