/*
 * monitor.hh
 *
 *  Created on: Mar 30, 2010
 *      Author: Leonard Harris
 */

#ifndef MONITOR_HH_
#define MONITOR_HH_

#include "../MoMMA.hh"

using namespace std;

namespace MoMMA{
	class Tracker;
	class Monitor{
	public:
		vector<Tracker*> trackers;

		Monitor();
		Monitor(vector<Tracker*> tr);
		Monitor(vector<Tracker*> tr, vector<double> ts);
		Monitor(vector<Tracker*> tr, vector<double> ts, vector<double> init);
		~Monitor();

		void addTracker(Tracker* tr){ this->addTracker(tr,INFINITY,0.0); }
		void addTracker(Tracker* tr, double ts){ this->addTracker(tr,ts,0.0); }
		void addTracker(Tracker* tr, double ts, double init){
			this->trackers.push_back(tr);
			this->timescales.push_back(ts);
			this->initialTimes.push_back(init);
		}

		void addTrackers(vector<Tracker*> tr);
		void addTrackers(vector<Tracker*> tr, vector<double> ts);
		void addTrackers(vector<Tracker*> tr, vector<double> ts, vector<double> init);

		bool anyExceeded();
		vector<Tracker*> getExceeded();
		vector<Tracker*> getChanged();
		vector<Tracker*> getAll(){ return this->trackers; }
		Tracker* getTracker(string name);
		void resetExceeded(double currentTime);
		void resetAll(double currentTime);
		void synchronize(double currentTime);

		double getTimescale();

	protected:
//		vector<Tracker*> trackers;
		vector<double> initialTimes;
		vector<double> timescales;
	};
}


#endif /* MONITOR_HH_ */
