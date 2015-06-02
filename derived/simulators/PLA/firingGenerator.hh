/*
 * firingGenerator.hh
 *
 *  Created on: Feb 12, 2011
 *      Author: Leonard Harris
 */

#ifndef FIRINGGENERATOR_HH_
#define FIRINGGENERATOR_HH_

#include "../../../MoMMA.hh"
#include "../../../model_spec/reaction.hh"

using namespace std;

namespace MoMMA{

	class FiringGenerator{
	public:
		FiringGenerator();
		FiringGenerator(const FiringGenerator& fg);
		virtual ~FiringGenerator();
		virtual void fireRxns(vector<double>& k, vector<int>& classif, double tau);
		virtual FiringGenerator* clone() const{ return new FiringGenerator(*this); }
	};
}

#endif /* FIRINGGENERATOR_HH_ */
