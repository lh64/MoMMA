/*
 * heatbugs.hh
 *
 *  Created on: Dec 14, 2010
 *      Author: Leonard Harris
 */

#ifndef HEATBUGS_HH_
#define HEATBUGS_HH_

#include "../../MoMMA.hh"

using namespace std;

namespace MoMMA{

	class Heatbugs{
	public:
		Heatbugs();
		~Heatbugs(){}
	};

	class Coordinate{
	public:
		int xPos, yPos;
		Coordinate(int xPos, int yPos){ this->xPos = xPos; this->yPos = yPos; }
		~Coordinate(){}
	};

	class Bug{
	public:
		int idealTemp;
		int outputHeat;
		double jumpProbability;
		Bug(int idealTemp, int outputHeat, double jumpProbability){
			this->idealTemp = idealTemp;
			this->outputHeat = outputHeat;
			this->jumpProbability = jumpProbability;
		}
		~Bug(){}
	};

	class GridElement{
	public:
		int temp;
		double dissipationRate;
		double diffusionRate;
		bool hasBug;
		int neighbor[4][2];
		GridElement(int initialTemp, double dissipationRate, double diffusionRate){
			this->temp = initialTemp;
			this->dissipationRate = dissipationRate;
			this->diffusionRate = diffusionRate;
			this->hasBug = false;
		}
		~GridElement(){}
		int getTemp(){ return this->temp; }
		void changeTemp(int howMuch){ this->temp += howMuch; }
	};

	class HeatbugsSimulator : public fSimulator{
	public:
		vector<vector<GridElement*> > grid;
		map<Bug*,Coordinate*> bug;
		map<Bug*,Coordinate*>::iterator bugIter;
//		vector<Bug*> bug;
//		vector<pair<int,int> > bugPosition;
		HeatbugsSimulator(int xCells, int yCells, int initialTemp, double heatDissipation, double heatDiffusivity,
						  int nBugs, int minIdealTemp, int maxIdealTemp, int minOutputHeat, int maxOutputHeat,
						  double jumpProbability);
		~HeatbugsSimulator();
//		virtual void initialize();
		virtual double run(double t){ return this->run(0.0,t); }
		virtual double run(double tStart, double tEnd);
//		virtual void rollBack(double amount);
//		virtual bool checkForEquilibrium();
	};
}

#endif /* HEATBUGS_HH_ */
