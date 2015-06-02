/*
 * trackSimulator.hh
 *
 *  Created on: Apr 20, 2010
 *      Author: Leonard Harris
 */

#ifndef TRACKSIMULATOR_HH_
#define TRACKSIMULATOR_HH_

#include <string>
#include "../../MoMMA.hh"

using namespace std;

namespace MoMMA{

	class TrackSimulator : public fSimulator{
	public:
		double v, p;

		TrackSimulator(double v_init, double p_init);
		~TrackSimulator(){}

		double run(double t);
//		double run(int n);
	};
}

#endif /* TRACKSIMULATOR_HH_ */
