/*
 * butcherTableau.hh
 *
 *  Created on: Mar 23, 2011
 *      Author: Leonard Harris
 */

#ifndef BUTCHERTABLEAU_HH_
#define BUTCHERTABLEAU_HH_

#include "../../../../../MoMMA.hh"

using namespace std;

namespace MoMMA{

	class ButcherTableau{
	public:
		vector<vector<double> > alpha;
		vector<double> beta;
		ButcherTableau();
		ButcherTableau(vector<vector<double> > alpha, vector<double> beta);
		unsigned int size(){ return this->s; }
		bool isExplicit(){ return this->explicit_; }
	protected:
		unsigned int s;
		vector<double> gamma;
		bool explicit_;
	};
}

#endif /* BUTCHERTABLEAU_HH_ */
