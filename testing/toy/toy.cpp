/*
 * toy.cpp
 *
 *  Created on: Nov 6, 2010
 *      Author: Leonard Harris
 */

#include "toy.hh"

#include <string>
#include <ctime>
#include <fstream>

#include "../../derived/trackers/doublePtrTracker.hh"
#include "../../derived/translators/trivialTranslator.hh"
#include "../../derived/translators/nullTranslator.hh"
#include "../../derived/conductors/serialConductorType1.hh"

#include "../../derived/simulators/gillespieDM.hh"
#include "../../derived/simulators/simpleEuler.hh"

#include "../../model_spec/reactions/bioNetGenRxn.hh"

using namespace std;
using namespace MoMMA;

TOY::TOY(){

	// 3 species (A,B,X), 3 reactions
	// -------------------------------
    // 0) X + A -> X + B	k1 = 0.1 M^-1 s^-1
    // 1) B -> A			k2 = 0.1 s^-1
    // 2) * -> X  			k3 = 2.0 M/s

	vector<SimpleSpecies*> species_full;
	vector<Reaction*> reaction_full;

	// Parameters
	double k1 = 0.1; 	 // 1/(M-s)
	double k2 = 0.1;	 // 1/s
	double k3 = 2.0;	 // M/s
	//
	double A_init = 1e6; // M
	double B_init = 0.0; // M
	double X_init = 1.0; // M

	// Species
	species_full.push_back(new SimpleSpecies("A",A_init));
	species_full.push_back(new SimpleSpecies("B",B_init));
	species_full.push_back(new SimpleSpecies("X",X_init));

	for (unsigned int i=0;i < species_full.size();i++){
		cout << species_full.at(i)->name << ": " << species_full.at(i)->population << endl;
	}
	cout << endl;

	// Reactions

	// 0) X + A -> X + B
//	RateElementary* re0 = new RateElementary(k1,RateElementary::BIMOLECULAR_AB);
	vector<SimpleSpecies*> reactants; reactants.push_back(species_full.at(2)); reactants.push_back(species_full.at(0));
	vector<SimpleSpecies*> products;  products.push_back(species_full.at(2));  products.push_back(species_full.at(1));
//	reaction_full.push_back(new Reaction(reactants,vector<int>(2,-1),products,vector<int>(2,1),re0));
	reaction_full.push_back(new ElementaryRxn(k1,reactants,vector<int>(2,-1),products,vector<int>(2,1)));

	// 1) B -> A
//	RateElementary* re1 = new RateElementary(k2,RateElementary::UNIMOLECULAR);
//	reaction_full.push_back(new Reaction(species_full.at(1),-1,species_full.at(0),1,re1));
	reaction_full.push_back(new ElementaryRxn(k2,species_full.at(1),-1,species_full.at(0),1));

	// 2) * -> X
//	RateElementary* re2 = new RateElementary(k3,RateElementary::SYNTHESIS);
//	reaction_full.push_back(new Reaction(vector<SimpleSpecies*>(),vector<int>(),species_full.at(2),1,re2));
	reaction_full.push_back(new ElementaryRxn(k3,vector<SimpleSpecies*>(),vector<int>(),species_full.at(2),1));

	for (unsigned int i=0;i < reaction_full.size();i++){
		cout << reaction_full.at(i)->toString() << ", rate = " << reaction_full.at(i)->getRate() << endl;
	}

//	SimpleEuler* sim = new SimpleEuler(species,reaction,1e-3);
//	sim->addOutputFile("testing/toy/full.txt",0.5);
//	sim->run(50.0);

	cout << endl << "--------------------------------------------------" << endl << endl;

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// *** Create modules ***
	string name; bool equil;
	Module* MOD_AB = new Module(name="MOD_AB",equil=false);
	Module* MOD_X = new Module(name="MOD_X",equil=false);

	// *** Create simulators ***
	// MOD_AB
	vector<SimpleSpecies*> species_AB;
	species_AB.push_back(new SimpleSpecies("A",A_init));
	species_AB.push_back(new SimpleSpecies("B",B_init));
	species_AB.push_back(new SimpleSpecies("X",X_init));
	//
	vector<Reaction*> reaction_AB;
	vector<SimpleSpecies*> react_AB; react_AB.push_back(species_AB.at(2)); react_AB.push_back(species_AB.at(0));
	vector<SimpleSpecies*> prod_AB;  prod_AB.push_back(species_AB.at(2));  prod_AB.push_back(species_AB.at(1));
//	reaction_AB.push_back(new Reaction(react_AB,vector<int>(2,-1),prod_AB,vector<int>(2,1),re0)); // X + A -> X + B
//	reaction_AB.push_back(new Reaction(species_AB.at(1),-1,species_AB.at(0),1,re1)); // B-> A
	reaction_AB.push_back(new ElementaryRxn(k1,react_AB,vector<int>(2,-1),prod_AB,vector<int>(2,1))); // X + A -> X + B
	reaction_AB.push_back(new ElementaryRxn(k2,species_AB.at(1),-1,species_AB.at(0),1)); // B-> A
	//
	SimpleEuler* euler_AB = new SimpleEuler(species_AB,reaction_AB,1e-3);
//	euler_AB->addOutputFile("testing/toy/toy_AB.txt",1e-3);
	Toy_Euler* sim_AB = new Toy_Euler(euler_AB);
	MOD_AB->addSimulator(sim_AB);
	MOD_AB->addOutputFile("testing/toy/toy_AB.txt");

	cout << MOD_AB->getName() << endl;
	cout << "------" << endl;
	for (unsigned int i=0;i < euler_AB->species.size();i++){
		cout << euler_AB->species.at(i)->name << endl;
	}
	cout << endl;
	for (unsigned int i=0;i < euler_AB->reaction.size();i++){
		cout << euler_AB->reaction.at(i)->toString() << ", rate = " << euler_AB->reaction.at(i)->getRate() << endl;
	}
	cout << endl;

	// MOD_X
	vector<SimpleSpecies*> species_X;
	species_X.push_back(new SimpleSpecies("X",X_init));
	//
	vector<Reaction*> reaction_X;
//	reaction_X.push_back(new Reaction(vector<SimpleSpecies*>(),vector<int>(),species_X.at(0),1,re2));
	reaction_X.push_back(new ElementaryRxn(k3,vector<SimpleSpecies*>(),vector<int>(),species_X.at(0),1));
	//
	SimpleEuler* euler_X = new SimpleEuler(species_X,reaction_X,1e-3);
	MOD_X->addSimulator(euler_X);
	MOD_X->addOutputFile("testing/toy/toy_X.txt");

	cout << MOD_X->getName() << endl;
	cout << "------" << endl;
	for (unsigned int i=0;i < euler_X->species.size();i++){
		cout << euler_X->species.at(i)->name << endl;
	}
	cout << endl;
	for (unsigned int i=0;i < euler_X->reaction.size();i++){
		cout << euler_X->reaction.at(i)->toString() << ", rate = " << euler_X->reaction.at(i)->getRate() << endl;
	}
	cout << endl;

	// *** Create outgoing and incoming data elements ***
	double eps = 0.01; // Tracker epsilon

	// MOD_AB (1 parameter, 2 dummy variables -- for outputting)
	TrivialTranslator* X_par = new TrivialTranslator(new DoublePtrData("X_data",&sim_AB->X_init));
	DoublePtrTracker* A_var = new DoublePtrTracker(new DoublePtrData("A_data",&euler_AB->species.at(0)->population),INFINITY);
	DoublePtrTracker* B_var = new DoublePtrTracker(new DoublePtrData("B_data",&euler_AB->species.at(1)->population),INFINITY);

	// MOD_X (1 variable, 2 null parameters -- for outputting)
	DoublePtrTracker* X_var = new DoublePtrTracker(new DoublePtrData("X_data",&euler_X->species.at(0)->population),eps);
	NullTranslator* A_par = new NullTranslator("A_data");
	NullTranslator* B_par = new NullTranslator("B_data");

	// *** Establish links between modules ***
	Module::addLink(MOD_X,X_var,MOD_AB,X_par); cout << endl; // X_out -> X_in
	Module::addLink(MOD_AB,A_var,MOD_X,A_par); cout << endl; // A_var
	Module::addLink(MOD_AB,B_var,MOD_X,B_par); cout << endl; // B_var

	// Print neighbors
	Module* module[2] = {MOD_AB,MOD_X};
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
	level.at(0).push_back(MOD_AB);
	level.push_back( vector<Module*>() ); // Level 2
	level.at(1).push_back(MOD_X);

	// *** Load the Conductor and start simulating ***
	cout << "BEGIN SIMULATION" << endl << "----------------" << endl << endl;
	double sFactor = 1.0; // <= 1 (sample factor)
	double tFactor = 1.0; // >= 1 (tau factor)
	SerialConductorType1 maestro1(level,sFactor,tFactor);
	maestro1.setOutputInterval(0.5);
	double startTime = 0.0;
	double endTime = 12.0;
	double initialTau = 3.0;
	maestro1.go(startTime,endTime,initialTau);

	for (unsigned int i=0;i < level.size();i++){
		for (unsigned int j=0;j < level.at(i).size();j++){
			level.at(i).at(j)->updateTimescale();
			cout << level.at(i).at(j)->getName() << ": " << level.at(i).at(j)->getTimescale() << endl;
		}
	}

}
