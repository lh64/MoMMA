/*
 * reaction.cpp
 *
 *  Created on: Oct 8, 2010
 *      Author: Leonard Harris
 */

#include <iostream>
#include "reaction.hh"
#include "../borrowed/util/util.hh"

using namespace std;
using namespace MoMMA;

Reaction::Reaction(){
	if (MoMMA::debug)
		cout << "Reaction constructor called." << endl;
	this->type = "UNKNOWN";
}

Reaction::Reaction(map<SimpleSpecies*,int> stoichSpecies, vector<SimpleSpecies*> rateSpecies, RateExpression* re){
	if (MoMMA::debug)
		cout << "Reaction constructor called." << endl;
	// Error check
	for (unsigned int i=0;i < rateSpecies.size();i++){
		for (unsigned int j=i+1;j < rateSpecies.size();j++){
			if (rateSpecies[i] == rateSpecies[j]){
				cout << "Error in Reaction constructor: Species " << rateSpecies[i]->name << " is duplicated in 'rateSpecies' vector. ";
				cout << "This is not allowed. Exiting." << endl;
				exit(1);
			}
		}
	}
	//
	this->type = re->type;
	this->stoichSpecies = stoichSpecies;
	this->rateSpecies = rateSpecies;
	this->re = re;
	this->string_ID = Reaction::getStringID(this->stoichSpecies,this->re->toString());
}
/*
Reaction::Reaction(vector<pair<SimpleSpecies*,int> > stoichSpecies, vector<SimpleSpecies*> rateSpecies, RateExpression* re){
	if (MoMMA::debug)
		cout << "Reaction constructor called." << endl;
	this->type = re->type;
	for (unsigned int i=0;i < stoichSpecies.size();i++){
		this->stoichSpecies.insert(stoichSpecies[i]);
	}
	this->rateSpecies = rateSpecies;
	this->re = re;
	this->string_ID = Reaction::getStringID(this->stoichSpecies,this->re->toString());
}

Reaction::Reaction(vector<SimpleSpecies*> stoichSpecies, vector<int> stoich, vector<SimpleSpecies*> rateSpecies, RateExpression* re){
	if (MoMMA::debug)
		cout << "Reaction constructor called." << endl;
	// Error check
	if (stoichSpecies.size() != stoich.size()){
		cout << "Error in Reaction constructor: 'stoichSpecies' and 'stoich' vectors not equal length. Exiting." << endl;
		exit(1);
	}
	this->type = re->type;
	for (unsigned int i=0;i < stoichSpecies.size();i++){
		this->stoichSpecies.insert( pair<SimpleSpecies*,int>(stoichSpecies[i],stoich[i]) );
	}
	this->rateSpecies = rateSpecies;
	this->re = re;
	this->string_ID = Reaction::getStringID(this->stoichSpecies,this->re->toString());
}

Reaction::Reaction(SimpleSpecies* stoichSpecies, int stoich, vector<SimpleSpecies*> rateSpecies, RateExpression* re){
	if (MoMMA::debug)
		cout << "Reaction constructor called." << endl;
	this->type = re->type;
	this->stoichSpecies.insert( pair<SimpleSpecies*,int>(stoichSpecies,stoich) );
	this->rateSpecies = rateSpecies;
	this->re = re;
	this->string_ID = Reaction::getStringID(this->stoichSpecies,this->re->toString());
}

Reaction::Reaction(vector<SimpleSpecies*> stoichSpecies, vector<int> stoich, SimpleSpecies* rateSpecies, RateExpression* re){
	if (MoMMA::debug)
		cout << "Reaction constructor called." << endl;
	// Error check
	if (stoichSpecies.size() != stoich.size()){
		cout << "Error in Reaction constructor: 'stoichSpecies' and 'stoich' vectors not equal length. Exiting." << endl;
		exit(1);
	}
	this->type = re->type;
	for (unsigned int i=0;i < stoichSpecies.size();i++){
		this->stoichSpecies.insert( pair<SimpleSpecies*,int>(stoichSpecies[i],stoich[i]) );
	}
	this->rateSpecies.push_back(rateSpecies);
	this->re = re;
	this->string_ID = Reaction::getStringID(this->stoichSpecies,this->re->toString());
}

Reaction::Reaction(SimpleSpecies* stoichSpecies, int stoich, SimpleSpecies* rateSpecies, RateExpression* re){
	if (MoMMA::debug)
		cout << "Reaction constructor called." << endl;
	this->type = re->type;
	this->stoichSpecies.insert( pair<SimpleSpecies*,int>(stoichSpecies,stoich) );
	this->rateSpecies.push_back(rateSpecies);
	this->re = re;
	this->string_ID = Reaction::getStringID(this->stoichSpecies,this->re->toString());
}

// Old constructors
Reaction::Reaction(vector<SimpleSpecies*> r, vector<int> rS, vector<SimpleSpecies*> p, vector<int> pS, RateExpression* re){
	if (MoMMA::debug)
		cout << "Reaction constructor called." << endl;
	// Error check
	if (r.size() != rS.size()){
		cout << "Error in Reaction constructor: 'reactants' and 'rStoich' vectors not equal length. Exiting." << endl;
		exit(1);
	}
	if (p.size() != pS.size()){
		cout << "Error in Reaction constructor: 'products' and 'pStoich' vectors not equal length. Exiting." << endl;
		exit(1);
	}
	this->type = re->type;
	for (unsigned int i=0;i < r.size();i++){
		this->stoichSpecies.insert( pair<SimpleSpecies*,int>(r[i],rS[i]) );
		this->rateSpecies.push_back(r.at(i));
	}
	for (unsigned int i=0;i < p.size();i++){
		this->stoichSpecies.insert( pair<SimpleSpecies*,int>(p[i],pS[i]) );
	}
	this->re = re;
	this->string_ID = Reaction::getStringID(this->stoichSpecies,this->re->toString());
}

Reaction::Reaction(SimpleSpecies* r, int rS, vector<SimpleSpecies*> p, vector<int> pS, RateExpression* re){
	if (MoMMA::debug)
		cout << "Reaction constructor called." << endl;
	// Error check
	if (p.size() != pS.size()){
		cout << "Error in Reaction constructor: 'products' and 'pStoich' vectors not equal length. Exiting." << endl;
		exit(1);
	}
	this->type = re->type;
	this->stoichSpecies.insert( pair<SimpleSpecies*,int>(r,rS) );
	this->rateSpecies.push_back(r);
	for (unsigned int i=0;i < p.size();i++){
		this->stoichSpecies.insert( pair<SimpleSpecies*,int>(p[i],pS[i]) );
	}
	this->re = re;
	this->string_ID = Reaction::getStringID(this->stoichSpecies,this->re->toString());
}

Reaction::Reaction(vector<SimpleSpecies*> r, vector<int> rS, SimpleSpecies* p, int pS, RateExpression* re){
	if (MoMMA::debug)
		cout << "Reaction constructor called." << endl;
	// Error check
	if (r.size() != rS.size()){
		cout << "Error in Reaction constructor: 'reactants' and 'rStoich' vectors not equal length. Exiting." << endl;
		exit(1);
	}
	this->type = re->type;
	for (unsigned int i=0;i < r.size();i++){
		this->stoichSpecies.insert( pair<SimpleSpecies*,int>(r[i],rS[i]) );
		this->rateSpecies.push_back(r.at(i));
	}
	this->stoichSpecies.insert( pair<SimpleSpecies*,int>(p,pS) );
	this->re = re;
	this->string_ID = Reaction::getStringID(this->stoichSpecies,this->re->toString());
}

Reaction::Reaction(SimpleSpecies* r, int rS, SimpleSpecies* p, int pS, RateExpression* re){
	if (MoMMA::debug)
		cout << "Reaction constructor called." << endl;
	this->type = re->type;
	this->stoichSpecies.insert( pair<SimpleSpecies*,int>(r,rS) );
	this->stoichSpecies.insert( pair<SimpleSpecies*,int>(p,pS) );
	this->rateSpecies.push_back(r);
	this->re = re;
	this->string_ID = Reaction::getStringID(this->stoichSpecies,this->re->toString());
}
*/
Reaction::~Reaction(){
	if (MoMMA::debug)
		cout << "Reaction destructor called: " << this->toString() << endl;
}

double Reaction::getRate(){
	vector<double> X;
	for (unsigned int i=0;i < this->rateSpecies.size();i++){
		X.push_back(this->rateSpecies.at(i)->population);
	}
	return this->re->getRate(X);
}

double Reaction::get_dRate_dX(int which){
	vector<double> X;
	for (unsigned int i=0;i < this->rateSpecies.size();i++){
		X.push_back(this->rateSpecies[i]->population);
	}
	return this->re->get_dRate_dX(which,X);
}

void Reaction::fire(double K){
//	cout << this->toString() << ": ";
	map<SimpleSpecies*,int>::iterator it;
	SimpleSpecies* species;
	double stoich;
	for (it = this->stoichSpecies.begin();it != this->stoichSpecies.end();it++){
		species = (*it).first;
		stoich = static_cast<double>((*it).second);
		species->changePopulation(K*stoich);
//		cout << species->name << " " << K*stoich;
	}
//	cout << endl;
}

///////////////////

string Reaction::getStringID(vector<SimpleSpecies*> stoichSpecies, vector<int> stoich, string type_string){
	if (stoichSpecies.size() != stoich.size()){
		cout << "Error in Reaction::getStringID(): 'stoichSpecies' and 'stoich' vectors not equal length. Exiting." << endl;
		exit(1);
	}
	vector<pair<SimpleSpecies*,int> > ss;
	for (unsigned int i=0;i < stoichSpecies.size();i++){
		ss.push_back(pair<SimpleSpecies*,int>(stoichSpecies[i],stoich[i]));
	}
	return Reaction::getStringID(ss,type_string);
}

string Reaction::getStringID(vector<pair<SimpleSpecies*,int> > stoichSpecies, string type_string){
	vector<SimpleSpecies*> r; vector<int> rS;
	vector<SimpleSpecies*> p; vector<int> pS;
	for (unsigned int i=0;i < stoichSpecies.size();i++){
		if (stoichSpecies[i].second < 0){ // reactant
			r.push_back(stoichSpecies[i].first);
			rS.push_back(stoichSpecies[i].second);
		}
		else if (stoichSpecies[i].second > 0){ // product
			p.push_back(stoichSpecies[i].first);
			pS.push_back(stoichSpecies[i].second);
		}
		else{ // catalyst
			r.push_back(stoichSpecies[i].first);
			rS.push_back(-1);
			p.push_back(stoichSpecies[i].first);
			pS.push_back(1);
		}
	}
	return Reaction::getStringID(r,rS,p,pS,type_string);
}

string Reaction::getStringID(map<SimpleSpecies*,int> stoichSpecies, string type_string){
	map<SimpleSpecies*,int>::iterator it;
	vector<pair<SimpleSpecies*,int> > v;
	for (it = stoichSpecies.begin();it != stoichSpecies.end();it++){
		v.push_back(*it);
	}
	return Reaction::getStringID(v,type_string);
}

// Old type_string getter
string Reaction::getStringID(vector<SimpleSpecies*> r, vector<int> rS, vector<SimpleSpecies*> p, vector<int> pS,
							 string type_string){
	// Error check
	if (r.size() != rS.size()){
		cout << "Error in Reaction::getStringName(): r and rS vectors must be equal size. Exiting.";
		cout << endl;
		exit(1);
	}
	if (p.size() != pS.size()){
		cout << "Error in Reaction::getStringName(): p and pS vectors must be equal size. Exiting.";
		cout << endl;
		exit(1);
	}

	// Get reaction string
	string name = "";
	if (r.size() > 0){
		if (rS.at(0) < -1) {
			name += Util::toString(-rS.at(0));
		}
		name += r.at(0)->name;
		for (unsigned int i=1;i < r.size();i++){
			name += " + ";
			if (rS.at(i) < -1){
				name += Util::toString(-rS.at(i));
			}
			name += r.at(i)->name;
		}
	}
	else{
		name = "*";
	}
	//
	name += " -> ";
	//
	if (p.size() > 0){
		if (pS.at(0) > 1){
			name += Util::toString(pS.at(0));
		}
		name += p.at(0)->name;
		for (unsigned int i=1;i < p.size();i++){
			name += " + ";
			if (pS.at(i) > 1){
				name += Util::toString(pS.at(i));
			}
			name += p.at(i)->name;
		}
	}
	else{
		name += "*";
	}
	name += " (" + type_string + ")";

	return name;
}
