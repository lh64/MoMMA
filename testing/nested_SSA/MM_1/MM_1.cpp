/*
 * MM_1.cpp
 *
 *  Created on: Nov 24, 2010
 *      Author: Leonard Harris
 */

#include <ctime>

#include "MM_1.hh"
#include "../../../borrowed/primitiveData.hh"
#include "../../../derived/trackers/doublePtrTracker.hh"
#include "../../../derived/trackers/doublePtrVectorTracker.hh"
#include "../../../derived/translators/nullTranslator.hh"
#include "../../../derived/translators/trivialTranslator.hh"
#include "../../../derived/simulators/gillespieDM.hh"
#include "../../../derived/simulators/simpleEuler.hh"
#include "../../../derived/conductors/serialConductorType1.hh"

using namespace std;
using namespace MoMMA;

MM_1::MM_1(){

	time_t start, end; // For efficiency testing

	// Models
	double volume = 1.66e-21; // L
	double E_tot = 1.0;		  // M
	double S_tot = 10.0;	  // M

	FastModel_MM1* fastModel = new FastModel_MM1(E_tot,S_tot,volume,true);
	SlowModel_MM1* slowModel = new SlowModel_MM1(E_tot,volume,true);
	FullModel_MM1* fullModel = new FullModel_MM1(E_tot,S_tot,volume,true);

	GillespieDM* full_gillesp = new GillespieDM(fullModel->species,fullModel->reaction);
	full_gillesp->addOutputFile("testing/nested_SSA/MM_1/output/full.txt",1e-1);
	full_gillesp->setSeed(15);
/*	start = time(NULL);
	full_gillesp->run(30.0);
	end = time(NULL);
	cout << "Elapsed time = " << (end-start) << " seconds." << endl;
	exit(1);
*/
	SimpleEuler* full_euler = new SimpleEuler(fullModel->species,fullModel->reaction,1e-6);
	full_euler->addOutputFile("testing/nested_SSA/MM_1/output/full_euler.txt",1e-1);
//	full_euler->run(30.0);

	// *** Create modules ***
	string name; bool equil;
	Module* FAST = new Module(name="FAST",equil=false);
	Module* SLOW = new Module(name="SLOW",equil=false);

	// *** Create simulators ***

	// FAST
	GillespieDM* fast_gillesp = new GillespieDM(fastModel->species,fastModel->reaction);
//	fast_gillesp->addOutputFile("testing/nested_SSA/MM_1/output/fast.txt",1e-6);
//	fast_gillesp->setOutputInterval(1e-6);
	fast_gillesp->setSeed(5);
//	fast_gillesp->run(1e-4);
	//
	FastGillespie_MM1* fast_sim = new FastGillespie_MM1(fast_gillesp);
//	fast_sim->run(1e-4);
	//
	FAST->addSimulator(fast_sim);
	FAST->addOutputFile("testing/nested_SSA/MM_1/output/fast.txt");

	// SLOW
	GillespieDM* slow_gillesp = new GillespieDM(slowModel->species,slowModel->reaction);
//	slow_gillesp->addOutputFile("testing/nested_SSA/MM_1/output/slow.txt",10.0);
//	slow_gillesp->setOutputInterval(10.0);
	slow_gillesp->setSeed(10);
//	slow_gillesp->run(1e3);
	//
	SlowGillespie_MM1* slow_sim = new SlowGillespie_MM1(slow_gillesp,2e-4);
//	slow_sim->run(1e3);
	//
	SLOW->addSimulator(slow_sim);
	SLOW->addOutputFile("testing/nested_SSA/MM_1/output/slow.txt");

	// *** Create variables and parameters ***
	double eps;
	// FAST
	DoublePtrTracker* f_fast_var = new DoublePtrTracker(new DoublePtrData("f_data",&fast_sim->f),eps=0.0);
	//
	DoublePtrTracker* E_fast_var =
			new DoublePtrTracker(new DoublePtrData("E_data",&fast_gillesp->species.at(0)->population),eps=INFINITY);
	DoublePtrTracker* S_fast_var =
			new DoublePtrTracker(new DoublePtrData("S_data",&fast_gillesp->species.at(1)->population),eps=INFINITY);
	DoublePtrTracker* ES_fast_var =
			new DoublePtrTracker(new DoublePtrData("ES_data",&fast_gillesp->species.at(2)->population),eps=INFINITY);
	//
	DoublePtrVectorData* P_fast_data = new DoublePtrVectorData("P_data",2);
	P_fast_data->setDoublePtr(&fast_sim->P,0);
	P_fast_data->setDoublePtr(&fast_sim->dP,1);
	FastTranslator_MM1* P_fast_par = new FastTranslator_MM1(P_fast_data);

	// SLOW
	DoublePtrTracker* P_slow_var = new DoublePtrTracker(new DoublePtrData("P_data",slow_sim->P),eps=0.0);
	//
	SlowTranslator_MM1* f_slow_par = new SlowTranslator_MM1(new DoublePtrData("f_data",slow_sim->kcat),*slow_sim->kcat);
	//
	NullTranslator* E_slow_par  = new NullTranslator("E_data");
	NullTranslator* S_slow_par  = new NullTranslator("S_data");
	NullTranslator* ES_slow_par = new NullTranslator("ES_data");

	// *** Establish links between modules ***
	Module::addLink(FAST,f_fast_var,SLOW,f_slow_par); cout << endl; // f_fast -> f_slow
	Module::addLink(FAST,E_fast_var,SLOW,E_slow_par); cout << endl;	// E_fast -> E_slow
	Module::addLink(FAST,S_fast_var,SLOW,S_slow_par); cout << endl;	// S_fast -> S_slow
	Module::addLink(FAST,ES_fast_var,SLOW,ES_slow_par); cout << endl;	// ES_fast -> ES_slow
	//
	Module::addLink(SLOW,P_slow_var,FAST,P_fast_par); cout << endl; // P_slow -> P_fast

	// *** Define level hierarchy ***
	vector< vector<Module*> > level;
	level.push_back( vector<Module*>() ); // Level 1
	level.at(0).push_back(SLOW);
	level.push_back( vector<Module*>() ); // Level 2
	level.at(1).push_back(FAST);

	// *** Load the Conductor and start simulating ***
	cout << "BEGIN SIMULATION" << endl << "----------------" << endl << endl;
	double sFactor = 1.0; // <= 1 (sample factor)
	double tFactor = 1.0; // >= 1 (tau factor)
	SerialConductorType1 maestro1(level,sFactor,tFactor);
	maestro1.setOutputInterval(0.1);
	double startTime = 0.0;
	double endTime = 30.0;
	double initialTau = 1e-4;
	start = time(NULL);
	maestro1.go(startTime,endTime,initialTau);
	end = time(NULL);

	for (unsigned int i=0;i < level.size();i++){
		for (unsigned int j=0;j < level.at(i).size();j++){
			level.at(i).at(j)->updateTimescale();
			cout << level.at(i).at(j)->getName() << ": " << level.at(i).at(j)->getTimescale() << endl;
		}
	}
	cout << endl;
	cout << "Elapsed time = " << (end-start) << " seconds." << endl;
}
