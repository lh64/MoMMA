/*
 * serialConductorType3.hh
 *
 *  Created on: Jul 12, 2010
 *      Author: Leonard Harris
 */

#ifndef SERIALCONDUCTORTYPE3_HH_
#define SERIALCONDUCTORTYPE3_HH_

// Pass data (pointer types) immediately after simulation and store in destination inboxes.
// Process inboxes after all modules are synchronized.
// Trackers must be reset after backtracking.

// Pass data (non-pointer types) immediately after simulation and store in destination inboxes.
// Process inboxes after all modules are synchronized. Inboxes must subsequently be cleared.
// After backtracking, a new message must be sent before trackers are reset.

#include <string>
#include "../../MoMMA.hh"

using namespace std;

namespace MoMMA{

	class SerialConductorType3 : public Conductor{
	public:
		vector< vector<Module*> >* level;
		SerialConductorType3();
		SerialConductorType3(vector< vector<Module*> >& level);
		virtual ~SerialConductorType3();
		virtual void go(double startTime, double endTime);
	};

}

#endif /* SERIALCONDUCTORTYPE3_HH_ */
