/*
 * binomialCorrector_PL.cpp
 *
 *  Created on: Apr 27, 2011
 *      Author: Leonard Harris
 */

#include "binomialCorrector_PL.hh"

using namespace std;
using namespace MoMMA;
/*
BinomialCorrector_PL::BinomialCorrector_PL() : rxn(){
	if (MoMMA::debug)
		cout << "BinomialCorrector_PL constructor called." << endl;
}
*/
BinomialCorrector_PL::BinomialCorrector_PL(double p, vector<Reaction*>& rxn) : p(p), rxn(rxn){
	if (MoMMA::debug)
		cout << "BinomialCorrector_PL constructor called." << endl;
	// Error check
	if (p <= 0.0 || p >= 1.0){
		cout << "Error in BinomialCorrector_PL constructor: ";
		cout << "p must be > 0.0 and < 1.0; your p = " << this->p << ". Exiting. " << endl;
		exit(1);
	}
}

BinomialCorrector_PL::BinomialCorrector_PL(const BinomialCorrector_PL& pl)
: PostleapChecker(pl), p(pl.p), rxn(pl.rxn){
	if (MoMMA::debug)
		cout << "BinomialCorrector_PL copy constructor called." << endl;
}

BinomialCorrector_PL::~BinomialCorrector_PL(){
	if (MoMMA::debug)
		cout << "BinomialCorrector_PL destructor called." << endl;
}

void BinomialCorrector_PL::correct(vector<double>& k, double& tau){
//	cout << "Correcting." << endl;
	// Error check
	if (k.size() != this->rxn.size()){
		cout << "Error in BinomialCorrector_PL::correct(): Sizes of 'k' and 'rxn' vectors not equal. Exiting." << endl;
		exit(1);
	}
	// Correct
	double tau_old = tau;
	tau *= this->p; // Reduce tau
	double k_old;
	bool stop = true;
	for (unsigned int v=0;v < this->rxn.size();v++){
		if (k[v] > 0.0){
			stop = false;
			k_old = k[v];
			k[v] = Util::RANDOM_BINOMIAL(tau/tau_old,static_cast<int>(floor(k_old + 0.5))); // Reduce k[v]
			this->rxn[v]->fire(k[v]-k_old); // Fire rxn k_new-k_old times (negative value)
		}
	}
	if (stop){
		cout << "Error in BinomialCorrector_PL::correct(): All rxn firings equal 0.0. Shouldn't happen. Exiting." << endl;
		exit(1);
	}
	// Check again
	if (!this->check()){
		this->correct(k,tau);
	}
	else{
//		cout << "**Fixed**" << endl;
	}
}
