/*
 * models.hh
 *
 *  Created on: Nov 15, 2010
 *      Author: Leonard Harris
 */

#ifndef MODELS_HH_
#define MODELS_HH_

#include "../../../MoMMA.hh"
#include "../../../model_spec/simpleSpecies.hh"
#include "../../../model_spec/reaction.hh"
#include "../../../model_spec/rateExpression.hh"
#include "../../../model_spec/reactions/bioNetGenRxn.hh"

using namespace std;

namespace MoMMA{

	class SlowModel {
	public:
		vector<SimpleSpecies*> species;
		vector<Reaction*> reaction;
		SlowModel(bool printToScreen);
		~SlowModel();
	};

	class MediumModel {
	public:
		vector<SimpleSpecies*> species;
		vector<Reaction*> reaction;
		MediumModel(bool printToScreen);
		~MediumModel();
	};

	class FastModel {
	public:
		vector<SimpleSpecies*> species;
		vector<Reaction*> reaction;
		FastModel(bool printToScreen);
		~FastModel();
	};
}

#endif /* MODELS_HH_ */
