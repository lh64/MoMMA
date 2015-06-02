/*
 * SLW.cpp
 *
 *  Created on: Oct 22, 2009
 *      Author: Leonard Harris
 */

#include "SLW.hh"

#include <iostream>
#include <exception>
#include <string>
#include <time.h>
#include <math.h>
#include <map>

#include "../../borrowed/primitiveData.hh"
#include "../../borrowed/util/util.hh"

#include "../../model_spec/simpleSpecies.hh"
#include "../../model_spec/simpleRxn.hh"

#include "../../derived/simulators/simpleGillespie.hh"
#include "../../derived/trackers/doublePtrTracker.hh"

#include "../../MoMMA.hh"
//#include "../../module.hh"
//#include "../../translator.hh"

#include "worldModel.hh"
#include "signalingModel.hh"
#include "worldSimulator.hh"
#include "cellTranslator.hh"
#include "worldTranslator.hh"
#include "worldTracker.hh"

using namespace std;
using namespace MoMMA;

SLW::SLW(){

	bool debug = false;

	// Create empty modules
	Module* world = new Module("World");
	Module* cell = new Module("Cell");

	// Provide simulators and add them to the modules
	WorldModel* WM = new WorldModel();
	if (debug){
		for (int i=0;i<WM->nSpecies;i++){ cout << WM->species[i]->name << ": " << WM->species[i]->population << endl; }
		for (int i=0;i<WM->nRxns;i++){ cout << WM->reaction[i]->name << endl; }
	}
	SimpleGillespie* worldGillespie = new SimpleGillespie(WM->nSpecies,WM->species,WM->nRxns,WM->reaction,debug);
	WorldSimulator* worldSim = new WorldSimulator(worldGillespie);
	world->addSimulator(worldSim);

	SignalingModel* SM = new SignalingModel();
	if (debug){
		for (int i=0;i<SM->nSpecies;i++){ cout << SM->species[i]->name << ": " << SM->species[i]->population << endl; }
		for (int i=0;i<SM->nRxns;i++){ cout << SM->reaction[i]->name << endl; }
	}
	SimpleGillespie* cellSim = new SimpleGillespie(SM->nSpecies,SM->species,SM->nRxns,SM->reaction,debug);
	cell->addSimulator(cellSim);

	// Create data elements
	IntPtrData* worldLigData = new IntPtrData("LigData",&worldSim->ligLevel); // Outgoing
	DoublePtrMatrixData* worldYpData = new DoublePtrMatrixData("YpData",2,6); // Incoming
	worldYpData->setDoublePtr(&WM->reaction[18]->c,0,0);
	worldYpData->setDoublePtr(&WM->reaction[20]->c,0,1);
	worldYpData->setDoublePtr(&WM->reaction[22]->c,0,2);
	worldYpData->setDoublePtr(&WM->reaction[24]->c,0,3);
	worldYpData->setDoublePtr(&WM->reaction[26]->c,0,4);
	worldYpData->setDoublePtr(&WM->reaction[28]->c,0,5);
	worldYpData->setDoublePtr(&WM->reaction[19]->c,1,0);
	worldYpData->setDoublePtr(&WM->reaction[21]->c,1,1);
	worldYpData->setDoublePtr(&WM->reaction[23]->c,1,2);
	worldYpData->setDoublePtr(&WM->reaction[25]->c,1,3);
	worldYpData->setDoublePtr(&WM->reaction[27]->c,1,4);
	worldYpData->setDoublePtr(&WM->reaction[29]->c,1,5);

	DoublePtrData* cellYpData = new DoublePtrData("YpData",&SM->species[6]->population); // Outgoing
	DoublePtrData* cellLigData = new DoublePtrData("LigData",&SM->species[0]->population); // Incoming

	// Define translators for all incoming data elements
	WorldTranslator* worldTran = new WorldTranslator(worldYpData);
	CellTranslator* cellTran = new CellTranslator(cellLigData);

	// Define trackers for all outgoing data elements
	WorldTracker* worldTrack = new WorldTracker(worldLigData);
	double cellEps = 0.1;
	DoublePtrTracker* cellTrack = new DoublePtrTracker(cellYpData,cellEps);

	// Add data elements to databases
//	world->addVariable(worldTrack,cell);
//	world->addParameter(worldTran);
//	cell->addVariable(cellTrack,world);
//	cell->addParameter(cellTran);

	// Setup modules
//	world->setupModule();
//	cell->setupModule();

	// Define equilibration metrics
	// ...

	// Define module connectivity
//	world->addChild(cell);
	map<Tracker*,Translator*> world_to_cell;
	world_to_cell.insert( pair<Tracker*,Translator*>(worldTrack,cellTran) );
	map<Tracker*,Translator*> cell_to_world;
	cell_to_world.insert( pair<Tracker*,Translator*>(cellTrack,worldTran) );
	Module::makeNeighbors(world,cell,world_to_cell,cell_to_world);

	// Run top-level parent
	// ...

	//-------------------------------------------------------------------------



/*	cell->db->addData(cellYpData);
	cell->db->addData(cellLigData);

	cout << "YpData ";
	if (cell->db->existsDataItem("YpData")){
		cout << "EXISTS: Value = "
		<< *(static_cast<DoublePtrData*>(cell->db->getDataItem("YpData"))->getDoublePtr())
		<< endl;
	}else{ cout << "does NOT exist.\n";}

	cout << "LigData ";
	if (cell->db->existsDataItem("LigData")){
		cout << "EXISTS: Value = "
		<< *(static_cast<DoublePtrData*>(cell->db->getDataItem("LigData"))->getDoublePtr())
		<< endl;
	}else{ cout << "does NOT exist.\n";}
*/
/*
	cout << "*Yp = " << *Yp << endl;
	*Yp = 100.0;
	cout << "*Yp = " << *Yp << endl;
	cout << "Yp = " << Yp << endl;
	cout << cellYpData->getDoublePtr() << endl;
	*cellYpData->getDoublePtr() = 200.0;
	cout << "*Yp = " << *Yp << endl;
	cout << *cellYpData->getDoublePtr() << endl;
	cout << *(static_cast<DoublePtrData*>(cell->db->getDataItem("YpLevel"))->getDoublePtr())
		 << endl;
*/
/*
	cout << endl;
	WorldModel *WM = new WorldModel();
	if (debug==true){
		for (int i=0;i<WM->nSpecies;i++){ cout << WM->species[i]->name
			<< ": " << WM->species[i]->population << endl; }
		for (int i=0;i<WM->nRxns;i++){ cout << WM->reaction[i]->name << endl; }
	}
	SimpleGillespie *worldGillespie = new SimpleGillespie(WM->nSpecies,WM->species,
														  WM->nRxns,WM->reaction,debug);
	WorldSimulator *worldSim = new WorldSimulator(worldGillespie);
	Module *world = new Module("World",1);
	world->addSimulator(worldSim);
	IntPtrData *worldLigData = new IntPtrData("LigData",&worldSim->ligLevel);
	world->db->addData(worldLigData);

	cout << "LigData ";
	if (world->db->existsDataItem("LigData")){
		cout << "EXISTS: Value = "
		<< *(static_cast<IntPtrData*>(world->db->getDataItem("LigData"))->getIntPtr())
		<< endl;
	}else{ cout << "does NOT exist\n";}

	DoublePtrMatrixData *worldYpData = new DoublePtrMatrixData("YpData",2,6);
	worldYpData->setDoublePtr(&WM->reaction[18]->c,0,0);
	worldYpData->setDoublePtr(&WM->reaction[20]->c,0,1);
	worldYpData->setDoublePtr(&WM->reaction[22]->c,0,2);
	worldYpData->setDoublePtr(&WM->reaction[24]->c,0,3);
	worldYpData->setDoublePtr(&WM->reaction[26]->c,0,4);
	worldYpData->setDoublePtr(&WM->reaction[28]->c,0,5);

	worldYpData->setDoublePtr(&WM->reaction[19]->c,1,0);
	worldYpData->setDoublePtr(&WM->reaction[21]->c,1,1);
	worldYpData->setDoublePtr(&WM->reaction[23]->c,1,2);
	worldYpData->setDoublePtr(&WM->reaction[25]->c,1,3);
	worldYpData->setDoublePtr(&WM->reaction[27]->c,1,4);
	worldYpData->setDoublePtr(&WM->reaction[29]->c,1,5);

	world->db->addData(worldYpData);
	cout << "YpData ";
	if (world->db->existsDataItem("YpData")){
		cout << "EXISTS: Value =\n";
		for (int i=0;i<2;i++){
			for (int j=0;j<6;j++){
				cout << "\t[" << i << "][" << j << "] = "
				<< *static_cast<DoublePtrMatrixData*>(world->db->getDataItem("YpData"))->getDoublePtr(i,j)
				<< endl;
			}
		}
	}else{ cout << "does NOT exist\n";}

	world->addChild(cell);
*/
//
/*
	cout << endl;
	cout << "Module #" << cell->getId() << ":" << endl;
	if (cell->getParent()){
		cout << "\tParent is #" << cell->getParent()->getId() << "." << endl;
	}
	else{
		cout << "\tHas no parent." << endl;
	}
	if (cell->getChildren().size() > 0){
		cout << "\tChildren are:" << endl;
		for (int i=0;i < (int)cell->getChildren().size();i++){
			cout << "\t\t#" << cell->getChildren().at(i)->getId() << endl;
		}
	}
	else{
		cout << "\tHas no children." << endl;
	}
	cout << endl;

	cout << "Module #" << world->getId() << ":" << endl;
	if (world->getParent()){
		cout << "\tParent is #" << world->getParent()->getId() << "." <<  endl;
	}
	else{
		cout << "\tHas no parent." << endl;
	}
	if (world->getChildren().size() > 0){
		cout << "\tChildren are:" << endl;
		for (int i=0;i < (int)world->getChildren().size();i++){
			cout << "\t\t#" << world->getChildren().at(i)->getId() << endl;
		}
	}
	else{
		cout << "\tHas no children." << endl;
	}
*/
//
	cout << endl;

	int cellSteps = 100;
	cout << "Cell Simulator: " << cellSteps << " steps\n";
	cellSim->seed(50L);
	cellSim->setDebug(false);
	cell->sim->run(cellSteps);
/*
	cout << "YpData ";
	if (cell->db->existsDataItem("YpData")){
		cout << "EXISTS: Value = "
		     << *(static_cast<DoublePtrData*>(cell->db->getDataItem("YpData"))->getDoublePtr())
		     << endl;
	}else{ cout << "does NOT exist.\n";}
	cout << SM->species[6]->name << " = " << SM->species[6]->population << endl;

	cout << "LigData ";
	if (cell->db->existsDataItem("LigData")){
		cout << "EXISTS: Value = "
			 << *(static_cast<DoublePtrData*>(cell->db->getDataItem("LigData"))->getDoublePtr())
			 << endl;
	}else{ cout << "does NOT exist.\n";}
	cout << SM->species[0]->name << " = " << SM->species[0]->population << endl;

	cout << "Can we change it?\n";
	*(static_cast<DoublePtrData*>(cell->db->getDataItem("LigData"))->getDoublePtr()) = 200.0;
	cout << "LigData ";;
	if (cell->db->existsDataItem("LigData")){
		cout << "EXISTS: Value = "
			 << *(static_cast<DoublePtrData*>(cell->db->getDataItem("LigData"))->getDoublePtr())
			 << endl;
	}else{ cout << "does NOT exist.\n";}
*/
	cout << SM->species[0]->name << " = " << SM->species[0]->population << endl;

//
	cout << endl;

	int worldSteps = 100;
	cout << "World Simulator: " << worldSteps << " steps\n";
	worldSim->seed(20L);
	worldSim->setDebug(false);
	world->sim->run(worldSteps);

/*	for (int i=0;i<WM->nSpecies;i++){
		cout << WM->species[i]->name << ": " << WM->species[i]->population << endl;
	}
*/
	/*
	cout << "LigData ";
	if (world->db->existsDataItem("LigData")){
		cout << "EXISTS: Value = "
		<< *(static_cast<IntPtrData*>(world->db->getDataItem("LigData"))->getIntPtr())
		<< endl;
	}
	cout << "ligLevel = " << worldSim->ligLevel << endl;

	cout << "YpData ";
	if (world->db->existsDataItem("YpData")){
		cout << "EXISTS: Value =\n";
		for (int i=0;i<2;i++){
			for (int j=0;j<6;j++){
				cout << "\t[" << i << "][" << j << "] = "
				<< *static_cast<DoublePtrMatrixData*>(world->db->getDataItem("YpData"))->getDoublePtr(i,j)
				<< endl;
			}
		}
	}else{ cout << "does NOT exist\n";}

	cout << "Can we change it?" << endl;
	double f;
	for (int i=0;i<2;i++) {
		if (i==0) { f = 1.5; }
		else { f = 0.5; }
		for (int j=0;j<6;j++){
			*static_cast<DoublePtrMatrixData*>(
					world->db->getDataItem("YpData"))->getDoublePtr(i,j) *= f;
		}
	}
	cout << "YpData ";
	if (world->db->existsDataItem("YpData")){
		cout << "EXISTS: Value =\n";
		for (int i=0;i<2;i++){
			for (int j=0;j<6;j++){
				cout << "\t[" << i << "][" << j << "] = "
				<< *static_cast<DoublePtrMatrixData*>(world->db->getDataItem("YpData"))->getDoublePtr(i,j)
				<< endl;
			}
		}
	}else{ cout << "does NOT exist\n";}
*/
	cout << endl << "Run -> Tumble\n";
	cout << WM->reaction[18]->name << ": c = " << WM->reaction[18]->c << endl;
	cout << WM->reaction[20]->name << ": c = " << WM->reaction[20]->c << endl;
	cout << WM->reaction[22]->name << ": c = " << WM->reaction[22]->c << endl;
	cout << WM->reaction[24]->name << ": c = " << WM->reaction[24]->c << endl;
	cout << WM->reaction[26]->name << ": c = " << WM->reaction[26]->c << endl;
	cout << WM->reaction[28]->name << ": c = " << WM->reaction[28]->c << endl;

	cout << "Tumble -> Run\n";
	cout << WM->reaction[19]->name << ": c = " << WM->reaction[19]->c << endl;
	cout << WM->reaction[21]->name << ": c = " << WM->reaction[21]->c << endl;
	cout << WM->reaction[23]->name << ": c = " << WM->reaction[23]->c << endl;
	cout << WM->reaction[25]->name << ": c = " << WM->reaction[25]->c << endl;
	cout << WM->reaction[27]->name << ": c = " << WM->reaction[27]->c << endl;
	cout << WM->reaction[29]->name << ": c = " << WM->reaction[29]->c << endl;
//
	cout << endl;
/*
	cout << "LigData for World = " << *(static_cast<IntPtrData*>(world->db->getDataItem("LigData"))->getIntPtr()) << endl;
	cout << "LigData for Cell = " << *(static_cast<DoublePtrData*>(cell->db->getDataItem("LigData"))->getDoublePtr()) << endl;
	cout << "Yp Data for Cell = " << *(static_cast<DoublePtrData*>(cell->db->getDataItem("YpData"))->getDoublePtr()) << endl;
	cout << "YpData for World: " << endl;
	cout << "  kf = " << *static_cast<DoublePtrMatrixData*>(world->db->getDataItem("YpData"))->getDoublePtr(0,0) << endl;
	cout << "  kr = " << *static_cast<DoublePtrMatrixData*>(world->db->getDataItem("YpData"))->getDoublePtr(1,0) << endl;
	cout << endl;
*/
//	CellTranslator* cellTr = new CellTranslator(cell->fdb->getDataItem("LigData"));
//	WorldTranslator* worldTr = new WorldTranslator(world->fdb->getDataItem("YpData"));
/*
	cout << endl;
	map<Module*,Data*> worldOutgoing;
	worldOutgoing[cell] = world->db->getDataItem("LigData");
	world->comm->outgoing = worldOutgoing;
	map<string,Translator*> worldIncoming;
	worldIncoming[world->db->getDataItem("YpData")->getName()] = worldTr;
	world->comm->incoming = worldIncoming;
	cout << "Outgoing from World: '" << world->comm->outgoing.find(cell)->second->getName() << "'" << endl;
	cout << "Incoming to World: '" << world->comm->incoming.find("YpData")->first << "'" << endl;
	world->comm->incoming.find("YpData")->second->translate(cell->db->getDataItem("YpData"));

	cout << endl;
	map<Module*,Data*> cellOutgoing;
	cellOutgoing[world] = cell->db->getDataItem("YpData");
	cell->comm->outgoing = cellOutgoing;
	map<string,Translator*> cellIncoming;
	cellIncoming[cell->db->getDataItem("LigData")->getName()] = cellTr;
	cell->comm->incoming = cellIncoming;
	cout << "Outgoing from Cell: '" << cell->comm->outgoing.find(world)->second->getName() << "'" << endl;
	cout << "Incoming to Cell: '" << cell->comm->incoming.find("LigData")->first << "'" << endl;
	cell->comm->incoming.find("LigData")->second->translate(world->db->getDataItem("LigData"));

	cout << endl;
	fCommunicator* worldComm = new fCommunicator(worldOutgoing,worldIncoming);
	world->addCommunicator(worldComm);
	world->comm->call(cell);
	cout << "LigData for World = " << *(static_cast<IntPtrData*>(world->db->getDataItem("LigData"))->getIntPtr()) << endl;
	cout << "LigData for Cell = " << *(static_cast<DoublePtrData*>(cell->db->getDataItem("LigData"))->getDoublePtr()) << endl;

	cout << endl;
	fCommunicator* cellComm = new fCommunicator(cellOutgoing,cellIncoming);
	cell->addCommunicator(cellComm);
	cell->comm->call(world);
	cout << "Yp Data for Cell = " << *(static_cast<DoublePtrData*>(cell->db->getDataItem("YpData"))->getDoublePtr()) << endl;
	cout << "YpData for World: " << endl;
	cout << "  kf = " << *static_cast<DoublePtrMatrixData*>(world->db->getDataItem("YpData"))->getDoublePtr(0,0) << endl;
	cout << "  kr = " << *static_cast<DoublePtrMatrixData*>(world->db->getDataItem("YpData"))->getDoublePtr(1,0) << endl;
*/

//	TrivialStepper* world_ts = new TrivialStepper(9.9);
//	world->addStepper(world_ts);

//	TrivialStepper* cell_ts = new TrivialStepper(0.1);
//	cell->addStepper(cell_ts);

/*	int iter = 0;
	cout << endl;
	cout << "*****************" << endl << endl << "Time = " << Module::Global_time << endl << endl;
	while (Module::Global_time < 100.0){
		world->go();
		cout << "Time = " << Module::Global_time << "; iteration " << ++iter << "." << endl << endl;
	}
*/
	// Clean up
	delete world;
}
