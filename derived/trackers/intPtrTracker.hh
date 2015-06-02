/*
 * intPtrTracker.hh
 *
 *  Created on: Apr 18, 2010
 *      Author: Leonard Harris
 */

#ifndef INTPTRTRACKER_HH_
#define INTPTRTRACKER_HH_

#include "../../MoMMA.hh"
#include "../../borrowed/primitiveData.hh"

using namespace std;

namespace MoMMA{

	class IntPtrTracker : public Tracker{
	public:
		double epsilon;
		IntPtrTracker();
		IntPtrTracker(IntPtrData* d, double epsilon);
		~IntPtrTracker();
		void addData(IntPtrData* d, double epsilon);
		virtual bool exceeded();
		virtual bool changed();
		virtual void reset();
		virtual bool synchronized();

		int initial;
		int current;
	protected:
//		int initial;
//		int current;
	};
}

#endif /* INTPTRTRACKER_HH_ */
