/*
 * conductor.hh
 *
 *  Created on: Jul 12, 2010
 *      Author: Leonard Harris
 */

#ifndef CONDUCTOR_HH_
#define CONDUCTOR_HH_

#include <string>
#include "../MoMMA.hh"

using namespace std;

namespace MoMMA{

	class Conductor{
	public:
		double globalTime;
		Conductor();
		virtual ~Conductor();
		void setGlobalTime(double inTime){ this->globalTime = inTime; }
		virtual void go(double startTime, double endTime);
	};

}

#endif /* CONDUCTOR_HH_ */
