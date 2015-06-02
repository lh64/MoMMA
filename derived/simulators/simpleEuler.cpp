/*
 * simpleEuler.cpp
 *
 *  Created on: Nov 3, 2010
 *      Author: Leonard Harris
 */

#include "simpleEuler.hh"

using namespace std;
using namespace MoMMA;

SimpleEuler::SimpleEuler(vector<SimpleSpecies*> species, vector<Reaction*> reaction, double tau) : fSimulator(){
	if (MoMMA::debug)
		cout << "SimpleEuler constructor called.\n";
	this->species = species;
	this->reaction = reaction;
	this->setTimestep(tau);
	this->output_interval = INFINITY;
}

void SimpleEuler::addOutputFile(string directory, string filename, double outInterval){
	if ( directory.substr(directory.size()-1,directory.size()-1) != "/" ){
		directory.append("/");
	}
	this->addOutputFile((directory+filename),outInterval);
}

void SimpleEuler::addOutputFile(string filePath, double outInterval){
	this->output_interval = outInterval;
	this->output.open(filePath.c_str());
	// Initialize output file
	this->output << "time";
	for (unsigned int i=0;i < this->species.size();i++){
		this->output << "\t" << this->species.at(i)->name;
	} this->output << endl;
}

double SimpleEuler::run(double tStart, double tEnd){

	// Error check
	if (tEnd < tStart){
		cout << "Error in SimpleEuler::run(): Simulation time cannot be negative. Exiting." << endl;
		exit(1);
	}

	cout << "Simple Euler simulation." << endl;

	int step = 0;
	double time = tStart;
	double nextOutput = tStart + this->output_interval;

	// Initial output
	if (this->output.is_open()){
		// Output to file
		this->output << time;
		for (unsigned int i=0;i < this->species.size();i++){
			this->output << "\t" << this->species.at(i)->population;
		} this->output << endl;
	}
	// Output to stdout
	if (this->output_interval != INFINITY){
		cout << "time";
		for (unsigned int i=0;i < this->species.size();i++){
			cout << "\t" << this->species.at(i)->name;
		}
		cout << endl;
		cout << time;
		for (unsigned int i=0;i < this->species.size();i++){
			cout << "\t" << this->species.at(i)->population;
		}
		cout << endl;
	}

	// Simulation loop
	bool lastOut;
	double sumRates = 0.0;
	for (unsigned int i=0;i < this->reaction.size();i++){
		sumRates += this->reaction.at(i)->getRate();
	}
	while (time < tEnd && sumRates > MoMMA::TOL){

		// Next step
		step++;
		time += this->tau;
		double K;
		for (unsigned int i=0;i < this->reaction.size();i++){
			K = this->reaction.at(i)->getRate()*this->tau;
			this->reaction.at(i)->fire(K);
		}

		// Output
		lastOut = false;
		if (time >= nextOutput){
			nextOutput += this->output_interval;
			lastOut = true;
			// Output to file
			if (this->output.is_open()){
				this->output << time;
				for (unsigned int i=0;i < this->species.size();i++){
					this->output << "\t" << this->species.at(i)->population;
				} this->output << endl;
			}
			// Output to stdout
			cout << time;
			for (unsigned int i=0;i < this->species.size();i++){
				cout << "\t" << this->species.at(i)->population;
			}
			cout << endl;
		}

		// Update sumRates
		sumRates = 0.0;
		for (unsigned int i=0;i < this->reaction.size();i++){
			sumRates += this->reaction.at(i)->getRate();
		}
	}

	// Final output
	if (!lastOut){
		// Output to file
		if (this->output.is_open()){
			this->output << time;
			for (unsigned int i=0;i < this->species.size();i++){
				this->output << "\t" << this->species.at(i)->population;
			} this->output << endl;
		}
		// Output to stdout
		if (this->output_interval != INFINITY){
			cout << time;
			for (unsigned int i=0;i < this->species.size();i++){
				cout << "\t" << this->species.at(i)->population;
			}
			cout << endl;
		}
	}

	return (time-tStart);
}





