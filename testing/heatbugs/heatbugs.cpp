/*
 * heatbugs.cpp
 *
 *  Created on: Dec 14, 2010
 *      Author: Leonard Harris
 */

#include "heatbugs.hh"
#include "../../borrowed/util/util.hh"

using namespace std;
using namespace MoMMA;

Heatbugs::Heatbugs(){

	// World parameters
	int xCells = 10;
	int yCells = 10;
	int initialTemp = 0;
	double heatDissipation = 0.01;
	double heatDiffusivity = 0.9;

	// Bug parameters
	int nBugs = 5;
	int minIdealTemp = 10;
	int maxIdealTemp = 40;
	int minOutputHeat = 5;
	int maxOutputHeat = 25;
	double jumpProbability = 0.1;

	Util::SEED_RANDOM(11);
	HeatbugsSimulator* hb_sim = new HeatbugsSimulator(xCells,yCells,initialTemp,heatDissipation,heatDiffusivity,
													  nBugs,minIdealTemp,maxIdealTemp,minOutputHeat,maxOutputHeat,
													  jumpProbability);
	hb_sim->run(10.0);
}
