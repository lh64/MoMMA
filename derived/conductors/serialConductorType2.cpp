/*
 * serialConductorType2.cpp
 *
 *  Created on: Aug 8, 2010
 *      Author: Leonard Harris
 */

#include "../../borrowed/util/util.hh"
#include "../../testing/communication/commSimulator.hh"
#include "serialConductorType2.hh"

using namespace std;
using namespace MoMMA;

SerialConductorType2::SerialConductorType2(){
	if (MoMMA::debug)
		cout << "SerialConductorType2 constructor called." << endl;
	this->level = NULL;
}

SerialConductorType2::SerialConductorType2(vector< vector<Module*> >& level, double sFactor, double tFactor){
	if (MoMMA::debug)
		cout << "SerialConductorType2 constructor called." << endl;
	this->level = &level;

	if (sFactor > 0.0 && sFactor <= 1.0){ this->sFactor = sFactor; }
	else{
		cout << "Error in SerialConductorType2 constructor: Sampling factor must be > 0.0 and <= 1.0. Exiting." << endl;
		exit(1);
	}

	if (tFactor > 1.0){ this->tFactor = tFactor; }
	else{
		cout << "Error in SerialConductorType2 constructor: Multiplicative factor for tau must be > 1.0. Exiting." << endl;
		exit(1);
	}
}

void SerialConductorType2::go(double startTime, double endTime){

	// Set global time equal to the starting time and make sure all modules have local times equal to the global time
	this->globalTime = startTime;
	for (unsigned int i=0;i < this->level->size();i++){
		for (unsigned int j=0;j < this->level->at(i).size();j++){
			this->level->at(i).at(j)->setLocalTime(this->globalTime);
		}
	}

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

	// Find starting level and print levels
	cout << "Levels: " << this->level->size() << endl;
	cout << "--------------" << endl;
	int startLevel = 0;
	string eq;
	for (unsigned int i=0;i < this->level->size();i++){
		for (unsigned int j=0;j < this->level->at(i).size();j++){
			if (this->level->at(i).at(j)->isEquilibrated()){
				eq = "_(eq)";
			}
			else{
				eq = "_(neq)";
				startLevel = i;
			}
			cout << this->level->at(i).at(j)->getName() + eq + "\t";
		}
		cout << endl;
	}
	cout << "--------------" << endl;
	cout << "Start level: " << (startLevel+1) << endl;
	cout << endl;

	// *** Begin simulation procedure ***
	int iteration = 0;
	double tau = this->level->at(startLevel).at(0)->getTimescale();
//	double tau = this->level->at(startLevel).at(0)->ts->getTimestep(); // Initialize
	vector<int> newEquil; // For storing newly equilibrated modules
	while (this->globalTime < endTime){

		cout << "===== ITERATION " << ++iteration << ": Global time = " << this->globalTime << " =====" << endl << endl;

		// Step 1: Initial simulation sweep
		cout << "///Initial simulation sweep..." << endl << endl;
		double oldTau = NAN;
		double initialTau = tau;
		bool backtrack = false;
		bool foundNeq = false;

		// Loop over levels
		for (int i=startLevel;i >= 0;i--){
			// Loop over modules in level
			for (unsigned int j=0;j < this->level->at(i).size();j++){
				// Only worry about non-equilibrated modules
				if (!this->level->at(i).at(j)->isEquilibrated()){
					foundNeq = true;

					// Run simulation
					if (this->level->at(i).at(j)->getLocalTime() == this->globalTime){
						//******************************************************
	//					tau = this->level->at(i).at(j)->runSimulation(tau,this->sFactor*tau);
						//******************************************************
						double testTau = this->level->at(i).at(j)->getTimescale();
						testTau += 0.1*testTau*Util::RANDOM_GAUSSIAN();
						cout << "(#testTau = " << testTau << ")" << endl;
						testTau = min(tau,testTau);
						tau = this->level->at(i).at(j)->runSimulation(testTau,this->sFactor*testTau);
						//******************************************************
					}
					else if (this->level->at(i).at(j)->getLocalTime() > this->globalTime){
						double targetTau = (this->globalTime + tau) - this->level->at(i).at(j)->getLocalTime();
						double tempTau = this->level->at(i).at(j)->runSimulation(targetTau,this->sFactor*targetTau);
						cout << "(#targetTau = " << targetTau << "; tempTau = " << tempTau << ")" << endl;
						if (tempTau < targetTau){
							tau = tempTau;
						}
					}
					else{ // This shouldn't happen
						cout << "Error: Local time of Module " << this->level->at(i).at(j)->getName()
							 << " (" << this->level->at(i).at(j)->getLocalTime() << ")" << endl;
						cout << " is less than global time (" << this->globalTime << ")." << endl;
						cout << "Shouldn't be possible. Exiting." << endl;
						exit(1);
					}

					// Check if module equilibrated
					//******************************************************
					if (i==2 && j==5){
						this->level->at(2).at(5)->setEquilibrated(true);
						cout << ")))Module " << this->level->at(i).at(j)->getName() << " is now equilibrated(((" << endl;
					}
					//******************************************************
					if (this->level->at(i).at(j)->isEquilibrated()){
						newEquil.push_back(this->level->at(i).at(j)->getId());
					}

					// Check if new tau is less than oldTau
					if (tau != oldTau){
						if (!MoMMA::isNAN(oldTau)){
							if (tau < oldTau){ backtrack = true; }
							else{ // Just to be safe
								cout << "Error: New tau greater than old tau. Shouldn't be possible. Exiting." << endl;
								exit(1);
							}
						}
						cout << "(#tau = " << tau << "; oldTau = " << oldTau << "; initialTau = " << initialTau << ")" << endl;
						oldTau = tau;
						if (tau != initialTau){
//							this->level->at(i).at(j)->setTimescale(tau);
							cout << "**Timescale = " << this->level->at(i).at(j)->getTimescale() << endl;
						}
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
			if (!foundNeq){
				startLevel--;
				cout << "   ## New start level = " << (startLevel+1) << " ##" << endl << endl;
			}
		}
		cout << "tau = " << tau << endl;
//		cout << "...Done.///" << endl << endl;

		// Update global time
		this->globalTime += tau;

		// Step 2: Backtracking phase
/*		cout << "///Backtracking phase..." << endl << endl;
		if (backtrack){
			double localTime;
			bool done=false;
			// Loop over levels
			int i=startLevel;
			while (i >=0 && !done){
				// Loop over modules in level
				int j=0;
				while (j < (int)this->level->at(i).size() && !done){
					// Only worry about non-equilibrated modules
					if (!this->level->at(i).at(j)->isEquilibrated()){
						// Backtrack if the local time of the module is greater than the global time
						localTime = this->level->at(i).at(j)->getLocalTime();
						if (localTime > this->globalTime){
							this->level->at(i).at(j)->backtrack(localTime-this->globalTime);
							cout << endl;
						}
						else{ done = true; }
					}
					j++;
				}
				i--;
			}
		}
*/
//		else{
//			cout << "Nothing to backtrack.";
			// Check to see if we can increase tau
		if (tau == initialTau){
			tau *= this->tFactor;
			cout << "Increasing tau to " << tau;
		}
		cout << endl << endl;
//		}
		cout << "...Done.///" << endl << endl;

		// Step 3: Message sweep
		cout << "///Message sweep..." << endl;
		bool immediate = true; // Immediate action
		bool asPtrData = true; // Send as pointers
		cout << "+++Newly-equilibrated modules: " << newEquil.size() << endl << endl;
//		for (int i=startLevel;i >= 0;i--){
		for (int i=0;i <= startLevel;i++){
//			for (unsigned int j=0;j < this->level->at(i).size();j++){
			for (int j=(this->level->at(i).size()-1);j >= 0;j--){

				// Send messages from non-equilibrated modules...
				if (!this->level->at(i).at(j)->isEquilibrated()){
					this->level->at(i).at(j)->sendMessages(immediate,asPtrData,false);
				}
				// ...OR from newly-equilibrated modules
				else if (newEquil.size() > 0){
					vector<int>::iterator iter;
					iter = newEquil.begin();
					while (*iter != this->level->at(i).at(j)->getId() && iter != newEquil.end()){
						iter++;
					}
					if (iter != newEquil.end()){ // This is a newly-equilibrated module
						cout << "(**newly equilibrated**)" << endl;
						this->level->at(i).at(j)->sendMessages(immediate,asPtrData,true);
						newEquil.erase(iter); // Don't forget to remove the entry from the vector
					}
				}
			}
		}
//		cout << "+++Newly-equilibrated modules: " << newEquil.size() << endl; // There should be zero
		cout << "...Done.///" << endl << endl;

		// Step 4: Start level search
		cout << "///Start-level search..." << endl << endl;
		if (startLevel != ((int)this->level->size()-1)){
			bool newLevel = false;
			// Search below the start level
			for (unsigned int i=(startLevel+1);i < this->level->size();i++){
				unsigned int j = 0;
				bool found = false;
				while (!found && j < this->level->at(i).size()){
					if (!this->level->at(i).at(j)->isEquilibrated()){
						startLevel = i;
						found = true;
						newLevel = true;
					}
					else{
						j++;
					}
				}
			}
			if (newLevel){
				cout << "New start level = " << (startLevel+1) << endl << endl;
			}
			else{
				cout << "No change. Start level = " << (startLevel+1) << endl << endl;
			}
		}
		else{
			cout << "Already at the bottom level." << endl << endl;
		}
		cout << "...Done.///" << endl << endl;

	}

	// Print out final time
	cout << "===== END: Global time = " << globalTime << " =====" << endl << endl;

}
