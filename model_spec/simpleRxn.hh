/*
 * simpleRxn.hh
 *
 *  Created on: Oct 21, 2009
 *      Author: Len
 */

#ifndef SIMPLERXN_HH_
#define SIMPLERXN_HH_

#include <string>
#include <vector>
#include "../MoMMA.hh"
#include "simpleSpecies.hh"

using namespace std;

namespace MoMMA{

	class SimpleRxn{
	public:
		string name;
		int nReactants;
		SimpleSpecies **reactants;
		int nProducts;
		SimpleSpecies **products;
		int *stoichiometry;
		int type;
		double c; // rate constant (only considering elementary reaction types)
		double rate;

		SimpleRxn(){};
		SimpleRxn(double c, int nReactants, SimpleSpecies **reactants, int nProducts,
					SimpleSpecies **products, int *stoichiometry);
		SimpleRxn(double c, vector<SimpleSpecies*> reactants, vector<SimpleSpecies*> products, vector<int> stoichiometry);
		~SimpleRxn();

		void calculateRate();
		static double calculateRate(double c, int type, SimpleSpecies **reactants);
	protected:
		void construct(double c, int nReactants, SimpleSpecies** reactants, int nProducts,
							SimpleSpecies** products, int* stoichiometry);

	};
}

#endif /* SIMPLERXN_HH_ */
