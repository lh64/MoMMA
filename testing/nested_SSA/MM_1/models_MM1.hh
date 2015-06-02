/*
 * models.hh
 *
 *  Created on: Nov 24, 2010
 *      Author: Leonard Harris
 */

#ifndef MODELS_MM1_HH_
#define MODELS_MM1_HH_

#include "../../../MoMMA.hh"
#include "../../../model_spec/simpleSpecies.hh"
#include "../../../model_spec/reaction.hh"
#include "../../../model_spec/rateExpression.hh"
#include "../../../model_spec/reactions/bioNetGenRxn.hh"

using namespace std;

namespace MoMMA{

	class SlowModel_MM1{
	public:
		vector<SimpleSpecies*> species;
		vector<Reaction*> reaction;
		RateElementary* re;
		SlowModel_MM1(double E_tot, double V, bool printToScreen);
		~SlowModel_MM1();
	};

	class FastModel_MM1{
	public:
		vector<SimpleSpecies*> species;
		vector<Reaction*> reaction;
		RateElementary* re_f;
		RateElementary* re_r;
		FastModel_MM1(double E_tot, double S_tot, double V, bool printToScreen);
		~FastModel_MM1();
	};

	class FullModel_MM1{
	public:
		vector<SimpleSpecies*> species;
		vector<Reaction*> reaction;
		RateElementary* re_f;
		RateElementary* re_r;
		RateElementary* re_cat;
		FullModel_MM1(double E_tot, double S_tot, double V, bool printToScreen);
		~FullModel_MM1();
	};
}

#endif /* MODELS_MM1_HH_ */
