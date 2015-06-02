/*
 * serialConductorType1.hh
 *
 *  Created on: Jul 12, 2010
 *      Author: Leonard Harris
 */

#ifndef SERIALCONDUCTORTYPE1_HH_
#define SERIALCONDUCTORTYPE1_HH_

// Synchronize all modules before passing data for immediate action.
// Backtracking can be done directly, no need to reset trackers.

#include <fstream>
#include "../../MoMMA.hh"

using namespace std;

namespace MoMMA{

	class SerialConductorType1 : public Conductor{
	public:
		vector< vector<Module*> >* level;
		SerialConductorType1();
		SerialConductorType1(vector< vector<Module*> >& level, double samplingFraction, double tauMultiplier);
		virtual ~SerialConductorType1(){}
		void initialize();
		virtual void go(double startTime, double endTime);
		virtual void go(double startTime, double endTime, double startTau);
		//
		void setOutputInterval(double outInterval){ this->output_interval = outInterval; }
	protected:
		double samplingFraction;// Sampling interval (> 0 && <= 1)
		double tauMultiplier; 	// For increasing tau (>= 1)
		int startLevel;
		unsigned int nModules;
		//
		double output_interval;
	};

}

#endif /* SERIALCONDUCTORTYPE1_HH_ */
