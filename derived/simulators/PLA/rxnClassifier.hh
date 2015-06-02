/*
 * rxnClassifier.hh
 *
 *  Created on: Feb 13, 2011
 *      Author: Leonard Harris
 */

#ifndef RXNCLASSIFIER_HH_
#define RXNCLASSIFIER_HH_

#include "../../../MoMMA.hh"
#include "../../../model_spec/reaction.hh"

using namespace std;

namespace MoMMA{

	class RxnClassifier{
	public:
		enum{EXACT_STOCHASTIC,POISSON,LANGEVIN,DETERMINISTIC};
		RxnClassifier();
		RxnClassifier(const RxnClassifier& rc);
		virtual ~RxnClassifier();
		virtual void classifyRxns(vector<int>& classif, double tau, bool initial);
		virtual RxnClassifier* clone() const{ return new RxnClassifier(*this); }
	};
}

#endif /* RXNCLASSIFIER_HH_ */
