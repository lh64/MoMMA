/*
 * heatbugsSimulator.cpp
 *
 *  Created on: Dec 14, 2010
 *      Author: Leonard Harris
 */

#include "heatbugs.hh"
#include "../../borrowed/util/util.hh"

using namespace std;
using namespace MoMMA;

HeatbugsSimulator::HeatbugsSimulator(int xCells, int yCells, int initialTemp, double heatDissipation, double heatDiffusivity,
									 int nBugs, int minIdealTemp, int maxIdealTemp, int minOutputHeat, int maxOutputHeat,
									 double jumpProbability){

	cout << "World:" << endl << "------" << endl;
	cout << "xCells = " << xCells << ", yCells = " << yCells << ", initialTemp = " << initialTemp
		 << ", heatDissipation = " << heatDissipation << ", heatDiffusivity = " << heatDiffusivity << endl;
	cout << endl;

	cout << "Bugs:" << endl << "------" << endl;
	cout << "nBugs = " << nBugs << ", minIdealTemp = " << minIdealTemp << ", maxIdealTemp = " << maxIdealTemp
		 << ", minOutputHeat = " << minOutputHeat << ", maxOutputHeat = " << maxOutputHeat << ", jumpProbability = "
		 << jumpProbability << endl;
	cout << endl;

	// Create grid
	int iNew, jNew;
	this->grid.resize(xCells);
	for (int i=0;i < xCells;i++){
		this->grid[i].resize(yCells);
		for (int j=0;j < yCells;j++){
			this->grid[i][j] = new GridElement(initialTemp,heatDissipation,heatDiffusivity);
			if ( (j-1) < 0 ){ jNew = yCells-1; } else{ jNew = j-1; }
			this->grid[i][j]->neighbor[0][0] = i; this->grid[i][j]->neighbor[0][1] = jNew; // North
			if ( (j+1) > (yCells-1) ){ jNew = 0; } else{ jNew = j+1; }
			this->grid[i][j]->neighbor[1][0] = i; this->grid[i][j]->neighbor[1][1] = jNew; // South
			if ( (i+1) > (xCells-1) ){ iNew = 0; } else{ iNew = i+1; }
			this->grid[i][j]->neighbor[2][0] = iNew; this->grid[i][j]->neighbor[2][1] = j; // East
			if ( (i-1) < 0 ){ iNew = xCells-1; } else{ iNew = i-1; }
			this->grid[i][j]->neighbor[3][0] = iNew; this->grid[i][j]->neighbor[3][1] = j; // West
		}
	}

	// Create bugs and randomly place on grid
	bool done;
	int idealTemp, outputHeat;
	int xCoord, yCoord;
	for (int i=0;i < nBugs;i++){
		// Generate coordinates first
		xCoord = Util::RANDOM_INT(0,xCells);
		yCoord = Util::RANDOM_INT(0,yCells);
		// Make sure a bug doesn't already live here
		done = false;
		while (!done){
			done = true;
			for (this->bugIter = this->bug.begin();this->bugIter != this->bug.end();this->bugIter++){
				if ((*this->bugIter).second->xPos == xCoord){
					if ((*this->bugIter).second->yPos == yCoord){
						cout << "**Oops, a bug already lives on site (" << xCoord << "," << yCoord << "). Try again." << endl;
						xCoord = Util::RANDOM_INT(0,xCells);
						yCoord = Util::RANDOM_INT(0,yCells);
						done = false;
					}
				}
			}
		}
		// Make the bug
		idealTemp = Util::RANDOM_INT(minIdealTemp,maxIdealTemp);
		outputHeat = Util::RANDOM_INT(minOutputHeat,maxOutputHeat);
		this->bug.insert( pair<Bug*,Coordinate*>(new Bug(idealTemp,outputHeat,jumpProbability),new Coordinate(xCoord,yCoord)) );
		// Tell the grid element about the bug
		this->grid[xCoord][yCoord]->hasBug = true;
		cout << "Bug[" << i << "]: xCoord = " << xCoord << ", yCoord = " << yCoord << ", idealTemp = " << idealTemp
			 << ", outputHeat = " << outputHeat << endl;
	}
	cout << endl;
/*
	for (unsigned int i=0;i < this->grid.size();i++){
		for (unsigned int j=0;j < this->grid[i].size();j++){
			cout << "Site (" << i << "," << j << "):";
			if (this->grid[i][j]->hasBug){
				cout << " has a bug";
			}
			cout << "; neighbors->";
			for (int k=0;k<4;k++){
				cout << "(" << this->grid[i][j]->neighbor[k][0] << "," << this->grid[i][j]->neighbor[k][1] << ") ";
			}
			cout << endl;
		}
	}
*/
}

double HeatbugsSimulator::run(double tStart, double tEnd){
	double time = tStart;
	int step = 0;
	while (time < tEnd){
		cout << "Step " << ++step << ":" << endl;

		// Bugs first
		Bug* BUG;
		Coordinate* COORD;
		for (this->bugIter = this->bug.begin();this->bugIter != this->bug.end();this->bugIter++){
			BUG = (*this->bugIter).first;
			COORD = (*this->bugIter).second;
			// Check unhappiness
			if ( (BUG->idealTemp - this->grid[COORD->xPos][COORD->yPos]->getTemp()) != 0  ){
				// Random jump?
				if (Util::RANDOM_CLOSED() < BUG->jumpProbability){
					int xOld = COORD->xPos;
					int yOld = COORD->yPos;
					int dest, xNew, yNew;
					bool done = false;
					vector<int> already;
					while (!done && already.size() < 4){
						done = true;
						bool ok = false;
						while (!ok){
							ok = true;
							dest = Util::RANDOM_INT(0,4);
							for (unsigned int i=0;i < already.size();i++){
								if (dest == already[i]){
									ok = false;
								}
							}
						}
						already.push_back(dest);
						xNew = this->grid[xOld][yOld]->neighbor[dest][0];
						yNew = this->grid[xOld][yOld]->neighbor[dest][1];
						if (this->grid[xNew][yNew]->hasBug){
							done = false;
						}
					}
					if (done){ // Found an unoccupied neighbor
						cout << "Random jump from site (" << xOld << "," << yOld << ") to site (" << xNew << "," << yNew << ")"
							 << endl;
						// Remove bug from grid[xOld][yOld]
						this->grid[xOld][yOld]->hasBug = false;
						// Place bug in grid[xNew][yNew]
						COORD->xPos = xNew;
						COORD->yPos = yNew;
						this->grid[xNew][yNew]->hasBug = true;
					}
				}

				// Otherwise...
				else{
					vector<int> already;
					int dest = 0;
					int xNew = this->grid[COORD->xPos][COORD->yPos]->neighbor[dest][0];
					int yNew = this->grid[COORD->xPos][COORD->yPos]->neighbor[dest][1];
					int destTemp = this->grid[xNew][yNew]->getTemp();
					int xTemp, yTemp;
					bool done = false;
					while (!done && already.size() < 4){
						done = true;
						// Move to warmer site
						if ( (BUG->idealTemp - this->grid[COORD->xPos][COORD->yPos]->getTemp()) > 0  ){
cout << "hello" << endl;
							// Find warmest neighboring site
							for (int i=1;i<4;i++){
								bool ok = true;
								for (unsigned int j=0;j < already.size();j++){
									if (i == already[j]){ ok = false; }
								}
								if (ok){
									xTemp = this->grid[COORD->xPos][COORD->yPos]->neighbor[i][0];
									yTemp = this->grid[COORD->xPos][COORD->yPos]->neighbor[i][1];
									if (this->grid[xTemp][yTemp]->getTemp() > destTemp){
										dest = i;
										xNew = xTemp;
										yNew = yTemp;
										destTemp = this->grid[xNew][yNew]->getTemp();
									}
								}
							}
							// Only attempt move if destination temp is greater than current temp
							if (destTemp > this->grid[COORD->xPos][COORD->yPos]->getTemp()){
								already.push_back(dest);
								if (!this->grid[xNew][yNew]->hasBug){ // Unoccupied
									cout << "Jump from site (" << COORD->xPos << "," << COORD->yPos << ") to site ("
										 << xNew << "," << yNew << ")" << endl;
									this->grid[COORD->xPos][COORD->yPos]->hasBug = false;
									COORD->xPos = xNew;
									COORD->yPos = yNew;
									this->grid[COORD->xPos][COORD->yPos]->hasBug = true;
								}
								else{
									done = false;
								}
							}
						}
						// Move to colder site
						else{
							for (int i=1;i<4;i++){
								xTemp = this->grid[COORD->xPos][COORD->yPos]->neighbor[i][0];
								yTemp = this->grid[COORD->xPos][COORD->yPos]->neighbor[i][1];
								if (this->grid[xNew][yNew]->getTemp() < destTemp){
									xNew = xTemp;
									yNew = yTemp;
									destTemp = this->grid[xNew][yNew]->getTemp();
								}
							}
						}
					}
				}
			}
		}


		// World second
		// ...

		time += 1.0;
	}
	return (time-tStart);
}

HeatbugsSimulator::~HeatbugsSimulator(){
	// Delete grid
	for (unsigned int i=0;i < this->grid.size();i++){
		for (unsigned int j=0;j < this->grid[i].size();j++){
			delete this->grid[i][j];
		}
	}
	// Delete bugs
	for (this->bugIter = this->bug.begin();this->bugIter != this->bug.end();this->bugIter++){
		delete (*this->bugIter).first;
		delete (*this->bugIter).second;
	}
}
