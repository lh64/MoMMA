/*
 * commTest.cpp
 *
 *  Created on: Feb 12, 2010
 *      Author: Leonard Harris
 */

#include <iostream>
#include <exception>
#include <string>
#include <time.h>
#include <math.h>
#include <vector>
#include <map>

#include "commTest.hh"

#include "../../borrowed/primitiveData.hh"
#include "../../borrowed/util/util.hh"

#include "../../derived/conductors/serialConductorType1.hh"
#include "../../derived/conductors/serialConductorType2.hh"
#include "../../derived/conductors/serialConductorType3.hh"

#include "commSimulator.hh"
#include "commTranslator.hh"
#include "commTracker.hh"
#include "stringData.hh"

using namespace std;
using namespace MoMMA;

CommTest::CommTest(){

	cout << "***Communication Test***\n\n";

	// *** Create modules ***
	string name;
	bool equil;
	Module* W    = new Module(name="W",equil=false);	W->setTimescale(4.0);
	Module* M1   = new Module(name="M1",equil=true);	M1->setTimescale(3.0);
	Module* M2   = new Module(name="M2",equil=false);	M2->setTimescale(3.0);
	Module* M3   = new Module(name="M3",equil=false);	M3->setTimescale(3.0);
	Module* m11  = new Module(name="m11",equil=true);	m11->setTimescale(2.0);
	Module* m12  = new Module(name="m12",equil=false);	m12->setTimescale(2.0);
	Module* m13  = new Module(name="m13",equil=false);	m13->setTimescale(2.0);
	Module* m21  = new Module(name="m21",equil=false);	m21->setTimescale(2.0);
	Module* m22  = new Module(name="m22",equil=false);	m22->setTimescale(2.0);
	Module* m23  = new Module(name="m23",equil=false);	m23->setTimescale(2.0);
	Module* m31  = new Module(name="m31",equil=false);	m31->setTimescale(2.0);
	Module* m32  = new Module(name="m32",equil=false);	m32->setTimescale(2.0);
	Module* m33  = new Module(name="m33",equil=false);	m33->setTimescale(2.0);
	Module* u321 = new Module(name="u321",equil=true);	u321->setTimescale(1.0);

	// *** Create simulators and define outgoing variables ***
	// W
	CommSimulator* W_sim = new CommSimulator("W");
	string* W_var = &W_sim->sim_data;
	W->addSimulator(W_sim);

	// M1
	CommSimulator* M1_sim = new CommSimulator("M1");
	string* M1_var = &M1_sim->sim_data;
	M1->addSimulator(M1_sim);

	// M2
	CommSimulator* M2_sim = new CommSimulator("M2");
	string* M2_var = &M2_sim->sim_data;
	M2->addSimulator(M2_sim);

	// M3
	CommSimulator* M3_sim = new CommSimulator("M3");
	string* M3_var = &M3_sim->sim_data;
	M3->addSimulator(M3_sim);

	// m11
	CommSimulator* m11_sim = new CommSimulator("m11");
	string* m11_var = &m11_sim->sim_data;
	m11->addSimulator(m11_sim);

	// m12
	CommSimulator* m12_sim = new CommSimulator("m12");
//	string* m12_var = &m12_sim->sim_data; //
	m12->addSimulator(m12_sim);

	// m13
	CommSimulator* m13_sim = new CommSimulator("m13");
//	string* m13_var = &m13_sim->sim_data; //
	m13->addSimulator(m13_sim);

	// m21
	CommSimulator* m21_sim = new CommSimulator("m21");
	string* m21_var = &m21_sim->sim_data;
	m21->addSimulator(m21_sim);

	// m22
	CommSimulator* m22_sim = new CommSimulator("m22");
//	string* m22_var = &m22_sim->sim_data; //
	m22->addSimulator(m22_sim);

	// m23
	CommSimulator* m23_sim = new CommSimulator("m23");
	string* m23_var = &m23_sim->sim_data;
	m23->addSimulator(m23_sim);

	// m31
	CommSimulator* m31_sim = new CommSimulator("m31");
//	string* m31_var = &m31_sim->sim_data; //
	m31->addSimulator(m31_sim);

	// m32
	CommSimulator* m32_sim = new CommSimulator("m32");
	string* m32_var = &m32_sim->sim_data;
	m32->addSimulator(m32_sim);

	// m33
	CommSimulator* m33_sim = new CommSimulator("m33");
//	string* m33_var = &m33_sim->sim_data; //
	m33->addSimulator(m33_sim);

	// u321
	CommSimulator* u321_sim = new CommSimulator("u321");
	string* u321_var = &u321_sim->sim_data;
	u321->addSimulator(u321_sim);

	// *** Create trackers and translators for variables and parameters ***
	int maxIter;
	map<CommTracker*,Module*> tracker;
	map<CommTranslator*,Module*> translator;

	// W
	tracker.insert(pair<CommTracker*,Module*>(new CommTracker(new StringPtrData("W->M1",W_var),maxIter=4),W));
	tracker.insert(pair<CommTracker*,Module*>(new CommTracker(new StringPtrData("W->M2",W_var),maxIter=4),W));
	tracker.insert(pair<CommTracker*,Module*>(new CommTracker(new StringPtrData("W->M3",W_var),maxIter=4),W));
	//
	string W_par1 = "";
	string W_par2 = "";
	translator.insert(pair<CommTranslator*,Module*>(new CommTranslator(new StringPtrData("M2->W",&W_par1)),W));
	translator.insert(pair<CommTranslator*,Module*>(new CommTranslator(new StringPtrData("M3->W",&W_par2)),W));

	// M1
	tracker.insert(pair<CommTracker*,Module*>(new CommTracker(new StringPtrData("M1->m11",M1_var),maxIter=3),M1));
	tracker.insert(pair<CommTracker*,Module*>(new CommTracker(new StringPtrData("M1->m12",M1_var),maxIter=3),M1));
	tracker.insert(pair<CommTracker*,Module*>(new CommTracker(new StringPtrData("M1->m13",M1_var),maxIter=3),M1));
	//
	string M1_par1 = "";
	string M1_par2 = "";
	translator.insert(pair<CommTranslator*,Module*>(new CommTranslator(new StringPtrData("W->M1",&M1_par1)),M1));
	translator.insert(pair<CommTranslator*,Module*>(new CommTranslator(new StringPtrData("m11->M1",&M1_par2)),M1));

	// M2
	tracker.insert(pair<CommTracker*,Module*>(new CommTracker(new StringPtrData("M2->W",M2_var),maxIter=3),M2));
	tracker.insert(pair<CommTracker*,Module*>(new CommTracker(new StringPtrData("M2->m21",M2_var),maxIter=3),M2));
	tracker.insert(pair<CommTracker*,Module*>(new CommTracker(new StringPtrData("M2->m22",M2_var),maxIter=3),M2));
	tracker.insert(pair<CommTracker*,Module*>(new CommTracker(new StringPtrData("M2->m23",M2_var),maxIter=3),M2));
	//
	string M2_par1 = "";
	string M2_par2 = "";
	string M2_par3 = "";
	translator.insert(pair<CommTranslator*,Module*>(new CommTranslator(new StringPtrData("W->M2",&M2_par1)),M2));
	translator.insert(pair<CommTranslator*,Module*>(new CommTranslator(new StringPtrData("m21->M2",&M2_par2)),M2));
	translator.insert(pair<CommTranslator*,Module*>(new CommTranslator(new StringPtrData("m23->M2",&M2_par3)),M2));

	// M3
	tracker.insert(pair<CommTracker*,Module*>(new CommTracker(new StringPtrData("M3->W",M3_var),maxIter=3),M3));
	tracker.insert(pair<CommTracker*,Module*>(new CommTracker(new StringPtrData("M3->m31",M3_var),maxIter=3),M3));
	tracker.insert(pair<CommTracker*,Module*>(new CommTracker(new StringPtrData("M3->m32",M3_var),maxIter=3),M3));
	tracker.insert(pair<CommTracker*,Module*>(new CommTracker(new StringPtrData("M3->m33",M3_var),maxIter=3),M3));
	//
	string M3_par1 = "";
	string M3_par2 = "";
	translator.insert(pair<CommTranslator*,Module*>(new CommTranslator(new StringPtrData("W->M3",&M3_par1)),M3));
	translator.insert(pair<CommTranslator*,Module*>(new CommTranslator(new StringPtrData("m32->M3",&M3_par2)),M3));

	// m11
	tracker.insert(pair<CommTracker*,Module*>(new CommTracker(new StringPtrData("m11->M1",m11_var),maxIter=2),m11));
	//
	string m11_par1 = "";
	translator.insert(pair<CommTranslator*,Module*>(new CommTranslator(new StringPtrData("M1->m11",&m11_par1)),m11));

	// m12
	string m12_par1 = "";
	translator.insert(pair<CommTranslator*,Module*>(new CommTranslator(new StringPtrData("M1->m12",&m12_par1)),m12));

	// m13
	string m13_par1 = "";
	translator.insert(pair<CommTranslator*,Module*>(new CommTranslator(new StringPtrData("M1->m13",&m13_par1)),m13));

	// m21
	tracker.insert(pair<CommTracker*,Module*>(new CommTracker(new StringPtrData("m21->M2",m21_var),maxIter=2),m21));
	//
	string m21_par1 = "";
	translator.insert(pair<CommTranslator*,Module*>(new CommTranslator(new StringPtrData("M2->m21",&m21_par1)),m21));

	// m22
	string m22_par1 = "";
	translator.insert(pair<CommTranslator*,Module*>(new CommTranslator(new StringPtrData("M2->m22",&m22_par1)),m22));

	// m23
	tracker.insert(pair<CommTracker*,Module*>(new CommTracker(new StringPtrData("m23->M2",m23_var),maxIter=2),m23));
	//
	string m23_par1 = "";
	translator.insert(pair<CommTranslator*,Module*>(new CommTranslator(new StringPtrData("M2->m23",&m23_par1)),m23));

	// m31
	string m31_par1 = "";
	translator.insert(pair<CommTranslator*,Module*>(new CommTranslator(new StringPtrData("M3->m31",&m31_par1)),m31));

	// m32
	tracker.insert(pair<CommTracker*,Module*>(new CommTracker(new StringPtrData("m32->M3",m32_var),maxIter=2),m32));
	tracker.insert(pair<CommTracker*,Module*>(new CommTracker(new StringPtrData("m32->u321",m32_var),maxIter=2),m32));
	//
	string m32_par1 = "";
	string m32_par2 = "";
	translator.insert(pair<CommTranslator*,Module*>(new CommTranslator(new StringPtrData("M3->m32",&m32_par1)),m32));
	translator.insert(pair<CommTranslator*,Module*>(new CommTranslator(new StringPtrData("u321->m32",&m32_par2)),m32));

	// m33
	string m33_par1 = "";
	translator.insert(pair<CommTranslator*,Module*>(new CommTranslator(new StringPtrData("M3->m33",&m33_par1)),m33));

	// u321
	tracker.insert(pair<CommTracker*,Module*>(new CommTracker(new StringPtrData("u321->m32",u321_var),maxIter=1),u321));
	//
	string u321_par1 = "";
	translator.insert(pair<CommTranslator*,Module*>(new CommTranslator(new StringPtrData("m32->u321",&u321_par1)),u321));

	// *** Establish links between modules ***
	map<CommTracker*,Module*>::iterator trackIter;
	CommTracker* TRACK;
	Module* LOCAL;
	double timescale;
	map<CommTranslator*,Module*>::iterator tranIter;
	CommTranslator* TRAN;
	Module* DEST;
	bool found;
	int nFound = 0;

	for (trackIter = tracker.begin();trackIter != tracker.end();trackIter++){

		TRACK = (*trackIter).first;
		LOCAL = (*trackIter).second;
		if (LOCAL->getName() == "W"){ timescale = 4.0; }
		else if (LOCAL->getName() == "M1" || LOCAL->getName() == "M2" || LOCAL->getName() == "M3"){ timescale = 3.0; }
		else if (LOCAL->getName() == "m11" || LOCAL->getName() == "m12" || LOCAL->getName() == "m13" ||
				 LOCAL->getName() == "m21" || LOCAL->getName() == "m22" || LOCAL->getName() == "m23" ||
				 LOCAL->getName() == "m31" || LOCAL->getName() == "m32" || LOCAL->getName() == "m33"){
			timescale = 2.0;
		}
		else if (LOCAL->getName() == "u321"){ timescale = 1.0; }
		else{
			cout << "ERROR: Don't know which module this is (" << LOCAL->getName() << "). Exiting." << endl;
			exit(1);
		}
		found = false;
		tranIter = translator.begin();
		while (tranIter != translator.end() && !found){
			TRAN = (*tranIter).first;
			DEST = (*tranIter).second;
			if (TRACK->getName().compare(TRAN->getName()) == 0){ // Found it
				found = true;
				nFound++;
				Module::addLink(LOCAL,TRACK,timescale,DEST,TRAN);
				cout << endl;
			}
			tranIter++;
		}
		if (!found){ // Didn't find it
			cout << "ERROR: Couldn't find parameter " << TRACK->getName() << ". Exiting.\n";
			exit(1);
		}
	}
	cout << "# of connections = " << nFound << endl;

	// Print neighbors
	Module* module[14] = {W,M1,M2,M3,m11,m12,m13,m21,m22,m23,m31,m32,m33,u321};
	int nModules = sizeof(module)/sizeof(module[0]);
	map<Module*,int>::iterator neighIter;
	string outInBoth;
	for (int i=0;i < nModules;i++){
		cout << endl << module[i]->getName() << " neighbors:" << endl;
		for (neighIter = module[i]->neighbors.begin();neighIter != module[i]->neighbors.end();neighIter++){
			if ((*neighIter).second == 0){
				outInBoth = "out";
			}
			else if ((*neighIter).second == 1){
				outInBoth = "in";
			}
			else if ((*neighIter).second == 2){
				outInBoth = "both";
			}
			else{
				cout << "Error: Neighbor type " << (*neighIter).second << " unrecognized. Exiting." << endl;
				exit(1);
			}
			cout << "  " << (*neighIter).first->getName() << ", " << outInBoth << endl;
		}
	}
	cout << endl;

	// *** Define level hierarchy ***
	vector< vector<Module*> > level;
	level.push_back( vector<Module*>() ); // Level 1
	level.at(0).push_back(W);
	level.push_back( vector<Module*>() ); // Level 2
	level.at(1).push_back(M1);
	level.at(1).push_back(M2);
	level.at(1).push_back(M3);
	level.push_back( vector<Module*>() ); // Level 3
	level.at(2).push_back(m11);
	level.at(2).push_back(m12);
	level.at(2).push_back(m13);
	level.at(2).push_back(m21);
	level.at(2).push_back(m22);
	level.at(2).push_back(m23);
	level.at(2).push_back(m31);
	level.at(2).push_back(m32);
	level.at(2).push_back(m33);
	level.push_back( vector<Module*>() ); // Level 4
	level.at(3).push_back(u321);

	// *** Load the Conductor and start simulating ***
	cout << "BEGIN SIMULATION" << endl << "----------------" << endl << endl;
	double sFactor = 1.0; // <= 1
	double tFactor = 1.1; // > 1
	SerialConductorType1 maestro1(level,sFactor,tFactor);
//	double startTau = level.at(3).at(0)->getTimescale();
	maestro1.go(0.0,10.0);

	for (unsigned int i=0;i < level.size();i++){
		for (unsigned int j=0;j < level.at(i).size();j++){
			level.at(i).at(j)->updateTimescale();
			cout << level.at(i).at(j)->getName() << ": " << level.at(i).at(j)->getTimescale() << endl;
		}
	}

	// Clean up
	for (int i=0;i < nModules;i++){
		delete module[i];
	}
}

