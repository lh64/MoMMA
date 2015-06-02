/*
 * serialConductorType2.hh
 *
 *  Created on: Jul 12, 2010
 *      Author: Leonard Harris
 */

#ifndef SERIALCONDUCTORTYPE2_HH_
#define SERIALCONDUCTORTYPE2_HH_

// Pass data immediately after simulation runs for immediate action.
// Backtracking is done internally by modules if destination time differs from local time.
// If local time of a module differs from global time, simulation run for (globalTime + tau - localTime).

#include "../../MoMMA.hh"

using namespace std;

namespace MoMMA{

	class SerialConductorType2 : public Conductor{
	public:
		vector< vector<Module*> >* level;
		double sFactor; // Sampling interval (0 < sFactor <= 1)
		double tFactor; // For increasing tau
		SerialConductorType2();
		SerialConductorType2(vector< vector<Module*> >& level, double sFactor, double tFactor);
		virtual ~SerialConductorType2(){}
		virtual void go(double startTime, double endTime);
	};

}

#endif /* SERIALCONDUCTORTYPE2_HH_ */
