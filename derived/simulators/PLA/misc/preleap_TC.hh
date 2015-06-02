/*
 * preleap_TC.hh
 *
 *  Created on: Feb 7, 2011
 *      Author: Leonard Harris
 */

#ifndef PRELEAP_TC_HH_
#define PRELEAP_TC_HH_

#include "../tauCalculator.hh"

using namespace std;

namespace MoMMA{

	class Preleap_TC : public TauCalculator{
	public:
//		Preleap_TC(){}
		Preleap_TC(double eps){
			if (MoMMA::debug)
				cout << "Preleap_TC constructor called." << endl;
			this->eps = eps;
		}
		Preleap_TC(const Preleap_TC& tc) : TauCalculator(tc){
			if (MoMMA::debug)
				cout << "Preleap_TC copy constructor called." << endl;
			this->eps = tc.eps;
		}
		~Preleap_TC(){}
		virtual TauCalculator* clone() const{ return new Preleap_TC(*this); }
	protected:
		double eps;
	};
}

#endif /* PRELEAP_TC_HH_ */
