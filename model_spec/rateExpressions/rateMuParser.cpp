/*
 * rateMuParser.cpp
 *
 *  Created on: Jul 22, 2011
 *      Author: Leonard Harris
 */

#include "rateMuParser.hh"

using namespace std;
using namespace MoMMA;

RateMuParser::RateMuParser(mu::Parser& p, vector<SimpleSpecies*> r, vector<int> rS) : p(p), rStoich(rS){
	if (MoMMA::debug)
		cout << "RateMuParser constructor called." << endl;
	// Error check
	if (r.size() != rS.size()){
		cout << "Error in RateMuParser constructor: 'r' and 'rS' vectors must be equal size. Exiting." << endl;
		exit(1);
	}
	for (unsigned int i=0;i < rS.size();i++){
		if (rS[i] >= 0.0){
			cout << "Error in RateMuParser constructor: Reactant stoichiometries must be negative. Exiting." << endl;
			cout << "(" << r[i]->name << ": stoich = " << rS[i] << ")" << endl;
			exit(1);
		}
	}
	for (unsigned int i=0;i < r.size();i++){
		for (unsigned int j=i+1;j < r.size();j++){
			if (r[i] == r[j]){
				cout << "Error in RateMuParser constructor: Duplicate reactant species not allowed (r[" << i << "] = r[" << j << "] = ";
				cout << r[i]->name << "). Exiting." << endl;
				exit(1);
			}
		}
	}
	// Get type string
	this->type = "FUNCTION:{";
	if (r.size() == 0){
		this->type += "* ->}{";
	}
	else{
		this->type += r[0]->name;
		for (unsigned int i=1;i < r.size();i++){
			this->type += " + " + r[i]->name;
		}
		this->type += " ->}{";
	}
	this->type += this->p.GetExpr() + "}";
}

RateMuParser::~RateMuParser(){
	if (MoMMA::debug)
		cout << "RateMuParser destructor called." << endl;
}

double RateMuParser::getRate(vector<double> X){
	// Error check
	if (X.size() != this->rStoich.size()){
		cout << "Error in RateMuParser::getRate(): Size of 'X' vector not equal to that of 'rStoich' vector. Exiting." << endl;
		exit(1);
	}
	// Rate calculation
	double rate = this->p.Eval();
	for (unsigned int i=0;i < X.size();i++){
		// Error check
		if (X[i] < 0.0){
			cout << "Error in RateMuParser::getRate(): Negative population detected (X[" << i << "] = " << X[i] << "). Exiting." << endl;
			exit(1);
		}
		// Loop over stoichiometric factor
		for (int j=0;j < fabs(this->rStoich[i]);j++){
			rate *= (X[i]-(double)j)/((double)j+1.0);
		}
	}
	return max(0.0,rate); // If rate is negative, return 0.0 (just in case)
}
