/*
 * serialConductorType1.cpp
 *
 *  Created on: Jul 13, 2010
 *      Author: Leonard Harris
 */

#include "../../borrowed/util/util.hh"
#include "../../testing/communication/commSimulator.hh"
#include "serialConductorType1.hh"

using namespace std;
using namespace MoMMA;

SerialConductorType1::SerialConductorType1(){
	if (MoMMA::debug)
		cout << "SerialConductorType1 constructor called." << endl;
	this->level = NULL;
}

SerialConductorType1::SerialConductorType1(vector< vector<Module*> >& level, double samplingFraction, double tauMultiplier){
	if (MoMMA::debug)
		cout << "SerialConductorType1 constructor called." << endl;
	this->level = &level;

	if (samplingFraction > 0.0 && samplingFraction <= 1.0){ this->samplingFraction = samplingFraction; }
	else{
		cout << "Error in SerialConductorType1 constructor: Sampling factor must be > 0.0 and <= 1.0. Exiting." << endl;
		exit(1);
	}

	if (tauMultiplier >= 1.0){ this->tauMultiplier = tauMultiplier; }
	else{
		cout << "Error in SerialConductorType1 constructor: Multiplicative factor for tau must be >= 1.0. Exiting." << endl;
		exit(1);
	}
	// Initialize
	this->initialize();
	this->output_interval = INFINITY;
}

void SerialConductorType1::initialize(){

	// Confirm that all children of equilibrated modules are also equilibrated
	cout << "Checking for proper equilibrium status in the hierarchy:" << endl;
	int nProblems = 0;
	bool already;
	for (unsigned int i=0;i < (this->level->size()-1);i++){ // Only loop down to the next-to-last level
		for (unsigned int j=0;j < this->level->at(i).size();j++){
			if (this->level->at(i).at(j)->isEquilibrated()){ // Module is equilibrated
				already = false;
				// Loop over all levels below level i
				unsigned int k = i+1;
				while (k < this->level->size() && !already){
					// Loop through modules on the lower level
					unsigned int l = 0;
					while (l < this->level->at(k).size() && !already){
						if (!this->level->at(k).at(l)->isEquilibrated()
								&& !already
								&& this->level->at(i).at(j)->neighbors.find(this->level->at(k).at(l))
								!= this->level->at(i).at(j)->neighbors.end()){
							// Found a problem
							nProblems++;
							already = true;
							this->level->at(i).at(j)->setEquilibrated(false);

							cout << "---Warning: Module " << this->level->at(i).at(j)->getName()
								 << " is equilibrated but its child Module "
								 << this->level->at(k).at(l)->getName() << " is not. Changing status of "
								 << this->level->at(i).at(j)->getName() << " to non-equilibrated.---" << endl;
						}
						l++;
					}
					k++;
				}
			}
		}
	}
	cout << nProblems << " problem(s) found";
	if (nProblems > 0){ cout << " and fixed"; }
	cout << "." << endl;
	cout << endl;

	// Print levels, Find starting level and initialize output files
	cout << "Levels: " << this->level->size() << endl;
	cout << "--------------" << endl;
	this->startLevel = 0;
	this->nModules = 0;
	string eq;
	for (unsigned int i=0;i < this->level->size();i++){
		for (unsigned int j=0;j < this->level->at(i).size();j++){
			this->nModules++;
			this->level->at(i).at(j)->initializeOutput();
			if (this->level->at(i).at(j)->isEquilibrated()){
				eq = "_(eq)";
			}
			else{
				eq = "_(neq)";
				this->startLevel = i;
			}
			cout << this->level->at(i).at(j)->getName() + eq + "\t";
		}
		cout << endl;
	}
	cout << "--------------" << endl;
	cout << "No. of Modules: " << this->nModules << endl;
	cout << "Start level: " << (this->startLevel+1) << endl;
	cout << endl;
}

void SerialConductorType1::go(double startTime, double endTime){
	double startTau = this->level->at(this->startLevel).at(0)->getTimescale();
	this->go(startTime,endTime,startTau);
}

void SerialConductorType1::go(double startTime, double endTime, double startTau){

	// Set global time equal to the starting time and make sure all modules have local times equal to the global time
	this->globalTime = startTime;
	for (unsigned int i=0;i < this->level->size();i++){
		for (unsigned int j=0;j < this->level->at(i).size();j++){
			this->level->at(i).at(j)->setLocalTime(this->globalTime);
			this->level->at(i).at(j)->outputToFile(); // Output initial state to file
		}
	}

	// Output
	double nextOutput = this->globalTime + this->output_interval;
	bool lastOut; // For outputting final state

	// *** Begin simulation procedure ***
	int iteration = 0;
//	double tau = this->level->at(startLevel).at(0)->getTimescale(); // Initialize
	double tau = startTau; // Initialize
	vector<int> newEquil;  // For storing newly equilibrated modules
	vector<int>::iterator equilIter;
	bool foundNeq = true;  // Stop if no non-equilibrated modules found

//	while (iteration < 245918){
	while ( this->globalTime < (endTime-MoMMA::TOL) && foundNeq ){

		cout << "===== ITERATION " << ++iteration << ": Global time = " << this->globalTime << " =====" << endl << endl;

		// Step 1: Initial simulation sweep
		cout << "///Initial simulation sweep..." << endl << endl;
		double oldTau = NAN;
		double initialTau = tau;
		bool backtrack = false;
		foundNeq = false;

		// Loop over levels
		for (int i=this->startLevel;i >= 0;i--){
			// Loop over modules in level
			for (unsigned int j=0;j < this->level->at(i).size();j++){
				// Only worry about non-equilibrated modules
				if (!this->level->at(i).at(j)->isEquilibrated()){

					if (!foundNeq && i != this->startLevel){
						this->startLevel = i; // Change start level
						tau = this->level->at(i).at(j)->getTimescale(); // Get new timestep
						cout << "## New start level = " << (this->startLevel+1) << " (of " << this->level->size() << ")"
							 << endl;
						cout << "## New starting tau = " << tau << endl << endl;
					}
					foundNeq = true;

					// Run simulation
					//******************************************************
					tau = this->level->at(i).at(j)->runSimulation(tau,this->samplingFraction*tau);
					//******************************************************
//					double testTau = this->level->at(i).at(j)->getTimescale();
//					testTau += 0.1*testTau*Util::RANDOM_GAUSSIAN();
//					cout << "(#testTau = " << testTau << ")" << endl;
//					testTau = min(tau,testTau);
//					tau = this->level->at(i).at(j)->runSimulation(testTau,this->sFactor*testTau);
					//******************************************************

					// Check if module equilibrated
					//******************************************************
//					if (i==2 && j==5){ // Module m23
//						if (iteration == 5){
//							this->level->at(2).at(5)->setEquilibrated(true);
//							cout << ")))Module " << this->level->at(i).at(j)->getName() << " is now equilibrated(((" << endl;
//						}
//					}
					//******************************************************
					if (this->level->at(i).at(j)->isEquilibrated()){
						newEquil.push_back(this->level->at(i).at(j)->getId());
						cout << ")))Module " << this->level->at(i).at(j)->getName() << " is now equilibrated(((" << endl;
						// Error check
						if (newEquil.size() > this->nModules){
							cout << "Error in SerialConductorType1::go(): Number of equilibrated modules ("
								 << newEquil.size() << ") exceeds total number of modules (" << this->nModules
								 << "). Exiting." << endl;
							exit(1);
						}
					}

					// Check if new tau is less than oldTau
					if (tau != oldTau){
						if (!MoMMA::isNAN(oldTau)){
							if ( (tau-oldTau) < MoMMA::TOL ){ backtrack = true; }
							else if ( (tau-oldTau) > MoMMA::TOL ){ // Just to be safe
								cout << "Error: New tau greater than old tau. Shouldn't be possible. Exiting." << endl;
								printf("tau = %22.20lf, oldTau = %22.20lf\n",tau,oldTau);
								exit(1);
							}
						}
						cout << "(#tau = " << tau << "; oldTau = " << oldTau << "; initialTau = " << initialTau << ")" <<endl;
						cout << "(#backtrack = ";
						if (backtrack) { cout << "true)" << endl; }
						else { cout << "false)" << endl; }
						oldTau = tau;
					}
				}
				else{
					cout << "Module " << this->level->at(i).at(j)->getName() << " is in equilibrium." << endl;
				}
				//******************************************************
				// Print out variable value
//				cout << static_cast<CommSimulator*>(this->level->at(i).at(j)->sim)->sim_data
//					 << endl;
				//******************************************************
				cout << endl;
			}
			// If a non-equilibrated module was not found on this level, move the start level up
//			if (!foundNeq){
//				this->startLevel--;
//				cout << "   ## New start level = " << (this->startLevel+1) << " ##" << endl;
//			} ***DELETE***
		}
		cout << "tau = " << tau << endl;
		cout << "...Done.///" << endl << endl;

		// Update global time
		this->globalTime += tau;
		cout << "Global time = " << this->globalTime << endl << endl;

		// Step 2: Backtracking phase
		cout << "///Backtracking phase..." << endl << endl;
		if (backtrack){
			double localTime;
			bool done=false;
			// Loop over levels
			int i = this->startLevel;
			while (i >= 0 && !done){
				// Loop over modules in level
				int j=0;
				while (j < (int)this->level->at(i).size() && !done){

					// Backtrack if the local time of the module is greater than the global time
					localTime = this->level->at(i).at(j)->getLocalTime();
					if (localTime > this->globalTime){
						bool check = this->level->at(i).at(j)->isEquilibrated(); // If it's equilibrated, it may disequilibrate
						this->level->at(i).at(j)->rollBack(localTime-this->globalTime);

						// If it disequilibrated, remove it from the newEquil vector
						if (check && !this->level->at(i).at(j)->isEquilibrated()){
							equilIter = newEquil.begin();
							while (*equilIter != this->level->at(i).at(j)->getId() && equilIter != newEquil.end()){
								equilIter++;
							}
							if (equilIter != newEquil.end()){ // Found it
								newEquil.erase(equilIter);
							}
							else{ // Problem, where is it?
								cout << "ERROR: Module " << this->level->at(i).at(j)->getName()
									 << " disequilibrated during backtracking but can't be found in newEquil vector. Exiting.\n";
								exit(1);
							}
						}
						cout << endl;
					}
					else if (!this->level->at(i).at(j)->isEquilibrated()){
						// Found a non-equilibrated module with localTime <= globalTime
						if (localTime < this->globalTime){ // Just to be safe
							cout << "ERROR: Local time of module " << this->level->at(i).at(j)->getName()
								 << "(" << this->level->at(i).at(j)->getLocalTime() << ") is less ";
							cout << "than global time (" << this->globalTime << "). Shouldn't be possible. Exiting." << endl;
							exit(1);
						}
						done = true;
					}
					j++;
				}
				i--;
			}
		}
		else{
			cout << "Nothing to backtrack. ";
			// Check to see if we can increase tau
			if (tau == initialTau){
				tau *= this->tauMultiplier;
				cout << "Increasing tau to " << tau;
			}
			cout << endl << endl;
		}
		cout << "...Done.///" << endl << endl;

		// Step 3: Message sweep
		cout << "///Message sweep..." << endl;
		bool immediate = true; // Immediate action
		bool asPtrData = true; // Send as pointers
		cout << "+++Newly-equilibrated modules: " << newEquil.size() << endl << endl;

		for (int i=this->startLevel;i >= 0;i--){
			for (unsigned int j=0;j < this->level->at(i).size();j++){

				cout << "Module " << this->level->at(i).at(j)->getName() << ":" << endl;

				// Send messages from non-equilibrated modules...
				if (!this->level->at(i).at(j)->isEquilibrated()){
					this->level->at(i).at(j)->sendMessages(immediate,asPtrData,false);
					/////*****
//					for (unsigned int xx=0;xx < this->level->at(i).at(j)->monitor->trackers.size();xx++){
//						cout << this->level->at(i).at(j)->monitor->trackers.at(xx)->getName() << ": ";
//						this->level->at(i).at(j)->monitor->trackers.at(xx)->getData()->printContent(cout);
//						cout << endl;
//					}
//					cout << endl;
					/////*****
				}
				// ...OR from newly-equilibrated modules
				else if (newEquil.size() > 0){
					equilIter = newEquil.begin();
					while (*equilIter != this->level->at(i).at(j)->getId() && equilIter != newEquil.end()){
						equilIter++;
					}
					if (equilIter != newEquil.end()){ // This is a newly-equilibrated module
						cout << ")**newly equilibrated**(" << endl;
						this->level->at(i).at(j)->sendMessages(immediate,asPtrData,true);
						newEquil.erase(equilIter); // Don't forget to remove the entry from the vector
					}
				}
				cout << endl;
			}
		}
		// Warn if not all equilibrated modules found (higher level modules must have been disequilibrated)
		if (newEquil.size() > 0){
//			cout << "Error in SerialConductorType1::go(): Could not find equilibrated Modules:";
			cout << "Warning in SerialConductorType1::go(): Could not find equilibrated Modules:";
			for (unsigned int i=0;i < newEquil.size();i++){
				cout << " " << newEquil.at(i);
			}
			cout << endl;
//			cout << "Exiting." << endl;
			newEquil.clear();
//			exit(1);
		}
		cout << "...Done.///" << endl << endl;

		// Step 4: Start level search
		cout << "///Start-level search..." << endl << endl;
		if (this->startLevel != ((int)this->level->size()-1)){
			bool newLevel = false;
			// Search below the start level
			for (unsigned int i=(this->startLevel+1);i < this->level->size();i++){
				unsigned int j = 0;
				bool found = false;
				while (!found && j < this->level->at(i).size()){
					if (!this->level->at(i).at(j)->isEquilibrated()){
						this->startLevel = i;
						found = true;
						newLevel = true;
					}
					else{
						j++;
					}
				}
			}
			if (newLevel){
				cout << "New start level = " << (this->startLevel+1) << " (of " << this->level->size() << ")" << endl;
				// Get a new starting tau
				unsigned int startModule = 0;
				while (this->level->at(this->startLevel).at(startModule)->isEquilibrated()){
					startModule++;
				}
				tau = this->level->at(this->startLevel).at(startModule)->getTimescale();
				cout << "New starting tau = " << tau << endl << endl;
			}
			else{ cout << "No change. Start level = " << (this->startLevel+1) << " (of " << this->level->size() << ")"
					   << endl << endl; }
		}
		else{ cout << "Already at bottom level (level " << this->level->size() << ")." << endl << endl; }
		cout << "...Done.///" << endl << endl;

		// Output to file
		lastOut=false;
		if (this->globalTime >= nextOutput){
			for (unsigned int i=0;i < this->level->size();i++){
				for (unsigned int j=0;j < this->level->at(i).size();j++){
					if (this->level->at(i).at(j)->isEquilibrated()){
						this->level->at(i).at(j)->setLocalTime(this->globalTime);
					}
					this->level->at(i).at(j)->outputToFile();
				}
			}
			nextOutput += this->output_interval;
			lastOut = true;
		}
	}

	// Output final state if appropriate
	if (!lastOut){
		for (unsigned int i=0;i < this->level->size();i++){
			for (unsigned int j=0;j < this->level->at(i).size();j++){
				this->level->at(i).at(j)->outputToFile();
			}
		}
	}

	// Print out final time
	cout << "===== END: Global time = " << globalTime << " =====" << endl << endl;
}
