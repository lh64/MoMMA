/*
 * observable.cpp
 *
 *  Created on: Jul 18, 2011
 *      Author: Leonard Harris
 */

#include "observable.hh"

using namespace std;
using namespace MoMMA;

Observable::Observable(string name, vector<SimpleSpecies*> species, vector<double> mult_factor) : name(name){
	if (MoMMA::debug)
		cout << "Observable constructor called." << endl;
	// Error check
	if (species.size() != mult_factor.size()){
		cout << "Error in Observable constructor: 'species' and 'mult_factor' vectors must be equal size. Exiting." << endl;
		exit(1);
	}
	//
	for (unsigned int i=0;i < species.size();i++){
		this->sp.push_back( pair<SimpleSpecies*,double>(species[i],mult_factor[i]) );
	}
}

Observable::~Observable(){
	if (MoMMA::debug)
		cout << "Observable destructor called." << endl;
}

double Observable::getValue(){
	double val = 0.0;
	SimpleSpecies* s;
	double m;
	for (unsigned int i=0;i < this->sp.size();i++){
		s = this->sp[i].first;
		m = this->sp[i].second;
		val += m*s->population;
	}
	return val;
}
