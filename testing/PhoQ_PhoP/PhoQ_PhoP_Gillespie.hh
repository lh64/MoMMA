/*
 * PhoQ_PhoP_Gillespie.hh
 *
 *  Created on: Oct 15, 2010
 *      Author: Leonard Harris
 */

#ifndef PHOQ_PHOP_GILLESPIE_HH_
#define PHOQ_PHOP_GILLESPIE_HH_

#include "../../MoMMA.hh"
#include "../../derived/simulators/gillespieDM.hh"

using namespace std;

namespace MoMMA{

	class PhoQ_PhoP_Gillespie : public fSimulator {

	public:
		GillespieDM* gillespSim;

		double RR_init;		// parameter
		double RRp_init;	// parameter

		PhoQ_PhoP_Gillespie(GillespieDM* gillespSim);
		~PhoQ_PhoP_Gillespie(){}

		virtual void initialize();
		virtual double run(double t){ return this->run(0.0,t); }
		virtual double run(double tStart, double tEnd);
		virtual void rollBack(double amount);
	protected:
		vector<double> lastState;  // [0]: tStart, [1] tEnd, [2...]: species populations
	};
}

#endif /* PHOQ_PHOP_GILLESPIE_HH_ */
