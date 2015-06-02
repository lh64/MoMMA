/*
 * doublePtrVectorTracker.hh
 *
 *  Created on: Dec 8, 2010
 *      Author: Leonard Harris
 */

#ifndef DOUBLEPTRVECTORTRACKER_HH_
#define DOUBLEPTRVECTORTRACKER_HH_

#include "../../MoMMA.hh"
#include "../../borrowed/primitiveData.hh"

using namespace std;

namespace MoMMA{

	class DoublePtrVectorTracker : public Tracker{
	public:
		vector<double> epsilon;
		int numElements;
		DoublePtrVectorTracker();
		DoublePtrVectorTracker(DoublePtrVectorData* d, vector<double> epsilon);
		~DoublePtrVectorTracker();
		void addData(DoublePtrVectorData* d, vector<double> epsilon);
		virtual bool exceeded();
		virtual bool changed();
		virtual void reset();
		virtual bool synchronized();

		vector<double> initial;
		vector<double> current;
	protected:
//		double initial;
//		double current;
	};
}

#endif /* DOUBLEPTRVECTORTRACKER_HH_ */
