/*
 * approxPL_TC.hh
 *
 *  Created on: May 9, 2011
 *      Author: Leonard Harris
 */

#ifndef APPROXPL_TC_HH_
#define APPROXPL_TC_HH_

#include "../fEuler/fEuler.hh"
#include "../../../../model_spec/reaction.hh"

using namespace std;

namespace MoMMA{

	class ApproxRBPostleap_TC : public TauCalculator{
	public:
//		ApproxRBPostleap_TC();
		ApproxRBPostleap_TC(double eps, double w, vector<SimpleSpecies*>& sp, vector<Reaction*>& rxn, Preleap_TC& ptc);
		virtual ~ApproxRBPostleap_TC();
		virtual void getNewTau(double& tau);
	protected:
		double eps;
		double w;
		bool preCalc;
		Preleap_TC& ptc;
		double* currRate;
		vector<int>* spInRxn; 	// spInRxn[sp.size()][#rxns sp involved in]
		vector<double>* stoich; // stoich[sp.size()][#rxns sp involved in]
		vector<int>* rateSp;	// rateSp[rxn.size()][#sp that contribute to rate]
	private:
		vector<SimpleSpecies*>& sp;
		vector<Reaction*>& rxn;
	};

	class ApproxSBPostleap_TC : public fEulerPreleapSB_TC{
	public:
//		ApproxSBPostleap_TC();
		ApproxSBPostleap_TC(double eps, double w, vector<SimpleSpecies*>& sp, vector<Reaction*>& rxn, Preleap_TC& ptc);
		virtual ~ApproxSBPostleap_TC();
		virtual void getNewTau(double& tau);
	protected:
//		double eps;
		double w;
		bool preCalc;
		Preleap_TC& ptc;
		double* currRate;
		vector<int>* spInRxn; 	// spInRxn[sp.size()][#rxns sp involved in]
		vector<double>* stoich; // stoich[sp.size()][#rxns sp involved in]
	private:
		vector<SimpleSpecies*>& sp;
		vector<Reaction*>& rxn;
	};
}

#endif /* APPROXPL_TC_HH_ */
