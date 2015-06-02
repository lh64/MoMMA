/*
 * threeLevel.cpp
 *
 *  Created on: Nov 15, 2010
 *      Author: Leonard Harris
 */

#include "threeLevel.hh"
#include "../../../borrowed/primitiveData.hh"
#include "../../../derived/trackers/doublePtrTracker.hh"

using namespace std;
using namespace MoMMA;

ThreeLevel::ThreeLevel(){

	// Models
	SlowModel*   slow_model = new SlowModel(false);
	MediumModel* med_model  = new MediumModel(false);
	FastModel*   fast_model = new FastModel(false);

	// *** Create modules ***
	string name; bool equil;
	Module* SLOW = new Module(name="SLOW",equil=false);
	Module* MED  = new Module(name="MED" ,equil=false);
	Module* FAST = new Module(name="FAST",equil=false);

	// *** Create simulators ***
	// SLOW
	GillespieDM* slow_gillesp = new GillespieDM(slow_model->species,slow_model->reaction);
//	slow_gillesp->addOutputFile("testing/nested_SSA/slow.txt",1e2);
//	slow_gillesp->setOutputInterval(1e2);
	slow_gillesp->setSeed(5);
	//
	vector<unsigned int> slow_index;
	slow_index.push_back(0); // S3
	slow_index.push_back(1); // S6
	Nested_Gillespie* slow_sim = new Nested_Gillespie(slow_gillesp,slow_index,false);
	//
	SLOW->addSimulator(slow_sim);
	SLOW->addOutputFile("testing/nested_SSA/slow.txt");
	//
//	slow_gillesp->run(1e4);
//	slow_sim->run(1e4);

	// MED
	GillespieDM* med_gillesp = new GillespieDM(med_model->species,med_model->reaction);
//	med_gillesp->addOutputFile("testing/nested_SSA/med.txt",1e-6);
//	med_gillesp->setOutputInterval(1e-6);
	med_gillesp->setSeed(10);
	//
	vector<unsigned int> med_index;
	med_index.push_back(0); // S2
	med_index.push_back(1); // S3
	med_index.push_back(2); // S6
	med_index.push_back(3); // S7
	Nested_Gillespie* med_sim = new Nested_Gillespie(med_gillesp,med_index,false);
	//
	MED->addSimulator(med_sim);
	MED->addOutputFile("testing/nested_SSA/med.txt");
	//
//	med_gillesp->run(1e-4);
//	med_gillesp->run(10);
//	med_sim->run(1e-4);

	// FAST
	GillespieDM* fast_gillesp = new GillespieDM(fast_model->species,fast_model->reaction);
//	fast_gillesp->addOutputFile("testing/nested_SSA/fast.txt",1e-12);
	fast_gillesp->setOutputInterval(1e-12);
	fast_gillesp->setSeed(15);
	//
	vector<unsigned int> fast_index;
	fast_index.push_back(1); // S2
	fast_index.push_back(2); // S3
	fast_index.push_back(5); // S6
	fast_index.push_back(6); // S7
	Nested_Gillespie* fast_sim = new Nested_Gillespie(fast_gillesp,fast_index,true);
	//
	FAST->addSimulator(fast_sim);
	FAST->addOutputFile("testing/nested_SSA/fast.txt");
	//
//	fast_gillesp->run(1e-10);
//	fast_gillesp->run(10);
	fast_sim->run(1e-10);
	cout << endl;
	for (unsigned int i=0;i < fast_sim->timecourse[0].size();i++){
		for (unsigned int j=0;j < fast_sim->timecourse.size();j++){
			cout << fast_sim->timecourse[j][i] << "\t";
		}
		cout << endl;
	}

	// *** Create parameters ***
	// SLOW
	double* slow_S3_init = &slow_sim->X_init.find(0)->second;
	double* slow_S6_init = &slow_sim->X_init.find(1)->second;
	DoublePtrData* slow_S3_incoming = new DoublePtrData("S3_data",slow_S3_init);
	DoublePtrData* slow_S6_incoming = new DoublePtrData("S6_data",slow_S6_init);
//	TrivialTranslator* slow_S3_par = new TrivialTranslator(reg_RR_in);
//	TrivialTranslator* slow_S3_par = new TrivialTranslator(reg_RRp_in);

	// MED
	double* med_S2_init = &med_sim->X_init.find(0)->second;
	double* med_S3_init = &med_sim->X_init.find(1)->second;
	double* med_S6_init = &med_sim->X_init.find(2)->second;
	double* med_S7_init = &med_sim->X_init.find(3)->second;
	DoublePtrData* med_S2_incoming = new DoublePtrData("S2_data",med_S2_init);
	DoublePtrData* med_S3_incoming = new DoublePtrData("S3_data",med_S3_init);
	DoublePtrData* med_S6_incoming = new DoublePtrData("S6_data",med_S6_init);
	DoublePtrData* med_S7_incoming = new DoublePtrData("S7_data",med_S7_init);

	// FAST
	double* fast_S2_init = &fast_sim->X_init.find(1)->second;
	double* fast_S3_init = &fast_sim->X_init.find(2)->second;
	double* fast_S6_init = &fast_sim->X_init.find(5)->second;
	double* fast_S7_init = &fast_sim->X_init.find(6)->second;
	DoublePtrData* fast_S2_incoming = new DoublePtrData("S2_data",fast_S2_init);
	DoublePtrData* fast_S3_incoming = new DoublePtrData("S3_data",fast_S3_init);
	DoublePtrData* fast_S6_incoming = new DoublePtrData("S6_data",fast_S6_init);
	DoublePtrData* fast_S7_incoming = new DoublePtrData("S7_data",fast_S7_init);
/*
	cout << "SLOW" << endl << "----" << endl;
	cout << slow_sim->gillespSim->species.at(slow_sim->X_init.find(0)->first)->name << ": " << *slow_S3_init << endl;
	cout << slow_sim->gillespSim->species.at(slow_sim->X_init.find(1)->first)->name << ": " << *slow_S6_init << endl;
	cout << endl;
	cout << "MED" << endl << "----" << endl;
	cout << med_sim->gillespSim->species.at(med_sim->X_init.find(0)->first)->name << ": " << *med_S2_init << endl;
	cout << med_sim->gillespSim->species.at(med_sim->X_init.find(1)->first)->name << ": " << *med_S3_init << endl;
	cout << med_sim->gillespSim->species.at(med_sim->X_init.find(2)->first)->name << ": " << *med_S6_init << endl;
	cout << med_sim->gillespSim->species.at(med_sim->X_init.find(3)->first)->name << ": " << *med_S7_init << endl;
	cout << endl;
	cout << "FAST" << endl << "----" << endl;
	cout << fast_sim->gillespSim->species.at(fast_sim->X_init.find(1)->first)->name << ": " << *fast_S2_init << endl;
	cout << fast_sim->gillespSim->species.at(fast_sim->X_init.find(2)->first)->name << ": " << *fast_S3_init << endl;
	cout << fast_sim->gillespSim->species.at(fast_sim->X_init.find(5)->first)->name << ": " << *fast_S6_init << endl;
	cout << fast_sim->gillespSim->species.at(fast_sim->X_init.find(6)->first)->name << ": " << *fast_S7_init << endl;
	cout << endl;
*/
	// *** Create variables ***
	// SLOW
	double* slow_S3_pop = &slow_sim->gillespSim->species.at(0)->population;
	double* slow_S6_pop = &slow_sim->gillespSim->species.at(1)->population;
	DoublePtrData* slow_S3_outgoing = new DoublePtrData("S3_data",slow_S3_pop);
	DoublePtrData* slow_S6_outgoing = new DoublePtrData("S6_data",slow_S6_pop);
	DoublePtrTracker* slow_S3_var = new DoublePtrTracker(slow_S3_outgoing,0.0); // Pass data upon ANY change (eps = 0)
	DoublePtrTracker* slow_S6_var = new DoublePtrTracker(slow_S6_outgoing,0.0);

	// MED


	// FAST


/*
	cout << slow_sim->gillespSim->species.at(0)->name << ": " << *slow_S3_pop << endl;
	cout << slow_sim->gillespSim->species.at(1)->name << ": " << *slow_S6_pop << endl;
*/



}
