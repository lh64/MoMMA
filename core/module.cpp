/*
 * module.cpp
 *
 *  Created on: Feb 1, 2010
 *      Author: Leonard Harris
 */

#include "module.hh"
#include "../borrowed/util/util.hh"

using namespace std;
using namespace MoMMA;

unsigned int Module::ModuleCounter = 1; // Module #0 is NULL

// Constructors
void Module::construct(int module_id, string module_name, fSimulator* sim, bool equil){
	if (MoMMA::debug) cout << "Module constructor called: Module #" << module_id << endl;
	Module::ModuleCounter++;
	this->setLocalTime(0.0);
	this->module_id = module_id;
	this->module_name = module_name;
	this->sim = sim;
	this->comm = new fCommunicator();
	this->monitor = new Monitor();
	this->timescale = INFINITY; // Default
	this->setEquilibrated(equil);
}

Module::Module(){
//	cout << "default" << endl;
	int module_id = Module::ModuleCounter;
	string module_name = "#" + Util::toString(module_id);
	fSimulator* sim = new fSimulator();
	bool equil = false; // Default
	this->construct(module_id,module_name,sim,equil);
}

Module::Module(int module_id){
//	cout << "id" << endl;
	string module_name = "#" + Util::toString(module_id);
	fSimulator* sim = new fSimulator();
	bool equil = false; // Default
	this->construct(module_id,module_name,sim,equil);
}

Module::Module(string module_name){
//	cout << "name" << endl;
	int module_id = Module::ModuleCounter;
	fSimulator* sim = new fSimulator();
	bool equil = false; // Default
	this->construct(module_id,module_name,sim,equil);
}

Module::Module(fSimulator* sim){
//	cout << "sim" << endl;
	int module_id = Module::ModuleCounter;
	string module_name = "#" + Util::toString(module_id);
	bool equil = false; // Default
	this->construct(module_id,module_name,sim,equil);
}

Module::Module(bool equil){
//	cout << "equil" << endl;
	int module_id = Module::ModuleCounter;
	string module_name = "#" + Util::toString(module_id);
	fSimulator* sim = new fSimulator();
	this->construct(module_id,module_name,sim,equil);
}

Module::Module(int module_id, string module_name){
//	cout << "id + name" << endl;
	fSimulator* sim = new fSimulator();
	bool equil = false; // Default
	this->construct(module_id,module_name,sim,equil);
}

Module::Module(int module_id, fSimulator* sim){
//	cout << "id + sim" << endl;
	string module_name = "#" + Util::toString(module_id);
	bool equil = false; // Default
	this->construct(module_id,module_name,sim,equil);
}

Module::Module(int module_id, bool equil){
//	cout << "id + equil" << endl;
	string module_name = "#" + Util::toString(module_id);
	fSimulator* sim = new fSimulator();
	this->construct(module_id,module_name,sim,equil);
}

Module::Module(string module_name, fSimulator* sim){
//	cout << "name + sim" << endl;
	int module_id = Module::ModuleCounter;
	bool equil = false; // Default
	this->construct(module_id,module_name,sim,equil);
}

Module::Module(string module_name, bool equil){
//	cout << "name + equil" << endl;
	int module_id = Module::ModuleCounter;
	fSimulator* sim = new fSimulator();
	this->construct(module_id,module_name,sim,equil);
}

Module::Module(fSimulator* sim, bool equil){
//	cout << "sim + equil" << endl;
	int module_id = Module::ModuleCounter;
	string module_name = "#" + Util::toString(module_id);
	this->construct(module_id,module_name,sim,equil);
}

Module::Module(int module_id, string module_name, fSimulator* sim){
//	cout << "id + name + sim" << endl;
	bool equil = false; // Default
	this->construct(module_id,module_name,sim,equil);
}

Module::Module(int module_id, string module_name, bool equil){
	//	cout << "id + name + equil" << endl;
	fSimulator* sim = new fSimulator();
	this->construct(module_id,module_name,sim,equil);
}

Module::Module(int module_id, fSimulator* sim, bool equil){
	//	cout << "id + sim + equil" << endl;
	string module_name = "#" + Util::toString(module_id);
	this->construct(module_id,module_name,sim,equil);
}

Module::Module(string module_name, fSimulator* sim, bool equil){
	//	cout << "name + sim + equil" << endl;
	int module_id = Module::ModuleCounter;
	this->construct(module_id,module_name,sim,equil);
}

Module::Module(int module_id, string module_name, fSimulator* sim, bool equil){
	//	cout << "id + name + sim + equil" << endl;
	this->construct(module_id,module_name,sim,equil);
}

// Destructor
Module::~Module(){
	if (MoMMA::debug) cout << "------\n" << "Module destructor called: "  << this->getName() << endl;
	delete this->sim;
	delete this->comm;
	delete this->monitor;
}

// Methods
void Module::updateTimescale(){
	double ts = this->monitor->getTimescale();
	if (!MoMMA::isNAN(ts) && ts != this->timescale){
		this->setTimescale(ts);
		cout << "*New timescale = " << this->timescale << endl;
	}
}

void Module::makeNeighbors(Module* m1, Module* m2, map<Tracker*,Translator*> m1_to_m2, map<Tracker*,Translator*> m2_to_m1){
	map<Tracker*,Translator*>::iterator iter;
	Tracker* var;
	Translator* par;

	// m1->m2
	for (iter = m1_to_m2.begin();iter != m1_to_m2.end();iter++){
		var = (*iter).first;
		par = (*iter).second;
		Module::addLink(m1,var,m2,par);
	}

	// m2->m1
	for (iter = m2_to_m1.begin();iter != m2_to_m1.end();iter++){
		var = (*iter).first;
		par = (*iter).second;
		Module::addLink(m2,var,m1,par);
	}
}

void Module::addLink(Module* m1, Tracker* var, Module* m2, Translator* par){
	Module::addLink(m1,var,INFINITY,m2,par);
}

void Module::addLink(Module* m1, Tracker* var, double varTimescale, Module* m2, Translator* par){

	// Error check
	if ( var->getName().compare( par->getName() ) != 0 ){
		cout << "Oops in Module::addLink(): Variable '" + var->getName() + "' and parameter '"
				+ par->getName() + "' have different names. Exiting." << endl;
		exit(1);
	}

	// Add variable to m1 and add m2 to neighbor list of m1
	map<Module*,int>::iterator it;
	m1->addVariable(var,varTimescale,m2);
	cout << "Module " << m1->getName() << " added variable '" << var->getName() << "'.\n";
	it = m1->neighbors.find(m2);
	if (it != m1->neighbors.end() && (*it).second == 1){ // Already on the list as incoming (1), set to both (2)
		(*it).second = 2;
	}
	else{ // New neighbor
		m1->neighbors.insert( pair<Module*,int>(m2,0) );
	}

	// Add parameter to m2 and add m1 to neighbor list of m2
	m2->addParameter(par);
	cout << "Module " << m2->getName() << " added parameter '" << par->getName() << "'.\n";
	it = m2->neighbors.find(m1);
	if (it != m2->neighbors.end() && (*it).second == 0){ // Already on the list as outgoing (0), set to both
		(*it).second = 2;
	}
	else{ // New neighbor
		m2->neighbors.insert( pair<Module*,int>(m1,1) );
	}
}

void Module::addVariable(Tracker* tr, Module* dest){
	this->comm->addOutgoing(tr->getData(),dest);
	this->monitor->addTracker(tr);
}

void Module::addVariable(Tracker* tr, double timescale, Module* dest){
	this->comm->addOutgoing(tr->getData(),dest);
	this->monitor->addTracker(tr,timescale);
}

void Module::addParameter(Translator* t){ this->comm->addIncoming(t); }

//bool Module::isEquilibrated() {
//	return (this->equilibrated = this->sim->checkForEquilibrium());
//}

void Module::disequilibrate(double currentTime){
	this->local_time = currentTime;
	this->equilibrated = false;
	this->monitor->resetAll(currentTime);
}

double Module::runSimulation(double totalTime, double sampleTime){

	// If totalTime > 0
	if (totalTime > 0.0){

		// Error check
		if (sampleTime > totalTime){
			cout << "Warning: Sampling time exceeds total time in Module::runSimuation()." << endl;
			cout << "Setting sampling time = total time." << endl;
			sampleTime = totalTime;
		}

		// Initialize
		this->sim->initialize();
		this->monitor->synchronize(this->local_time);

		// Simulate in parts, checking the monitor after each run
		double time = 0.0;
		double tEnd;
//		int iteration = 0;

		while( !this->isEquilibrated() // Check for equil first
				&& time < totalTime
//				&& (time < totalTime || iteration == 0) // Do at least one iteration
				&& !this->monitor->anyExceeded() )
		{
//			iteration++;
			tEnd = time + min(sampleTime,totalTime-time);
			time += this->sim->run(time,tEnd);
			this->equilibrated = this->sim->checkForEquilibrium();
		}
		cout << "Module " << this->getName() << " propagated for " << time << " time units.\n";

		// Update local time
		this->local_time += time;
		cout << "Local time = " << this->getLocalTime() << "." << endl;

		return time;
	}
	// Allow for zero time calculations
	else{
		cout << "Warning in Module::runSimulation(): Total simulation time is <= 0.0. Performing a single-step simulation and"
			 << " returning 0.0." << endl;
		this->sim->initialize();
		this->monitor->synchronize(this->local_time);
		this->sim->run(0.0);
		this->equilibrated = this->sim->checkForEquilibrium();
		cout << "Module " << this->getName() << " propagated for " << 0.0 << " time units.\n";
		return 0.0;
	}
}

void Module::rollBack(double amount){
	cout << "Module " << this->getName() << "...";
	// Backtrack, update local time and re-check for equilibrium
	this->sim->rollBack(amount);
	this->local_time -= amount;
	if (this->isEquilibrated()){
		this->setEquilibrated(this->sim->checkForEquilibrium());
	}
	cout << "Local time = " << this->getLocalTime() << endl;
}

void Module::sendMessages(bool immediateAction, bool asPtrData, bool sendAll){

	vector<Tracker*> messages;
	if (sendAll){ messages = this->monitor->getChanged(); }
	else{ messages = this->monitor->getExceeded(); }

	bool success;
	if (messages.size() != 0){
//		cout << "Module " << this->getName() << ":" << endl;
		Data* outData;
		Module* dest;
		for (unsigned int i=0;i < messages.size();i++){
			dest = this->comm->outgoing.find(messages.at(i)->getName())->second;

			// If time of destination module is greater than this module, backtrack the destination
			if (dest->getLocalTime() > this->getLocalTime()){
				cout << "Local time = " << this->getLocalTime() << "; Destination ("
					 << dest->getName() << ") time = " << dest->getLocalTime() << endl;
				double amount = dest->getLocalTime() - this->getLocalTime();
				dest->rollBack(amount);
			}
			// Else if the destination is NOT EQUILIBRATED and its time is less than this module, backtrack this module
			else if (!dest->isEquilibrated() && (dest->getLocalTime() < this->getLocalTime())){
				cout << "Local time = " << this->getLocalTime() << "; Destination ("
					 << dest->getName() << ") time = " << dest->getLocalTime() << endl;
				double amount = this->getLocalTime() - dest->getLocalTime();
				this->rollBack(amount);
			}

			// Communicate data
			if (asPtrData){ outData = messages.at(i)->getData(); }
			else{ outData = messages.at(i)->getData()->convertToNonPtr(); }

			if (immediateAction){ success = this->comm->send(outData); }
			else{ success = this->comm->send(outData,this->getLocalTime()); }

			// If the communication is successful and the destination module is equilibrated, disequilibrate the destination
			if (success && dest->isEquilibrated()){
				dest->disequilibrate(this->getLocalTime());
				cout << ")))Module " << dest->getName() << " now non-equilibrated. Local time = " << dest->getLocalTime() << "(((\n";
			}
		}
		// Don't forget to reset the trackers
		if (sendAll){ this->monitor->resetAll(this->getLocalTime()); }
		else{ this->monitor->resetExceeded(this->getLocalTime()); }

		// Update the timescale
		this->updateTimescale();
	}
}

void Module::processInbox(){
	cout << "Module " << this->getName() << "...";
	if (this->comm->inbox.size() == 0){
		cout << "Nothing in the inbox." << endl;
	}
	else{
		this->comm->processInbox(this->getLocalTime());
	}
}

void Module::clearInbox(){ this->comm->inbox.clear(); }

void Module::initializeOutput(){
	if (this->output.is_open()){
		this->output << "time";
		for (unsigned int i=0;i < this->monitor->trackers.size();i++){
			this->output << "\t" << this->monitor->trackers.at(i)->getName();
		}
		this->output << endl;
	}
}

void Module::outputToFile(){
	if (this->output.is_open()){
		this->output << this->local_time;
		for (unsigned int i=0;i < this->monitor->trackers.size();i++){
			this->output << "\t";
			this->monitor->trackers.at(i)->getData()->printContent(this->output);
		}
		this->output << endl;
	}
}




