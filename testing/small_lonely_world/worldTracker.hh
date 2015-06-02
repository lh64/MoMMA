/*
 * worldTracker.hh
 *
 *  Created on: Apr 26, 2010
 *      Author: Leonard Harris
 */

#ifndef WORLDTRACKER_HH_
#define WORLDTRACKER_HH_

#include "../../MoMMA.hh"

using namespace std;

namespace MoMMA{

	class WorldTracker : public Tracker{
	public:
		WorldTracker();
		WorldTracker(Data* d);
		~WorldTracker();
		void addData(Data* d);
		virtual bool exceeded();
		virtual void reset();

	protected:
		int initial;
		int current;
	};
}

#endif /* WORLDTRACKER_HH_ */
