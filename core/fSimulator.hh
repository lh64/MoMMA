/*
 * fSimulator.hh
 *
 *  Created on: Oct 27, 2009
 *      Author: Leonard Harris
 */

#ifndef FSIMULATOR_HH_
#define FSIMULATOR_HH_

#include "../MoMMA.hh"

using namespace std;

namespace MoMMA{

	class fSimulator{
	public:
		fSimulator();
		virtual ~fSimulator();
		virtual void initialize();
		virtual double run(double t);
		virtual double run(double tStart, double tEnd);
		virtual void rollBack(double amount);
		virtual bool checkForEquilibrium();
	};
}

#endif /* FSIMULATOR_HH_ */
