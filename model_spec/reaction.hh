/*
 * reaction.hh
 *
 *  Created on: Aug 22, 2010
 *      Author: Leonard Harris
 */

#ifndef REACTION_HH_
#define REACTION_HH_

#include <string>
#include "../MoMMA.hh"
#include "simpleSpecies.hh"
#include "rateExpression.hh"

using namespace std;

namespace MoMMA{

	class Reaction{
	public:
		string type;
		map<SimpleSpecies*,int> stoichSpecies;
		vector<SimpleSpecies*> rateSpecies;
		RateExpression* re;
		Reaction();
		Reaction(map<SimpleSpecies*,int> stoichSpecies, vector<SimpleSpecies*> rateSpecies, RateExpression* re);
/*		Reaction(vector<pair<SimpleSpecies*,int> > stoichSpecies, vector<SimpleSpecies*> rateSpecies, RateExpression* re);
		Reaction(vector<SimpleSpecies*> stoichSpecies, vector<int> stoich, vector<SimpleSpecies*> rateSpecies, RateExpression* re);
		Reaction(SimpleSpecies* stoichSpecies, int stoich, vector<SimpleSpecies*> rateSpecies, RateExpression* re);
		Reaction(vector<SimpleSpecies*> stoichSpecies, vector<int> stoich, SimpleSpecies* rateSpecies, RateExpression* re);
		Reaction(SimpleSpecies* stoichSpecies, int stoich, SimpleSpecies* rateSpecies, RateExpression* re);
		// Old constructors
		Reaction(vector<SimpleSpecies*> r, vector<int> rS, vector<SimpleSpecies*> p, vector<int> pS, RateExpression* re);
		Reaction(SimpleSpecies* r, int rS, vector<SimpleSpecies*> p, vector<int> pS, RateExpression* re);
		Reaction(vector<SimpleSpecies*> r, vector<int> rS, SimpleSpecies* p, int pS, RateExpression* re);
		Reaction(SimpleSpecies* r, int rS, SimpleSpecies* p, int pS, RateExpression* re);*/
		virtual ~Reaction();
		double getRate();
		double get_dRate_dX(int which);
		void fire(double K);
		string toString(){ return string_ID; }
	protected:
		string string_ID;
		static string getStringID(vector<SimpleSpecies*> stoichSpecies, vector<int> stoich, string type_string);
		static string getStringID(vector<pair<SimpleSpecies*,int> > stoichSpecies, string type_string);
		static string getStringID(map<SimpleSpecies*,int> stoichSpecies, string type_string);
		// Old type_string getter
		static string getStringID(vector<SimpleSpecies*> r, vector<int> rS, vector<SimpleSpecies*> p, vector<int> pS,
								  string type_string);
	};
}

#endif /* REACTION_HH_ */
