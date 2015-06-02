/*
 * trackTest.cpp
 *
 *  Created on: Apr 19, 2010
 *      Author: Leonard Harris
 */

#include <string>
#include <time.h>

#include "trackTest.hh"
#include "trackSimulator.hh"
#include "trackTranslator.hh"

#include "../../MoMMA.hh"

#include "../../derived/trackers/intPtrTracker.hh"
#include "../../derived/trackers/doublePtrTracker.hh"

#include "../../borrowed/primitiveData.hh"

using namespace std;
using namespace MoMMA;

TrackTest::TrackTest(){
	cout << "***TRACKING TEST***" << endl << endl;

	// Create empty modules
	string name;
	bool equil;
	Module* m1 = new Module(name="m1",equil=false);
	Module* m2 = new Module(name="m2",equil=false);

	// Provide simulators and load them into the modules
	double v_12 = 100.0, N1 = 1.0, M1 = 5e5, L1 = 9.0; 		// Variable in sim1
	double v_21 = 100.0, N2 = 10.0, M2 = 5e5, L2 = 90.0;	// Variable in sim2
	double p_21 = N1 + v_21/(M1 + v_21)*L1;					// Parameter in sim1 informed by variable in sim2
	double p_12 = N2 + v_12/(M2 + v_12)*L2;					// Parameter in sim2 informed by variable in sim1
	cout << "p_21 = " << p_21 << "\t" << "p_12 = " << p_12 << endl << endl;
	TrackSimulator* sim1 = new TrackSimulator(v_12,p_21);
	TrackSimulator* sim2 = new TrackSimulator(v_21,p_12);
	m1->addSimulator(sim1);
	m2->addSimulator(sim2);

	// Create data elements pointing to variables and parameters in the simulators
	DoublePtrData* ptr_v_12 = new DoublePtrData("m1->m2",&sim1->v); // v_12 -> p_12
	DoublePtrData* ptr_p_21 = new DoublePtrData("m2->m1",&sim1->p);
	DoublePtrData* ptr_v_21 = new DoublePtrData("m2->m1",&sim2->v); // v_21 -> p_21
	DoublePtrData* ptr_p_12 = new DoublePtrData("m1->m2",&sim2->p);

	// Define trackers for all variables
	double eps1,eps2;
	DoublePtrTracker* track1 = new DoublePtrTracker(ptr_v_12,eps1=0.1);
	DoublePtrTracker* track2 = new DoublePtrTracker(ptr_v_21,eps2=0.1);

	// Define translators for all parameters
	TrackTranslator* tran1 = new TrackTranslator(ptr_p_21,N1,M1,L1);
	TrackTranslator* tran2 = new TrackTranslator(ptr_p_12,N2,M2,L2);

	// Make m1 and m2 neighbors
	map<Tracker*,Translator*> m1_to_m2;
	m1_to_m2.insert( pair<Tracker*,Translator*>(track1,tran2) );
	map<Tracker*,Translator*> m2_to_m1;
	m2_to_m1.insert( pair<Tracker*,Translator*>(track2,tran1) );
	Module::makeNeighbors(m1,m2,m1_to_m2,m2_to_m1);
	cout << endl;

	// Define equilibrators
	// ...
///*
	// Some more modules
	Module* m3 = new Module(name="m3");
	Module* m4 = new Module(name="m4");
	Module* m5 = new Module(name="m5",equil=true);
	Module* m6 = new Module(name="m6",equil=true);
	Module* m7 = new Module(name="m7",equil=false);

	map<Tracker*,Translator*> null;
	Module::makeNeighbors(m2,m3,null,null);
	Module::makeNeighbors(m2,m4,null,null);
	Module::makeNeighbors(m3,m5,null,null);
	Module::makeNeighbors(m3,m6,null,null);
	Module::makeNeighbors(m4,m7,null,null);
//*/
	// --------------------

	// Define levels
	vector< vector<Module*> > level;

	// Level 1
	level.push_back( vector<Module*>() );
	level.at(0).push_back(m1); // top-level parent

	// Level 2
	level.push_back( vector<Module*>() );
	level.at(1).push_back(m2);
///*
	// Level 3
	level.push_back( vector<Module*>() );
	level.at(2).push_back(m3);
	level.at(2).push_back(m4);

	// Level 4
	level.push_back( vector<Module*>() );
	level.at(3).push_back(m5);
	level.at(3).push_back(m6);
	level.at(3).push_back(m7);
//*/
	// Find starting level
	int startLevel = 0;
	bool foundLevel = false;
	bool foundNeq;
	unsigned int i=1,j;
	while (i < level.size() && !foundLevel){
		j=0;
		foundNeq = false;
		foundLevel = true;
		while (j < level.at(i).size() && !foundNeq){
			if (!level.at(i).at(j)->isEquilibrated()){
				startLevel = i;
				foundNeq = true;
				foundLevel = false;
			}
			j++;
		}
		i++;
	}

	// Print levels
//	cout << endl;
	cout << "Levels = " << level.size() << endl;
	cout << "Start level = " << (startLevel+1) << endl;
	cout << "-----" << endl;
	string eq;
	for (unsigned int i=0;i < level.size();i++){
		cout << "Level " << (i+1) << ":";
		for (unsigned int j=0;j < level.at(i).size();j++){
			if (level.at(i).at(j)->isEquilibrated()){
				eq = "_(eq )";
			}
			else{
				eq = "_(neq)";
			}
			cout << "\t" + level.at(i).at(j)->getName() + eq;
		}
		cout << endl;
	}

	// Run simulations

	double globalTime = 0.0;
	double endTime = 1.0;

	cout << endl << "Initial values:" << endl;
	cout << "v_12: " << *ptr_v_12->getDoublePtr() << "\t"
		 << "v_21: " << *ptr_v_21->getDoublePtr() << endl << endl;

	double t1 = 0.0, t2 = 0.0;
	double tau1 = INFINITY, tau2 = INFINITY;
	double dt1 = 1e-6, dt2 = 1e-6;

	while (globalTime < endTime){
//	for (int n=0;n<3;n++){

		// Start at lowest level with a non-equilibrated module
		for (int i = startLevel;i >= 0;i--){
			for (unsigned int j=0;j < level.at(i).size();j++){
				if (!level.at(i).at(j)->isEquilibrated()){
					cout << "Run module " << level.at(i).at(j)->getName() << endl;
				}
			}

		}

		globalTime = endTime;
/*
		// Start with child (m2) since equilibrium metrics not defined
		cout << "--------------------------------------" << endl;
		cout << "Running m2 simulation:" << endl;
		cout << "tau2 = " << tau2 << "\t" << "dt2 = " << dt2 << endl;
		t2 += m2->runSimulation(tau2,dt2);
		cout << *ptr_v_12->getDoublePtr() << "\t" << *ptr_v_21->getDoublePtr() << endl;
		cout << "t2 = " << t2 << endl;
		m2->monitor->resetAll();
		// Set run and sample times
		tau2 = 10.0*(t2-globalTime);
		dt2 = tau2/1e6;

		// Catch parent (m1) up with child using OLD parameter values
		tau1 = t2-globalTime;
		dt1 = tau1/1e6;
		cout << "Running m1 simulation:" << endl;
		cout << "tau1 = " << tau1 << "\t" << "dt1 = " << dt1 << endl;
		t1 += m1->runSimulation(tau1,dt1);
		cout << *ptr_v_12->getDoublePtr() << "\t" << *ptr_v_21->getDoublePtr() << endl;
		cout << "t1 = " << t1 << endl;

		// Check to make sure v1 hasn't changed significantly, negating the results from the m2 simulation
		if (m1->monitor->anyExceeded()){
			cout << "***v1 changed significantly, do something!***" << endl;
			exit(1);
		}
		else{
			m1->monitor->resetAll();
		}

		// Pass information from m2 to m1 AND vice versa
//		m2->comm->call(m1);
//		m1->comm->call(m2);

		// Update global time
		globalTime = t1;
		t2 = globalTime;
		cout << "Global time = " << globalTime << endl;
*/
	}
	cout << "  *****DONE*****" << endl;



/*	cout << endl;
	cout << *ptr_v1->getIntPtr() << endl;
	while (*ptr_v1->getIntPtr() < 1000){
		m1->runSimulation( (min(totalSteps,(1000-*ptr_v1->getIntPtr()) / *ptr_p1->getIntPtr())), sampleSteps );
		cout << *ptr_v1->getIntPtr() << endl;
		if (m1->monitor->anyExceeded()){ m1->monitor->resetLast(); }
	}
	cout << "  *****DONE*****" << endl;

	cout << endl;
	cout << *ptr_v2->getIntPtr() << endl;
	while (*ptr_v2->getIntPtr() < 1000){
		m2->runSimulation( ( min(totalSteps,(1000-*ptr_v2->getIntPtr()) / *ptr_p2->getIntPtr()) ), sampleSteps );
		cout << *ptr_v2->getIntPtr() << endl;
		if (m2->monitor->anyExceeded()){ m2->monitor->resetLast(); }
	}
	cout << "  *****DONE*****" << endl;
*/

//	cout << *ptr_v1->getIntPtr() << "\t\t" << *ptr_v2->getIntPtr() << endl;
//	while (*ptr_v1->getIntPtr() < 1000){
//		m1->sim->run(sampleSteps);
//		m2->sim->run(sampleSteps);
		//m1->runSimulation(min(totalSteps,1000-v1),sampleSteps);
		//m2->runSimulation(min(totalSteps,1000-v2),sampleSteps);
//		cout << *ptr_v1->getIntPtr() << "\t\t" << *ptr_v2->getIntPtr() << endl;
//		cout << *ptr_v1->getIntPtr() << " (" << xt->delta() << ")\t\t" << *ptr_v2->getIntPtr() << " (" << yt->delta() << ")" << endl;
//		if (mod->monitor->exceeded()){
//			mod->monitor->resetLast();
//		}
//	}
//	cout << "  *****DONE*****" << endl;


}








