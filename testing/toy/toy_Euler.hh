/*
 * toy_Euler.hh
 *
 *  Created on: Nov 6, 2010
 *      Author: Leonard Harris
 */

#ifndef TOY_EULER_HH_
#define TOY_EULER_HH_

#include "../../MoMMA.hh"
#include "../../derived/simulators/simpleEuler.hh"

using namespace std;

namespace MoMMA{

	class Toy_Euler : public fSimulator {

	public:
		SimpleEuler* eulerSim;

		double X_init;	// parameter

		Toy_Euler(SimpleEuler* eulerSim);
		~Toy_Euler(){}

		virtual void initialize();
		virtual double run(double t){ return this->run(0.0,t); }
		virtual double run(double tStart, double tEnd);
//		virtual void backtrack(double amount);
	protected:
//		vector<double> lastState;  // [0]: tStart, [1] tEnd, [2...]: species populations
	};
}

#endif /* TOY_EULER_HH_ */
