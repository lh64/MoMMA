/*
 * muParserRxn.cpp
 *
 *  Created on: Jul 22, 2011
 *      Author: Leonard Harris
 */

#include "bioNetGenRxn.hh"

using namespace std;
using namespace MoMMA;

MuParserRxn::MuParserRxn(mu::Parser& parser, vector<SimpleSpecies*> r, vector<int> rS, vector<SimpleSpecies*> p, vector<int> pS)
	: BioNetGenRxn(r,rS,p,pS){
	this->construct(parser);
}

MuParserRxn::MuParserRxn(mu::Parser& parser, SimpleSpecies* r, int rS, vector<SimpleSpecies*> p, vector<int> pS)
	: BioNetGenRxn(vector<SimpleSpecies*>(1,r),vector<int>(1,rS),p,pS){
	this->construct(parser);
}

MuParserRxn::MuParserRxn(mu::Parser& parser, vector<SimpleSpecies*> r, vector<int> rS, SimpleSpecies* p, int pS)
	: BioNetGenRxn(r,rS,vector<SimpleSpecies*>(1,p),vector<int>(1,pS)){
	this->construct(parser);
}

MuParserRxn::MuParserRxn(mu::Parser& parser, SimpleSpecies* r, int rS, SimpleSpecies* p, int pS)
	: BioNetGenRxn(vector<SimpleSpecies*>(1,r),vector<int>(1,rS),vector<SimpleSpecies*>(1,p),vector<int>(1,pS)){
	this->construct(parser);
}

MuParserRxn::~MuParserRxn(){
	if (MoMMA::debug)
		cout << "MuParserRxn destructor called." << endl;
	delete this->re;
}

void MuParserRxn::construct(mu::Parser& parser){
	if (MoMMA::debug)
		cout << "MuParserRxn constructor called." << endl;
	this->re = new RateMuParser(parser,this->rateSpecies,this->rStoich); // Don't forget to delete this in the destructor
	this->type = this->re->type;
	this->string_ID = Reaction::getStringID(this->stoichSpecies,this->re->toString());
}
