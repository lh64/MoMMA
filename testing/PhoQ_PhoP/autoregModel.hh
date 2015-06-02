/*
 * autoregModel.hh
 *
 *  Created on: Aug 22, 2010
 *      Author: Leonard Harris
 */

#ifndef AUTOREGMODEL_HH_
#define AUTOREGMODEL_HH_

#include "../../MoMMA.hh"
#include "../../model_spec/simpleSpecies.hh"
#include "../../model_spec/reaction.hh"
#include "../../model_spec/rateExpression.hh"
#include "../../model_spec/reactions/bioNetGenRxn.hh"

using namespace std;

namespace MoMMA{

	class AutoregModel {

	public:
		vector<SimpleSpecies*> species;
		vector<Reaction*> reaction;

		AutoregModel(double volume);
		~AutoregModel();
	};
}

#endif /* AUTOREGMODEL_HH_ */
