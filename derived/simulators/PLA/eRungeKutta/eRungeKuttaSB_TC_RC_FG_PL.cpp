/*
 * eRungeKuttaSB_TC_RC_FG_PL.cpp
 *
 *  Created on: May 19, 2011
 *      Author: Leonard Harris
 */

#include "eRungeKutta.hh"

using namespace std;
using namespace MoMMA;

eRungeKuttaSB_TC_RC_FG_PL::eRungeKuttaSB_TC_RC_FG_PL(ButcherTableau bt, double eps, double approx1, double gg1, double p,
		double pp, double q, double w, vector<SimpleSpecies*>& sp, vector<Reaction*>& rxn, Preleap_TC& ptc)
		: eRungeKuttaSB_TC_FG_PL(bt,eps,p,pp,q,w,sp,rxn,ptc){
	if (MoMMA::debug)
		cout << "eRungeKuttaSB_TC_RC_FG_PL constructor called." << endl;
	this->rc = new eRK_RC(approx1,gg1);
}

eRungeKuttaSB_TC_RC_FG_PL::eRungeKuttaSB_TC_RC_FG_PL(ButcherTableau bt, double eps, double approx1, double gg1, double p,
		double pp, double q, double w, vector<SimpleSpecies*>& sp, vector<Reaction*>& rxn, Preleap_TC& ptc, bool round)
		: eRungeKuttaSB_TC_FG_PL(bt,eps,p,pp,q,w,sp,rxn,ptc,round){
	if (MoMMA::debug)
		cout << "eRungeKuttaSB_TC_RC_FG_PL constructor called." << endl;
	this->rc = new eRK_RC(approx1,gg1);
}

eRungeKuttaSB_TC_RC_FG_PL::eRungeKuttaSB_TC_RC_FG_PL(const eRungeKuttaSB_TC_RC_FG_PL& tc_rc_fg_pl)
		: eRungeKuttaSB_TC_FG_PL(tc_rc_fg_pl){
	if (MoMMA::debug)
		cout << "eRungeKuttaSB_TC_RC_FG_PL copy constructor called." << endl;
	this->rc = new eRK_RC(*tc_rc_fg_pl.rc);
}

eRungeKuttaSB_TC_RC_FG_PL::~eRungeKuttaSB_TC_RC_FG_PL(){
	if (MoMMA::debug)
		cout << "eRungeKuttaSB_TC_RC_FG_PL destructor called." << endl;
	delete this->rc;
}

void eRungeKuttaSB_TC_RC_FG_PL::classifyRxns(vector<int>& classif, double tau, bool initial){
	// a_eff[] elements have already been calculated in getNewTau()
	this->rc->classifyRxns(classif,tau,initial,this->aCalc->a_eff);
}
