/*
 * observable.hh
 *
 *  Created on: Jul 18, 2011
 *      Author: Leonard Harris
 */

#ifndef OBSERVABLE_HH_
#define OBSERVABLE_HH_

#include <string>
#include "../MoMMA.hh"
#include "simpleSpecies.hh"

using namespace std;

namespace MoMMA{

	class Observable{
	public:
		vector<pair<SimpleSpecies*,double> > sp; // <species,mult_factor>
		Observable(string name, vector<SimpleSpecies*> species, vector<double> mult_factor);
		~Observable();
		string getName(){ return this->name; }
		double getValue();
	protected:
		string name;
//		vector<pair<SimpleSpecies*,double> > sp; // <species,mult_factor>
	};
}

#endif /* OBSERVABLE_HH_ */
