/*
 * PhoQ_PhoP.cpp
 *
 *  Created on: Aug 22, 2010
 *      Author: Leonard Harris
 */

#include "PhoQ_PhoP.hh"

#include <string>
#include <ctime>
#include <fstream>

#include "../../derived/trackers/doublePtrTracker.hh"
#include "../../derived/translators/trivialTranslator.hh"
#include "../../derived/conductors/serialConductorType1.hh"

#include "../../derived/simulators/gillespieDM.hh"
#include "../../derived/simulators/simpleEuler.hh"

using namespace std;
using namespace MoMMA;

PhoQ_PhoP::PhoQ_PhoP(){

	cout << "**PhoQ/PhoP Multiscale Model**" << endl << endl;

	// Autoregulation
	// 0) * -> RR; 				rate = B
	// 1) RRp -> RRp + RR; 		rate = A*[RRp]/(D+[RRp])
	// 2) RR -> *; 				rate = 1/tau*[RR]
	// 3) RRp -> *; 			rate = 1/tau*[RRp]
	//
	// Phosphorylation
	// 4) HK -> HKp;			rate = kf*[HK]
	// 5) HKp -> HK; 			rate = kr*[HKp]
	// 6) RR + HKp -> RRp + HK; rate = kt*[RR]*[HKp]/(Kmt+[RR])
	// 7) RRp + HK -> RR + HK; 	rate = kp*[RRp]*[HK]/(Kmp+[RRp])

	// *** Create modules ***
	string name; bool equil;
	Module* REG = new Module(name="REG",equil=false);	//W->setTimescale(4.0);
	Module* PHO = new Module(name="PHO",equil=false);	//M1->setTimescale(3.0);

	// *** Create simulators ***
	// REG
	AutoregModel* reg_model = new AutoregModel(1.66e-23); cout << endl;
	//
	GillespieDM* reg_gillesp = new GillespieDM(reg_model->species,reg_model->reaction);
//	reg_gillesp->addOutputFile("testing/PhoQ_PhoP/reg.txt",0.01);
//	reg_gillesp->setOutputInterval(0.1);
	reg_gillesp->setSeed(5);
	//
	SimpleEuler* reg_euler = new SimpleEuler(reg_model->species,reg_model->reaction,1e-8);
	//
//	PhoQ_PhoP_Gillespie* reg_sim = new PhoQ_PhoP_Gillespie(reg_gillesp);
	PhoQ_PhoP_Euler* reg_sim = new PhoQ_PhoP_Euler(reg_euler);
	//
	REG->addSimulator(reg_sim);
	REG->addOutputFile("testing/PhoQ_PhoP/reg.txt");

	// PHO
	PhosphoModel* pho_model = new PhosphoModel(1.66e-23); cout << endl;
	//
	GillespieDM* pho_gillesp = new GillespieDM(pho_model->species,pho_model->reaction);
//	pho_gillesp->addOutputFile("testing/PhoQ_PhoP/pho.txt",0.01);
//	pho_gillesp->setOutputInterval(0.1);
	pho_gillesp->setSeed(10);
	//
	SimpleEuler* pho_euler = new SimpleEuler(pho_model->species,pho_model->reaction,1e-8);
	//
//	PhoQ_PhoP_Gillespie* pho_sim = new PhoQ_PhoP_Gillespie(pho_gillesp);
	PhoQ_PhoP_Euler* pho_sim = new PhoQ_PhoP_Euler(pho_euler);
	//
	PHO->addSimulator(pho_sim);
	PHO->addOutputFile("testing/PhoQ_PhoP/pho.txt");

	// *** Create outgoing and incoming data elements ***
	double eps = 0.01; // Tracker epsilon
	// REG
	//
	// variables
//	double* reg_RR  = &reg_sim->gillespSim->species.at(0)->population;
//	double* reg_RRp = &reg_sim->gillespSim->species.at(1)->population;
	//
	double* reg_RR  = &reg_sim->eulerSim->species.at(0)->population;
	double* reg_RRp = &reg_sim->eulerSim->species.at(1)->population;
	//
	DoublePtrData* reg_RR_out  = new DoublePtrData("RR_data", reg_RR);
	DoublePtrData* reg_RRp_out = new DoublePtrData("RRp_data",reg_RRp);
	DoublePtrTracker* reg_RR_var  = new DoublePtrTracker(reg_RR_out, eps);
	DoublePtrTracker* reg_RRp_var = new DoublePtrTracker(reg_RRp_out,eps);
	//
	// parameters
	double* reg_RR_init  = &reg_sim->RR_init;
	double* reg_RRp_init = &reg_sim->RRp_init;
	DoublePtrData* reg_RR_in  = new DoublePtrData("RR_data", reg_RR_init);
	DoublePtrData* reg_RRp_in = new DoublePtrData("RRp_data",reg_RRp_init);
	TrivialTranslator* reg_RR_par  = new TrivialTranslator(reg_RR_in);
	TrivialTranslator* reg_RRp_par = new TrivialTranslator(reg_RRp_in);
	//
	// PHO
	//
	// variables
//	double* pho_RR  = &pho_sim->gillespSim->species.at(0)->population;
//	double* pho_RRp = &pho_sim->gillespSim->species.at(1)->population;
	//
	double* pho_RR  = &pho_sim->eulerSim->species.at(0)->population;
	double* pho_RRp = &pho_sim->eulerSim->species.at(1)->population;
	//
	DoublePtrData* pho_RR_out  = new DoublePtrData("RR_data", pho_RR);
	DoublePtrData* pho_RRp_out = new DoublePtrData("RRp_data",pho_RRp);
	DoublePtrTracker* pho_RR_var  = new DoublePtrTracker(pho_RR_out, eps);
	DoublePtrTracker* pho_RRp_var = new DoublePtrTracker(pho_RRp_out,eps);
	//
	// parameters
	double* pho_RR_init   = &pho_sim->RR_init;
	double* pho_RRp_init  = &pho_sim->RRp_init;
	DoublePtrData* pho_RR_in  = new DoublePtrData("RR_data", pho_RR_init);
	DoublePtrData* pho_RRp_in = new DoublePtrData("RRp_data",pho_RRp_init);
	TrivialTranslator* pho_RR_par  = new TrivialTranslator(pho_RR_in);
	TrivialTranslator* pho_RRp_par = new TrivialTranslator(pho_RRp_in);

	// *** Establish links between modules ***
	Module::addLink(REG,reg_RR_var,PHO,pho_RR_par);   cout << endl; // RR_reg -> RR_pho
	Module::addLink(REG,reg_RRp_var,PHO,pho_RRp_par); cout << endl;	// RRp_reg -> RRp_pho
	Module::addLink(PHO,pho_RR_var,REG,reg_RR_par);   cout << endl; // RR_reg -> RR_pho
	Module::addLink(PHO,pho_RRp_var,REG,reg_RRp_par); cout << endl;	// RRp_reg -> RRp_pho

	// Print neighbors
	Module* module[2] = {REG,PHO};
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
	level.at(0).push_back(REG);
	level.push_back( vector<Module*>() ); // Level 2
	level.at(1).push_back(PHO);
///*
	// *** Load the Conductor and start simulating ***
	cout << "BEGIN SIMULATION" << endl << "----------------" << endl << endl;
	double sFactor = 1.0; // <= 1 (sample factor)
	double tFactor = 1.0; // >= 1 (tau factor)
	SerialConductorType1 maestro1(level,sFactor,tFactor);
	maestro1.setOutputInterval(0.01);
	double startTime = 0.0;
	double endTime = 5.0;
	double initialTau = 1e-8;
	maestro1.go(startTime,endTime,initialTau);

	for (unsigned int i=0;i < level.size();i++){
		for (unsigned int j=0;j < level.at(i).size();j++){
			level.at(i).at(j)->updateTimescale();
			cout << level.at(i).at(j)->getName() << ": " << level.at(i).at(j)->getTimescale() << endl;
		}
	}
//*/

	//////////////////////////////////////////////////////////////////////////

//	FullModel* FULL = new FullModel(1.66e-23); cout << endl;
//	GillespieDM* full_sim = new GillespieDM(FULL->species,FULL->reaction);
//	SimpleEuler* full_sim = new SimpleEuler(FULL->species,FULL->reaction,1e-7);

/*	vector<vector<Reaction*> > full_dependency(8,vector<Reaction*>());
	//
	// 0: 2 6
	// 1: 2 6
	// 2: 2 6
	// 3: 1 3 7
	// 4: 4 5 6 7
	// 5: 4 5 6 7
	// 6: 1 2 3 4 5 6 7
	// 7: 1 2 3 6 7
	//
	full_dependency.at(0).push_back(FULL->reaction.at(2)); full_dependency.at(0).push_back(FULL->reaction.at(6));
	//
	full_dependency.at(1).push_back(FULL->reaction.at(2)); full_dependency.at(1).push_back(FULL->reaction.at(6));
	//
	full_dependency.at(2).push_back(FULL->reaction.at(2)); full_dependency.at(2).push_back(FULL->reaction.at(6));
	//
	full_dependency.at(3).push_back(FULL->reaction.at(1)); full_dependency.at(3).push_back(FULL->reaction.at(3));
		full_dependency.at(3).push_back(FULL->reaction.at(7));
	//
	full_dependency.at(4).push_back(FULL->reaction.at(4)); full_dependency.at(4).push_back(FULL->reaction.at(5));
		full_dependency.at(4).push_back(FULL->reaction.at(6)); full_dependency.at(4).push_back(FULL->reaction.at(7));
	//
	full_dependency.at(5).push_back(FULL->reaction.at(4)); full_dependency.at(5).push_back(FULL->reaction.at(5));
		full_dependency.at(5).push_back(FULL->reaction.at(6)); full_dependency.at(5).push_back(FULL->reaction.at(7));
	//
	full_dependency.at(6).push_back(FULL->reaction.at(1)); full_dependency.at(6).push_back(FULL->reaction.at(2));
		full_dependency.at(6).push_back(FULL->reaction.at(3)); full_dependency.at(6).push_back(FULL->reaction.at(4));
			full_dependency.at(6).push_back(FULL->reaction.at(5)); full_dependency.at(6).push_back(FULL->reaction.at(6));
				full_dependency.at(6).push_back(FULL->reaction.at(7));
	//
	full_dependency.at(7).push_back(FULL->reaction.at(1)); full_dependency.at(7).push_back(FULL->reaction.at(2));
		full_dependency.at(7).push_back(FULL->reaction.at(3)); full_dependency.at(7).push_back(FULL->reaction.at(6));
			full_dependency.at(7).push_back(FULL->reaction.at(7));

//	full_sim->addDependencyMap(full_dependency);
*/
//	full_sim->addOutputFile("testing/PhoQ_PhoP/","full.txt",0.01);

//	time_t start;
//	time_t end;


//	start = time(NULL);
//	full_sim->run(5.0);
//	end = time(NULL);
//	cout << endl << (end-start) << " seconds" << endl << endl;


}
