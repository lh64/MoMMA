/*
 * fullModel.hh
 *
 *  Created on: Oct 11, 2010
 *      Author: Leonard Harris
 */

#ifndef FULLMODEL_HH_
#define FULLMODEL_HH_

#include <vector>
#include "../../MoMMA.hh"
#include "../../model_spec/simpleSpecies.hh"
#include "../../model_spec/reaction.hh"
#include "../../model_spec/rateExpression.hh"
#include "../../model_spec/reactions/bioNetGenRxn.hh"

using namespace std;

namespace MoMMA{

	class FullModel{

	public:
		vector<SimpleSpecies*> species;
		vector<Reaction*> reaction;

		FullModel(double volume);
		~FullModel();
	};
}

#endif /* FULLMODEL_HH_ */
