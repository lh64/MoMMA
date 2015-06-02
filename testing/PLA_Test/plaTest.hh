/*
 * plaTest.hh
 *
 *  Created on: Feb 4, 2011
 *      Author: Leonard Harris
 */

#ifndef PLATEST_HH_
#define PLATEST_HH_

#include "../../MoMMA.hh"
#include "../../derived/simulators/PLA.hh"
#include "../../derived/simulators/PLA/TC/test/tauCalcTest.hh"
#include "../../derived/simulators/PLA/fEuler/fEuler.hh"
#include "../../derived/simulators/PLA/midpoint/midpoint.hh"
#include "../../derived/simulators/PLA/eRungeKutta/eRungeKutta.hh"
#include "../../derived/simulators/PLA/misc/negPop_PL.hh"
#include "../../model_spec/reactions/bioNetGenRxn.hh"

using namespace std;

namespace MoMMA{

	class PLATest{
	public:
		PLATest();
		~PLATest(){}
	};

	class DecayDimer{
	public:
		DecayDimer();
		~DecayDimer();
		vector<RateExpression*> re;
		vector<Reaction*> rxn;
		vector<SimpleSpecies*> sp;
	};

	class CaOscillate{
	public:
		CaOscillate(double V);
		~CaOscillate();
		vector<RateExpression*> re;
		vector<Reaction*> rxn;
		vector<SimpleSpecies*> sp;
	};
}

#endif /* PLATEST_HH_ */
