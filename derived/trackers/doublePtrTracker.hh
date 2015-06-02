/*
 * doublePtrTracker.hh
 *
 *  Created on: Apr 18, 2010
 *      Author: Leonard Harris
 */

#ifndef DOUBLEPTRTRACKER_HH_
#define DOUBLEPTRTRACKER_HH_

#include "../../MoMMA.hh"
#include "../../borrowed/primitiveData.hh"

using namespace std;

namespace MoMMA{

	class DoublePtrTracker : public Tracker{
	public:
		double epsilon;
		DoublePtrTracker();
		DoublePtrTracker(DoublePtrData* d, double epsilon);
		~DoublePtrTracker();
		void addData(DoublePtrData* d, double epsilon);
		virtual bool exceeded();
		virtual bool changed();
		virtual void reset();
		virtual bool synchronized();

		double initial;
		double current;
	protected:
//		double initial;
//		double current;
	};
}

#endif /* DOUBLEPTRTRACKER_HH_ */
