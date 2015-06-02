/*
 * plaTest.cpp
 *
 *  Created on: Feb 4, 2011
 *      Author: Leonard Harris
 */

#include "plaTest.hh"

#include <string>
#include <ctime>
#include <fstream>

#include "../../derived/simulators/gillespieDM.hh"
#include "../../derived/simulators/simpleEuler.hh"

using namespace std;
using namespace MoMMA;

PLATest::PLATest(){

	time_t start, end;

//	DecayDimer DD;
	CaOscillate Ca(1e-21);

	vector<SimpleSpecies*> sp = Ca.sp;
	vector<Reaction*> rxn = Ca.rxn;

	// Set up PLA simulator
	//
	double eps = 0.01; // tc params
	double approx1 = 3.0, gg1 = 100.0; // rc params
	double p = 0.5, pp = 0.8, q = 1.5, w = 0.75; // pl params
	//
//	fEulerPreleapRB_TC fe_ptc(eps,rxn);
	fEulerPreleapSB_TC fe_ptc(eps,sp,rxn);
	fEuler_RC fe_rc(approx1,gg1,rxn);
	fEuler_FG fe_fg(rxn);
//	fEulerRB_TC_PL fe_tc_pl(eps,p,pp,q,w,rxn,fe_ptc);
	fEulerSB_TC_PL fe_tc_pl(eps,p,pp,q,w,sp,rxn,fe_ptc);
	//
	Midpoint_FG mp_fg(sp,rxn);
	Midpoint_RC_FG mp_rc_fg(approx1,gg1,sp,rxn);
	//
	vector<double> beta; beta.resize(4);
	beta[0] = beta[3] = 1.0/6.0;
	beta[1] = beta[2] = 1.0/3.0;
	vector<vector<double> > alpha; alpha.resize(4);
	for (unsigned int i=0;i < 4;i++){
		alpha[i].resize(4,0.0);
	}
	alpha[1][0] = alpha[2][1] = 0.5; alpha[3][2] = 1.0;
	ButcherTableau bt(alpha,beta);
	//
	eRungeKutta_FG erk_fg(bt,sp,rxn);
	eRungeKutta_RC_FG erk_rc_fg(bt,approx1,gg1,sp,rxn);
//	eRungeKuttaRB_FG_PL erk_fg_pl(bt,eps,p,sp,rxn);
	eRungeKuttaSB_FG_PL erk_fg_pl(bt,eps,p,sp,rxn);
//	eRungeKuttaRB_RC_FG_PL erk_rc_fg_pl(bt,eps,p,approx1,gg1,sp,rxn);
	eRungeKuttaSB_RC_FG_PL erk_rc_fg_pl(bt,eps,p,approx1,gg1,sp,rxn);
//	eRungeKuttaRB_TC_FG_PL erk_tc_fg_pl(bt,eps,p,pp,q,w,sp,rxn,fe_ptc);
	eRungeKuttaSB_TC_FG_PL erk_tc_fg_pl(bt,eps,p,pp,q,w,sp,rxn,fe_ptc);
//	eRungeKuttaRB_TC_RC_FG_PL erk_tc_rc_fg_pl(bt,eps,approx1,gg1,p,pp,q,w,sp,rxn,fe_ptc);
	eRungeKuttaSB_TC_RC_FG_PL erk_tc_rc_fg_pl(bt,eps,approx1,gg1,p,pp,q,w,sp,rxn,fe_ptc);
	//
	NegPop_PL neg_pl(p,sp,rxn);
	//
	TauCalculator* tc; RxnClassifier* rc; FiringGenerator* fg; PostleapChecker* pl;
	//
//	tc = &fe_ptc;		   rc = &fe_rc;			  fg = &fe_fg;			 pl = &neg_pl;
//	tc = &fe_ptc; 		   rc = &fe_rc; 		  fg = &erk_fg;	 		 pl = &neg_pl;
//	tc = &fe_ptc; 		   rc = &erk_rc_fg; 	  fg = &erk_rc_fg; 		 pl = &neg_pl;
//	tc = &fe_ptc; 		   rc = &fe_rc; 		  fg = &erk_fg_pl; 	  	 pl = &erk_fg_pl;
//	tc = &fe_ptc; 		   rc = &erk_rc_fg_pl;	  fg = &erk_rc_fg_pl;	 pl = &erk_rc_fg_pl;
//	tc = &erk_tc_fg_pl;    rc = &fe_rc; 		  fg = &erk_tc_fg_pl;	 pl = &erk_tc_fg_pl;
	tc = &erk_tc_rc_fg_pl; rc = &erk_tc_rc_fg_pl; fg = &erk_tc_rc_fg_pl; pl = &erk_tc_rc_fg_pl;
	//
	PLA pla_sim(*tc,*rc,*fg,*pl,sp,rxn);
	//
//	pla_sim.addOutputFile("testing/PLA_Test/pla_pops.txt");
//	pla_sim.addOutputFile("testing/PLA_Test/pla_rates.txt");
//	pla_sim.addOutputFile("testing/PLA_Test/pla_tau.txt");
	pla_sim.setOutputInterval(0.1);
	pla_sim.setSeed(5);

	SimpleEuler euler_sim(sp,rxn,0.001);
//	euler_sim.addOutputFile("testing/PLA_Test/euler.txt",0.1);

	GillespieDM gillesp_sim(sp,rxn);
//	gillesp_sim.addOutputFile("testing/PLA_Test/gillesp.txt",0.1);
///*
	start = time(NULL);
	pla_sim.run(50.0);
//	euler_sim.run(50.0);
//	gillesp_sim.run(50.0);
	end = time(NULL);
	cout << "Elapsed time = " << (end-start) << " seconds." << endl;
//*/
}
