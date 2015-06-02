/*
 * simulators_MM1.hh
 *
 *  Created on: Dec 2, 2010
 *      Author: Leonard Harris
 */

#ifndef SIMULATORS_MM1_HH_
#define SIMULATORS_MM1_HH_

#include "../../../MoMMA.hh"
#include "../../../derived/simulators/gillespieDM.hh"

using namespace std;

namespace MoMMA{

	class SlowGillespie_MM1 : public fSimulator{
	public:
		GillespieDM* gillespSim;
		bool equil;	// equilibration flag (only TRUE if E_T == 0.0)
		double fastTau;
		double* P;		// product population (variable)**
		double* kcat;	// catalytic rate constant (parameter)**
		SlowGillespie_MM1(GillespieDM* gillespSim, double fastTau);
		~SlowGillespie_MM1(){}
		virtual void initialize(){ this->gillespSim->initialize(); }
		virtual double run(double t){ return this->run(0.0,t); }
		virtual double run(double tStart, double tEnd);
//		virtual void rollBack(double amount);
		virtual bool checkForEquilibrium();
	};

	class FastGillespie_MM1 : public fSimulator{
	public:
		GillespieDM* gillespSim;
		bool equil;		// equilibration flag
		double E_T;		// total enzyme
		double S_T;		// total substrate
		double f;		// <ES>/E_T (variable)**
		double P, dP; 	// product population and change in population (parameter)**
		FastGillespie_MM1(GillespieDM* gillespSim);
		~FastGillespie_MM1(){}
		virtual void initialize();
		virtual double run(double t){ return this->run(0.0,t); }
		virtual double run(double tStart, double tEnd);
//		virtual void rollBack(double amount);
		virtual bool checkForEquilibrium();
	};

}

#endif /* SIMULATORS_MM1_HH_ */
