/*
 * worldSimulator.cpp
 *
 *  Created on: Feb 3, 2010
 *      Author: Leonard Harris
 */

#include "worldSimulator.hh"

using namespace std;
using namespace MoMMA;

WorldSimulator::WorldSimulator(SimpleGillespie* sim){
	if (MoMMA::debug) cout << "WorldSimulator constructor called.\n";
	this->sim = sim;
	this->getLigandLevel();
}

double WorldSimulator::run(double t){
	double tOut = this->sim->run(t);
	this->getLigandLevel();
	return tOut;
}
/*
double WorldSimulator::run(int n){
	double tOut = this->sim->run(n);
	this->getLigandLevel();
	return tOut;
}
*/
void WorldSimulator::getLigandLevel(){

	bool gotIt = false;

	// Which cell species?
	int i=9;
	while (!gotIt){
		if (this->sim->species[i]->population == 1.0){
			gotIt = true;
		}
		else{
			i++;
		}
		if (i > 20){
			cout << "\tOops in WorldSimulator::getLigandLevel()\n";
			gotIt=true;
		}
	}

	// Which box?
	if (i >= 9 && i <= 12){
		if (this->sim->debug){
			cout << "\tCell is in Box 0\n";
		}
		if (this->sim->species[0]->population == 1.0){
			if (this->sim->debug){
				cout << "\tLigand level in Box 0 is 0 (low)\n";
			}
			this->ligLevel=0;
		}
		else if (this->sim->species[1]->population == 1.0){
			if (this->sim->debug){
				cout << "\tLigand level in Box 0 is 1 (medium)\n";
			}
			this->ligLevel=1;
		}
		else if (this->sim->species[2]->population == 1.0){
			if (this->sim->debug){
				cout << "\tLigand level in Box 0 is 2 (high)\n";
			}
			this->ligLevel=2;
		}
		else{cout << "\tOops in WorldSimulator::getLigandLevel()\n";}
	}
	else if (i >= 13 && i <= 16){
		if (this->sim->debug){
			cout << "\tCell is in Box 1\n";
		}
		if (this->sim->species[3]->population == 1.0){
			if (this->sim->debug){
				cout << "\tLigand level in Box 1 is 0 (low)\n";
			}
			this->ligLevel=0;
		}
		else if (this->sim->species[4]->population == 1.0){
			if (this->sim->debug){
				cout << "\tLigand level in Box 1 is 1 (medium)\n";
			}
			this->ligLevel=1;
		}
		else if (this->sim->species[5]->population == 1.0){
			if (this->sim->debug){
				cout << "\tLigand level in Box 1 is 2 (high)\n";
			}
			this->ligLevel=2;
		}
		else{cout << "\tOops in WorldSimulator::getLigandLevel()\n";}
	}
	else if (i >= 17 && i <= 20){
		if (this->sim->debug){
			cout << "\tCell is in Box 2\n";
		}
		if (this->sim->species[6]->population == 1.0){
			if (this->sim->debug){
				cout << "\tLigand level in Box 2 is 0 (low)\n";
			}
			this->ligLevel=0;
		}
		else if (this->sim->species[7]->population == 1.0){
			if (this->sim->debug){
				cout << "\tLigand level in Box 2 is 1 (medium)\n";
			}
			this->ligLevel=1;
		}
		else if (this->sim->species[8]->population == 1.0){
			if (this->sim->debug){
				cout << "\tLigand level in Box 2 is 2 (high)\n";
			}
			this->ligLevel=2;
		}
		else{cout << "\tOops in WorldSimulator::getLigandLevel()\n";}
	}
	else{cout << "\tOops in WorldSimulator::getLigandLevel()\n";}
}
