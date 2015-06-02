/*
 * nested_gillespie.hh
 *
 *  Created on: Nov 15, 2010
 *      Author: Leonard Harris
 */

#ifndef NESTED_GILLESPIE_HH_
#define NESTED_GILLESPIE_HH_

#include "../../MoMMA.hh"
#include "../../derived/simulators/gillespieDM.hh"

using namespace std;

namespace MoMMA{

	class Nested_Gillespie : public fSimulator{
	public:
		GillespieDM* gillespSim;
		bool fastest;
		map<unsigned int,double> X_init;    // parameters
		vector<vector<double> > timecourse; // variables
		Nested_Gillespie(GillespieDM* gillespSim, vector<unsigned int> speciesIndex, bool fastest);
		~Nested_Gillespie(){}
		virtual void initialize();
		virtual double run(double t){ return this->run(0.0,t); }
		virtual double run(double tStart, double tEnd);
//		virtual void backtrack(double amount);
	protected:
//		vector<double> lastState;  // [0]: tStart, [1] tEnd, [2...]: species populations
	};
}

#endif /* NESTED_GILLESPIE_HH_ */
