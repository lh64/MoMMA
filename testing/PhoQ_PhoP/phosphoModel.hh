/*
 * phosphoModel.hh
 *
 *  Created on: Aug 22, 2010
 *      Author: Leonard Harris
 */

#include <vector>
#include "../../MoMMA.hh"
#include "../../model_spec/simpleSpecies.hh"
#include "../../model_spec/reaction.hh"
#include "../../model_spec/rateExpression.hh"
#include "../../model_spec/reactions/bioNetGenRxn.hh"

#ifndef PHOSPHOMODEL_HH_
#define PHOSPHOMODEL_HH_

using namespace std;

namespace MoMMA{

	class PhosphoModel {

	public:
		vector<SimpleSpecies*> species;
		vector<Reaction*> reaction;

		PhosphoModel(double volume);
		~PhosphoModel();
	};
}

#endif /* PHOSPHOMODEL_HH_ */
