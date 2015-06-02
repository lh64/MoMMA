/*
 * tracker.hh
 *
 *  Created on: Apr 18, 2010
 *      Author: Leonard Harris
 */

#ifndef TRACKER_HH_
#define TRACKER_HH_

#include "../MoMMA.hh"

using namespace std;

namespace MoMMA{

	class Tracker{
	public:
		Tracker();
		Tracker(Data* d);
		virtual ~Tracker();
		Data* getData(){ return this->d; }
		string getName(){ return this->d->getName(); }
		virtual bool exceeded();
		virtual bool changed();
		virtual void reset();
		virtual bool synchronized(); // return true if synchronized, false if not

	protected:
		Data* d;
	};
}

#endif /* TRACKER_HH_ */
