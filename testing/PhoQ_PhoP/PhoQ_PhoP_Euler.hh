/*
 * PhoQ_PhoP_Euler.hh
 *
 *  Created on: Nov 4, 2010
 *      Author: Leonard Harris
 */

#ifndef PHOQ_PHOP_EULER_HH_
#define PHOQ_PHOP_EULER_HH_

#include "../../MoMMA.hh"
#include "../../derived/simulators/simpleEuler.hh"

using namespace std;

namespace MoMMA{

	class PhoQ_PhoP_Euler : public fSimulator {

	public:
		SimpleEuler* eulerSim;

		double RR_init;		// parameter
		double RRp_init;	// parameter

		PhoQ_PhoP_Euler(SimpleEuler* eulerSim);
		~PhoQ_PhoP_Euler(){}

		virtual void initialize();
		virtual double run(double t){ return this->run(0.0,t); }
		virtual double run(double tStart, double tEnd);
		virtual void backtrack(double amount);
	protected:
		vector<double> lastState;  // [0]: tStart, [1] tEnd, [2...]: species populations
	};
}

#endif /* PHOQ_PHOP_EULER_HH_ */
