/*
 * tauCalculator.hh
 *
 *  Created on: Feb 7, 2011
 *      Author: Leonard Harris
 */

#ifndef TAUCALCULATOR_HH_
#define TAUCALCULATOR_HH_

#include "../../../MoMMA.hh"
#include "../../../model_spec/reaction.hh"

using namespace std;

namespace MoMMA{

	class TauCalculator{
	public:
		TauCalculator();
		TauCalculator(const TauCalculator& tc);
		virtual ~TauCalculator();
		virtual void getNewTau(double& tau);
		virtual TauCalculator* clone() const{ return new TauCalculator(*this); }
	};
}

#endif /* TAUCALCULATOR_HH_ */
