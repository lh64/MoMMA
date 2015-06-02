/*
 * module.hh
 *
 *  Created on: Feb 1, 2010
 *      Author: Leonard Harris
 */

#ifndef MODULE_HH_
#define MODULE_HH_

#include <string>
#include <fstream>
#include "../MoMMA.hh"

using namespace std;

namespace MoMMA{

	class fSimulator;
	class fCommunicator;
	class Monitor;
	class Tracker;
	class Translator;

	class Module{
	public:
		// Variables
		map<Module*,int> neighbors; // <neighbor,0=outgoing, 1=incoming, 2=both>
		fSimulator* sim;
		fCommunicator* comm;
		Monitor* monitor;

		// Constructors and destructor
		Module();
		//
		Module(int module_id);
		Module(string module_name);
		Module(fSimulator* sim);
		Module(bool equil);
		//
		Module(int module_id, string module_name);
		Module(int module_id, fSimulator* sim);
		Module(int module_id, bool equil);
		Module(string module_name, fSimulator* sim);
		Module(string module_name, bool equil);
		Module(fSimulator* sim, bool equil);
		//
		Module(int module_id, string module_name, fSimulator* sim);
		Module(int module_id, string module_name, bool equil);
		Module(int module_id, fSimulator* sim, bool equil);
		Module(string module_name, fSimulator* sim, bool equil);
		//
		Module(int module_id, string module_name, fSimulator* sim, bool equil);
		//
		~Module();

		// Utility Methods
		double getLocalTime(){ return this->local_time; }
		void setLocalTime(double t){ this->local_time = t; }
		double getTimescale(){ return this->timescale; }
		void setTimescale(double timescale){ this->timescale = timescale; }
		void updateTimescale();

		static void makeNeighbors(Module* m1, Module* m2, map<Tracker*,Translator*> m1_to_m2,
								  map<Tracker*,Translator*> m2_to_m1);
		static void addLink(Module* m1, Tracker* var, Module* m2, Translator* par);
		static void addLink(Module* m1, Tracker* var, double varTimescale, Module* m2, Translator* par);

		void addSimulator(fSimulator* sim){ this->sim = sim; }
		void addVariable(Tracker* tr, Module* dest);
		void addVariable(Tracker* tr, double timescale, Module* dest);
		void addParameter(Translator* t);

		string getName(){ return this->module_name; }
		int getId(){ return this->module_id; }

		bool isEquilibrated(){ return this->equilibrated; }
		void setEquilibrated(bool equil) { this->equilibrated = equil; }
		void disequilibrate(double currentTime);

		// Action methods
		double runSimulation(double totalTime, double sampleTime); //{ return this->runSimulation(0.0,totalTime,sampleTime); }
//		double runSimulation(double tStart, double tEnd, double sampleTime);
		void rollBack(double amount);
		void sendMessages(bool immediateAction, bool asPtrData, bool sendAll);
		void processInbox();
		void clearInbox();

		// Output
		void addOutputFile(string filePath){ this->output.open(filePath.c_str()); }
		void initializeOutput();
		void outputToFile();

	protected:
		static unsigned int ModuleCounter;
		int module_id;
		string module_name;
		double local_time;
		double timescale;
		bool equilibrated;
		void construct(int module_id, string module_name, fSimulator* sim, bool equil);
		//
		ofstream output;
	};
}

#endif /* MODULE_HH_ */
