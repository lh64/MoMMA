/*
 * tauCalcTest.cpp
 *
 *  Created on: Feb 8, 2011
 *      Author: Leonard Harris
 */

#include <cstring>
#include "tauCalcTest.hh"

using namespace std;
using namespace MoMMA;

TauCalcTest::TauCalcTest(){

	// Decaying-Dimerizing rxn set
	// 3 species (S1,S2,S3), 4 reactions
	// -------------------------------
    // 0) S1 -> *		c0 = 1.0   (unitless)
    // 1) 2S1 -> S2		c1 = 0.002
    // 2) S2 -> 2S1 	c2 = 0.5
	// 3) S2 -> S3		c3 = 0.02

	vector<SimpleSpecies*> sp;
	vector<Reaction*> rxn;

	// Parameters
	double c0 = 1.0;
	double c1 = 0.002;
	double c2 = 0.5;
	double c3 = 0.02;
	//
	double X1_init = 2921.0; // molecules
	double X2_init = 22064.0;
	double X3_init = 6771.0;

	// Species
	sp.push_back(new SimpleSpecies("S1",X1_init));
	sp.push_back(new SimpleSpecies("S2",X2_init));
	sp.push_back(new SimpleSpecies("S3",X3_init));

	for (unsigned int i=0;i < sp.size();i++){
		cout << sp[i]->name << ": " << sp[i]->population << endl;
	}
	cout << endl;

	// Reactions
	//
	// 0) S1 -> *
//	RateElementary* re0 = new RateElementary(c0,RateElementary::UNIMOLECULAR);
	rxn.push_back(new ElementaryRxn(c0,sp[0],-1,vector<SimpleSpecies*>(),vector<int>()));

	// 1) 2S1 -> S2
//	RateElementary* re1 = new RateElementary(c1,RateElementary::BIMOLECULAR_AA);
	rxn.push_back(new ElementaryRxn(c1,sp[0],-2,sp[1],1));

	// 2) S2 -> 2S1
//	RateElementary* re2 = new RateElementary(c2,RateElementary::UNIMOLECULAR);
	rxn.push_back(new ElementaryRxn(c2,sp[1],-1,sp[0],2));

	// 3) S2 -> S3
//	RateElementary* re3 = new RateElementary(c3,RateElementary::UNIMOLECULAR);
	rxn.push_back(new ElementaryRxn(c3,sp[1],-1,sp[2],1));

	for (unsigned int i=0;i < rxn.size();i++){
		cout << rxn[i]->toString() << ", rate = " << rxn[i]->getRate() << endl;
	}

	double tau;

	// RB tau-selection
	cout << endl;
	cout << "RB tau-selection:" << endl;
	cout << "----------------" << endl;
	double eps = 0.01;
	fEulerPreleapRB_TC rb_tau(eps,rxn);
	rb_tau.getNewTau(tau);
	cout << "tau = " << tau << endl;

	// SB tau-selection
	cout << endl;
	cout << "SB tau-selection:" << endl;
	cout << "----------------" << endl;
	fEulerPreleapSB_TC sb_tau(eps,sp,rxn);
	sb_tau.getNewTau(tau);
	cout << "tau = " << tau << endl;

	cout << endl;
	double approx1 = 3.0, gg1 = 100.0;
	fEuler_RC rc(approx1,gg1,rxn);
	rb_tau.getNewTau(tau);
	vector<int> classif;
	rc.classifyRxns(classif,tau,true);
	cout << endl;
	for (unsigned int v=0;v < classif.size();v++){
		cout << classif[v] << endl;
	}
	cout << endl;

	fEuler_FG fg(rxn);
	vector<double> k;
	fg.fireRxns(k,classif,tau);
/*	for (unsigned int v=0;v < rxn.size();v++){
		if (classif[v] != RxnClassifier::EXACT_STOCHASTIC){
			cout << "rxn[" << v << "]: ";
			fg.fireRxn(rxn[v],classif[v],tau);
		}
	}
*/
	// Clean up
	for (unsigned int j=0;j < sp.size();j++){
		delete sp[j];
	}
//	delete re0;
//	delete re1;
//	delete re2;
//	delete re3;
	for (unsigned int v=0;v < rxn.size();v++){
		delete rxn[v];
	}

}
