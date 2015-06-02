/*
 * commSimulator.hh
 *
 *  Created on: Feb 12, 2010
 *      Author: Leonard Harris
 */

#ifndef COMMSIMULATOR_HH_
#define COMMSIMULATOR_HH_

#include <string>
#include "../../MoMMA.hh"

using namespace std;

namespace MoMMA{

	class CommSimulator : public fSimulator{
	public:

		string module_name;
		string sim_data;

		CommSimulator(string module_name);
		~CommSimulator();

		virtual double run(double t);
		virtual void backtrack(double amount);
	};
}

#endif /* COMMSIMULATOR_HH_ */
