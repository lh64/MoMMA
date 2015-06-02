/*
 * gillespieDM.cpp
 *
 *  Created on: Oct 10, 2010
 *      Author: Leonard Harris
 */

#include "gillespieDM.hh"

using namespace std;
using namespace MoMMA;

GillespieDM::GillespieDM(vector<SimpleSpecies*> species, vector<Reaction*> reaction)
	: species(species), reaction(reaction), sumRates(0.0), sort(false), output_interval(INFINITY){

	if (MoMMA::debug)
		cout << "GillespieDM constructor called.\n";

	// Round the species populations
	for (unsigned int i=0;i < this->species.size();i++){
		this->species[i]->setPopulation(floor(this->species[i]->population + 0.5));
	}

	// Initialize sumRates
	this->calcSumRates();
}

void GillespieDM::addDependencyMap(map<Reaction*,vector<Reaction*> > dependency){
	// Error check
	if (dependency.size() != this->reaction.size()){
		cout << "Error in GillespieDM::addDependencyMatrix(): 'dependency' must be same size as 'reaction' vector. ";
		cout << "Exiting." << endl;
		exit(1);
	}
	this->dependency = dependency;
}

void GillespieDM::addDependencyMap(vector<vector<Reaction*> > dependency){
	// Error check
	if (dependency.size() != this->reaction.size()){
		cout << "Error in GillespieDM::addDependencyMatrix(): 'dependency' must be same size as 'reaction' vector. ";
		cout << "Exiting." << endl;
		exit(1);
	}
	for (unsigned int i=0;i < dependency.size();i++){
		this->dependency.insert( pair<Reaction*,vector<Reaction*> >(this->reaction.at(i),dependency.at(i)) );
	}
}

void GillespieDM::addOutputFile(string directory, string filename, double outInterval){
	if ( directory.substr(directory.size()-1,directory.size()-1) != "/" ){
		directory.append("/");
	}
	this->addOutputFile((directory+filename),outInterval);
}

void GillespieDM::addOutputFile(string filePath, double outInterval){
	this->output_interval = outInterval;
	this->output.open(filePath.c_str());
	// Initialize output file
	this->output << "time" << "\t" << "step" << "\t" << "tau";
	for (unsigned int i=0;i < this->species.size();i++){
		this->output << "\t" << this->species.at(i)->name;
	} this->output << endl;
}

double GillespieDM::calcSumRates(){
	// Calculate sumRates
	this->sumRates = 0.0;
	for (unsigned int i=0;i < this->reaction.size();i++){
		this->sumRates += this->reaction.at(i)->getRate();
	}
	return this->sumRates;
}

double GillespieDM::run(double tStart, double tEnd){

	// Error check
	if (tEnd < tStart){
		cout << "Error in GillespieDM::run(): Simulation time cannot be negative. Exiting." << endl;
		exit(1);
	}
/*
	cout << "Gillespie DM simulation: Sorting turned ";
	if (this->sort){ cout << "ON; ";}
	else{ cout << "OFF; "; }
	if (this->dependency.size() == 0){ cout << "NOT using "; }
	else{ cout << "Using "; }
	cout << "dependency map for rate updates." << endl;
*/
	// Initialize sumRates
	this->calcSumRates();

	int step=0;
	double time = tStart;
	double tau;

	double nextOutput = tStart + this->output_interval;
	bool lastOut = true;

	// Initial output
	if (this->output.is_open()){
		// Output to file
		this->output << time << "\t" << step << "\t" << 0.0;
		for (unsigned int i=0;i < this->species.size();i++){
			this->output << "\t" << this->species.at(i)->population;
		} this->output << endl;
	}
	// Output to stdout
	if (this->output_interval != INFINITY){
		cout << "time" << "\t" << "step";
		for (unsigned int i=0;i < this->species.size();i++){
			cout << "\t" << this->species.at(i)->name;
		}
		cout << endl;
		cout << time << "\t" << step;
		for (unsigned int i=0;i < this->species.size();i++){
			cout << "\t" << this->species.at(i)->population;
		}
		cout << endl;
	}

	// Simulation loop
	while (time < tEnd && this->sumRates > 0.0){

		// Next step
		step++;
		tau = this->nextStep(tEnd-time);
		time += tau;

		// Output
		lastOut = false;
		if (time >= nextOutput){
			nextOutput += this->output_interval;
			lastOut = true;
			// Output to file
			if (this->output.is_open()){
				this->output << time << "\t" << step << "\t" << tau;
				for (unsigned int i=0;i < this->species.size();i++){
					this->output << "\t" << this->species.at(i)->population;
				} this->output << endl;
			}
			// Output to stdout
			cout << time << "\t" << step;
			for (unsigned int i=0;i < this->species.size();i++){
				cout << "\t" << this->species.at(i)->population;
			}
			cout << endl;
		}
	}

	// Final output
	if (!lastOut){
		// Output to file
		if (this->output.is_open()){
			this->output << time << "\t" << step << "\t" << tau;
			for (unsigned int i=0;i < this->species.size();i++){
				this->output << "\t" << this->species.at(i)->population;
			} this->output << endl;
		}
		// Output to stdout
		if (this->output_interval != INFINITY){
			cout << time << "\t" << step;
			for (unsigned int i=0;i < this->species.size();i++){
				cout << "\t" << this->species.at(i)->population;
			}
			cout << endl;
		}
	}

	return (time-tStart);
}

double GillespieDM::run(double tStart, int nSteps){

	// Error check
	if (nSteps < 0){
		cout << "Error in GillespieDM::run(): Number of simulation steps cannot be negative. Exiting." << endl;
		exit(1);
	}
/*
	cout << "Gillespie DM simulation: Sorting turned ";
	if (this->sort){ cout << "ON; ";}
	else{ cout << "OFF; "; }
	if (this->dependency.size() == 0){ cout << "NOT using "; }
	else{ cout << "Using "; }
	cout << "dependency map for rate updates." << endl;
*/
	// Initialize sumRates
	this->calcSumRates();

	int step=0;
	double time = tStart;
	double tau;

	double nextOutput = this->output_interval;
	bool lastOut = true;

	// Initial output
	if (this->output.is_open()){
		// Output to file
		this->output << time << "\t" << step << "\t" << 0.0;
		for (unsigned int i=0;i < this->species.size();i++){
			this->output << "\t" << this->species.at(i)->population;
		} this->output << endl;
	}
	// Output to stdout
	if (this->output_interval != INFINITY){
		cout << "time" << "\t" << "step";
		for (unsigned int i=0;i < this->species.size();i++){
			cout << "\t" << this->species.at(i)->name;
		}
		cout << endl;
		cout << time << "\t" << step;
		for (unsigned int i=0;i < this->species.size();i++){
			cout << "\t" << this->species.at(i)->population;
		}
		cout << endl;
	}

	// Simulation loop
	while (step < nSteps  && this->sumRates > 0.0){

		// Next step
		step++;
		tau = this->nextStep();
		time += tau;

		// Output
		lastOut = false;
		if (time >= nextOutput){
			nextOutput += this->output_interval;
			lastOut = true;
			// Output to file
			if (this->output.is_open()){
				this->output << time << "\t" << step << "\t" << tau;
				for (unsigned int i=0;i < this->species.size();i++){
					this->output << "\t" << this->species.at(i)->population;
				} this->output << endl;
			}
			// Output to stdout
			cout << time << "\t" << step;
			for (unsigned int i=0;i < this->species.size();i++){
				cout << "\t" << this->species.at(i)->population;
			}
			cout << endl;
		}
	}

	// Final output
	if (!lastOut){
		// Output to file
		if (this->output.is_open()){
			this->output << time << "\t" << step << "\t" << tau;
			for (unsigned int i=0;i < this->species.size();i++){
				this->output << "\t" << this->species.at(i)->population;
			} this->output << endl;
		}
		// Output to stdout
		if (this->output_interval != INFINITY){
			cout << time << "\t" << step;
			for (unsigned int i=0;i < this->species.size();i++){
				cout << "\t" << this->species.at(i)->population;
			}
			cout << endl;
		}
	}

	return (time - tStart);
}

double GillespieDM::nextStep(double maxTau){

	// Calculate tau
	double tau = NAN;
	double r1 = Util::RANDOM_CLOSED();
	tau = -log(r1)/this->sumRates;

	///////
//	cout << "sumRates = " << this->sumRates << endl;
/*	double test = 0.0;
	for (unsigned int i=0;i < this->reaction.size();i++){
		test += this->reaction.at(i)->getRate();
	}
	if ( fabs(test-this->sumRates) > MoMMA::TOL ){
		cout << "Error in GillespieDM::nextStep(): Error in sumRates calculation. Exiting" << endl;
		cout << "(sumRates = " << this->sumRates << ", test = " << test << ")" << endl;
		exit(1);
	}*/
//	cout << "test = " << test << endl;
	///////

	if (tau <= maxTau){

		// Identify firing reaction
		double r2 = Util::RANDOM_CLOSED();
		//
//		cout << "r2*sumRates = " << (r2*this->sumRates) << endl;
		//
		int firingRxn = -1;
		double partialSum = 0.0;
//		while (partialSum < (r2*this->sumRates)){
		while ( (r2*this->sumRates - partialSum) > MoMMA::TOL ){
			firingRxn++;
			//
			// Sorting procedure
			if (this->sort){
				if (firingRxn < (int)this->reaction.size()-1){
					// If rate of this reaction is LESS than the next one, swap them
					if (this->reaction.at(firingRxn)->getRate() < this->reaction.at(firingRxn+1)->getRate()){
						Reaction* temp = this->reaction.at(firingRxn+1);
						this->reaction.at(firingRxn+1) = this->reaction.at(firingRxn);
						this->reaction.at(firingRxn) = temp;
					}
				}
			}
			// Error check
			if (firingRxn >= (int)this->reaction.size()){
				cout << "Error in GillespieDM::nextStep(): Could not identify next firing reaction. Exiting." << endl;
				cout << "(firingRxn = " << firingRxn << ", reaction.size() = " << this->reaction.size() << ")" << endl;
//				printf("(partialSum = %22.20lf, r2*sumRates = %22.20lf, r2 = %22.20lf)\n",partialSum,r2*this->sumRates,r2);
				cout << "(partialSum = " << partialSum << ", sumRates = " << this->sumRates << ", r2 = " << r2 << ")\n";
				exit(1);
			}
			//
//			cout << "partialSum = " << partialSum << endl;
//			cout << "firingRxn = " << firingRxn << endl;
			partialSum += this->reaction.at(firingRxn)->getRate();
		}

		// Just in case r2 < MoMMA::TOL (which it is sometimes)
		if (firingRxn == -1){
			firingRxn = 0;
//			cout << "Error in GillespieDM::nextStep(): Could not identify next firing reaction. Exiting." << endl;
//			printf("(firingRxn = -1, partialSum = %22.20lf, r2*sumRates = %22.20lf, r2 = %22.20lf)\n",
//					partialSum,r2*this->sumRates,r2);
//			exit(1);
		}

		// Fire reaction and update sumRates
		if (this->dependency.size() != 0){ // If using dependencies

			// Find position of firing reaction in the dependency map
			map<Reaction*,vector<Reaction*> >::iterator rxnIter;
			rxnIter = this->dependency.find(this->reaction.at(firingRxn));

			// Subtract rates of all affected reactions from sumRates
			for (unsigned int i=0;i < (*rxnIter).second.size();i++){
				this->sumRates -= (*rxnIter).second.at(i)->getRate();
			}

			// Fire reaction
			this->reaction.at(firingRxn)->fire(1.0);

			// Add new rates of all affected reactions to sumRates
			for (unsigned int i=0;i < (*rxnIter).second.size();i++){
				this->sumRates += (*rxnIter).second.at(i)->getRate();
			}
		}
		else{ // Otherwise, simple update

			// Fire reaction
			this->reaction.at(firingRxn)->fire(1.0);

			// Recalculate sumRates
			this->calcSumRates();
//			cout << "update = " << this->sumRates << endl;
		}
	}
	else{
		tau = maxTau;
//		cout << "tau > maxTau" << endl;
	}

	return tau;
}
