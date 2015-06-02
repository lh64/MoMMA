/*
 * commTracker.hh
 *
 *  Created on: Apr 28, 2010
 *      Author: Leonard Harris
 */

#ifndef COMMTRACKER_HH_
#define COMMTRACKER_HH_

#include "../../MoMMA.hh"
#include "stringData.hh"

using namespace std;

namespace MoMMA{

	class CommTracker : public Tracker{
	public:
		int maxIterations;
		CommTracker();
		CommTracker(StringPtrData* d, int maxIterations);
		virtual ~CommTracker();
		void addData(StringPtrData* d, int maxIterations);
		virtual bool exceeded();
		virtual void reset();

	protected:
		int iteration;
		int pos;
	};
}

#endif /* COMMTRACKER_HH_ */
