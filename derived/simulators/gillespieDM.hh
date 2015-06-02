/*
 * gillespieDM.hh
 *
 * A Gillespie direct method implementation
 *
 *  Created on: Oct 10, 2010
 *      Author: Leonard Harris
 */

#ifndef GILLESPIEDM_HH_
#define GILLESPIEDM_HH_

#include <fstream>
#include "../../MoMMA.hh"
#include "../../borrowed/util/util.hh"
#include "../../model_spec/simpleSpecies.hh"
#include "../../model_spec/reaction.hh"

using namespace std;

namespace MoMMA{

	class GillespieDM : public fSimulator {

	public:
		vector<SimpleSpecies*> species;
		vector<Reaction*> reaction;

//		GillespieDM(){}

		GillespieDM(vector<SimpleSpecies*> species, vector<Reaction*> reaction);

		~GillespieDM(){}

		void setSort(bool sort){ this->sort = sort; }
		void addDependencyMap(map<Reaction*,vector<Reaction*> > dependency);
		void addDependencyMap(vector<vector<Reaction*> > dependency);
		//
		void addOutputFile(string directory, string filename){ this->addOutputFile(directory,filename,INFINITY); }
		void addOutputFile(string filePath){ this->addOutputFile(filePath,INFINITY); }
		void addOutputFile(string directory, string filename, double outInterval);
		void addOutputFile(string filePath, double outInterval);
		//
		void setOutputInterval(double outInterval){ this->output_interval = outInterval; }
		void setSeed(unsigned long seed){ Util::SEED_RANDOM(seed); }
		void setSeed(long seed){ this->setSeed((unsigned long)seed); }
		void setSeed(int seed){ this->setSeed((unsigned long)seed); }
		//
		double calcSumRates();

		virtual void initialize(){ this->calcSumRates(); }
		virtual double run(double t){ return this->run(0.0,t); }
		virtual double run(double tStart, double tEnd);
		double run(int nSteps){ return this->run(0.0,nSteps); }
		double run(double tStart, int nSteps);
		double nextStep(){ return this->nextStep(INFINITY); }
		double nextStep(double maxTau);

	protected:
		double sumRates;
		bool sort;
		map<Reaction*,vector<Reaction*> > dependency;
		//
		ofstream output;
		double output_interval;
	};
}

#endif /* GILLESPIEDM_HH_ */
