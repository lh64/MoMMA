/*
 * @file simpleGillespie.hh
 *
 *	A simple (unoptimized) Gillespie simulator
 *
 *	@author Leonard Harris
 *
 *	@date October 20, 2009, last edited: October 20, 2009
 */

#ifndef SIMPLEGILLESPIE_HH_
#define SIMPLEGILLESPIE_HH_

#include "../../MoMMA.hh"
#include "../../borrowed/util/util.hh"
#include "../../model_spec/simpleSpecies.hh"
#include "../../model_spec/simpleRxn.hh"

using namespace std;

namespace MoMMA{

	class SimpleGillespie : public fSimulator {

	public:
		/// Constructor
		SimpleGillespie(int nSpecies, SimpleSpecies **species, int nRxn,
				SimpleRxn **reaction, bool debug);

		/// Destructor
		~SimpleGillespie();

		void seed(unsigned long seedInt);

		void seed(long seedInt);

		void setDebug(bool debug) { this->debug = debug; }

		/**
		 * integrate the system for a given period of time t
		 * @param t time interval
		 */
		virtual double run(double t);

//		virtual double run(int n);

		double nextStep();

		double nextStep(double maxTau);

		int nSpecies;
		SimpleSpecies **species;
		int nRxns;
		SimpleRxn **reaction;
		bool debug;
	};
}

#endif /* SIMPLEGILLESPIE_HH_ */
