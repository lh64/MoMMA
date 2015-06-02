/*
 * @file worldSimulator.hh
 *
 *	Wrapper class for the World Gillespie simulator
 *
 *	@author Leonard Harris
 *
 *	@date February 3, 2010, last edited: February 3, 2010
 */

#ifndef WORLDSIMULATOR_HH_
#define WORLDSIMULATOR_HH_

#include "../../MoMMA.hh"
#include "../../derived/simulators/simpleGillespie.hh"

using namespace std;

namespace MoMMA{

	class WorldSimulator : public fSimulator {

	public:
		int ligLevel;
		WorldSimulator(SimpleGillespie* sim);
		~WorldSimulator(){}
		void seed(unsigned long seedInt) { this->sim->seed(seedInt); }
		void setDebug(bool debug) { this->sim->setDebug(debug); }
		virtual double run(double t);
//		virtual double run(int n);
		void getLigandLevel();

	private:
		SimpleGillespie* sim;
	};
}

#endif /* WORLDSIMULATOR_HH_ */
