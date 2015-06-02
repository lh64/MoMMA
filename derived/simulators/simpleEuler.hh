/*
 * simpleEuler.hh
 *
 * A simple forward Euler ODE integrator
 *
 *  Created on: Nov 3, 2010
 *      Author: Leonard Harris
 */

#ifndef SIMPLEEULER_HH_
#define SIMPLEEULER_HH_

#include <fstream>
#include "../../MoMMA.hh"
#include "../../model_spec/simpleSpecies.hh"
#include "../../model_spec/reaction.hh"

using namespace std;

namespace MoMMA{

	class SimpleEuler : public fSimulator {

	public:
		vector<SimpleSpecies*> species;
		vector<Reaction*> reaction;

		SimpleEuler(){}

		SimpleEuler(vector<SimpleSpecies*> species, vector<Reaction*> reaction, double tau);

		~SimpleEuler(){}

		void addOutputFile(string directory, string filename){ this->addOutputFile(directory,filename,INFINITY); }
		void addOutputFile(string filePath){ this->addOutputFile(filePath,INFINITY); }
		void addOutputFile(string directory, string filename, double outInterval);
		void addOutputFile(string filePath, double outInterval);
		//
		void setOutputInterval(double outInterval){ this->output_interval = outInterval; }

		void setTimestep(double tau){ this->tau = tau; }
		virtual double run(double t){ return this->run(0.0,t); }
		virtual double run(double tStart, double tEnd);

	protected:
		double tau;
		ofstream output;
		double output_interval;
	};
}

#endif /* SIMPLEEULER_HH_ */
