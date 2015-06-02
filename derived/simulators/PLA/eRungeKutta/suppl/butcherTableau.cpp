/*
 * butcherTableau.cpp
 *
 *  Created on: Mar 22, 2011
 *      Author: Leonard Harris
 */

#include "butcherTableau.hh"

using namespace std;
using namespace MoMMA;

ButcherTableau::ButcherTableau() : s(0){
	if (MoMMA::debug)
		cout << "ButcherTableau constructor called." << endl;
}

ButcherTableau::ButcherTableau(vector<vector<double> > alpha, vector<double> beta)
: alpha(alpha), beta(beta), s(alpha.size()){
	if (MoMMA::debug)
		cout << "ButcherTableau constructor called." << endl;
	// Error check
	if (alpha.size() != beta.size()){
		cout << "Error in ButcherTableau constructor: Matrix 'alpha' and vector 'beta' must be of equal lengths. Exiting." << endl;
		exit(1);
	}
	for (unsigned int i=0;i < alpha.size();i++){
		if (alpha[i].size() != alpha.size()){
			cout << "Error in ButcherTableau constructor: Matrix 'alpha' must be square. Exiting." << endl;
			exit(1);
		}
	}
	double sum = 0.0;
	for (unsigned int i=0;i < beta.size();i++){
		sum += beta[i];
	}
	if (sum > 1.0 + MoMMA::TOL || sum < 1.0 - MoMMA::TOL){
		cout << "Error in ButcherTableau constructor: Sum of elements of 'beta' must equal 1.0. Exiting." << endl;
		exit(1);
	}
	//
	this->gamma.resize(this->s,0.0);
	for (unsigned int i=0;i < this->gamma.size();i++){
		for (unsigned int j=0;j < this->alpha[i].size();j++){
			this->gamma[i] += this->alpha[i][j];
		}
	}
	// Error check
	for (unsigned int i=0;i < this->gamma.size();i++){
		if (this->gamma[i] < -MoMMA::TOL || this->gamma[i] > 1.0 + MoMMA::TOL){
			cout << "Error in ButcherTableau constructor: All elements of 'gamma' vector must be >= 0.0 and <= 1.0. Exiting.\n";
			exit(1);
		}
	}
	// Explicit or implicit?
	this->explicit_ = true;
	for (unsigned int i=0;i < this->s && this->explicit_;i++){
		for (unsigned int j=i;j < this->s && this->explicit_;j++){
			if (fabs(this->alpha[i][j]) > MoMMA::TOL){
				this->explicit_ = false;
			}
		}
	}
	//
//	if (this->explicit_) cout << "Explicit Butcher tableau" << endl;
//	else cout << "Implicit Butcher tableau" << endl;
}
