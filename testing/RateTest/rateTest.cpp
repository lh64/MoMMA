/*
 * rateTest.cpp
 *
 *  Created on: Oct 5, 2010
 *      Author: Leonard Harris
 */

#include "rateTest.hh"

using namespace std;
using namespace MoMMA;

RateTest::RateTest(){
	cout << "Rate Test" << endl << "---------" << endl;

	// Species
	vector<SimpleSpecies*> species;
	species.push_back(new SimpleSpecies("A",8.0));
	species.push_back(new SimpleSpecies("B",4.0));
	species.push_back(new SimpleSpecies("C",2.0));
	species.push_back(new SimpleSpecies("D",1.0));
	//
	species.push_back(new SimpleSpecies("S",1.0));
	species.push_back(new SimpleSpecies("P",1.0));
	species.push_back(new SimpleSpecies("G",1.0));
	species.push_back(new SimpleSpecies("M",1.0));
	//
	species.push_back(new SimpleSpecies("NULL",1.0));

	RateExpression* re = new RateExpression();
//	cout << "Base RateExpression" << endl;
	map<SimpleSpecies*,int> stoichSpecies;
	stoichSpecies.insert( pair<SimpleSpecies*,int>(species[0],-1) );
	stoichSpecies.insert( pair<SimpleSpecies*,int>(species[8],1) );
	vector<SimpleSpecies*> rateSpecies;
	rateSpecies.push_back(species[0]);
//	Reaction* Re_base = new Reaction(species.at(0),-1,species.at(8),1,re);
	Reaction* Re_base = new Reaction(stoichSpecies,rateSpecies,re);
	cout << Re_base->toString() << ", rate = " << Re_base->getRate() << endl;
	cout << endl;
	delete re;
	delete Re_base;

	// A -> B
	double cl_u = 1.0;
//	RateElementary* rl_u = new RateElementary(cl_u,RateElementary::UNIMOLECULAR);
	ElementaryRxn* Re_u = new ElementaryRxn(cl_u,species.at(0),-1,species.at(1),1);
	cout << Re_u->toString() << ", rate = " << Re_u->getRate() << endl;
	cout << endl;
	delete Re_u;

	// 2A -> B
	double cl_aa = 1.0;
//	RateElementary* rl_aa = new RateElementary(cl_aa,RateElementary::BIMOLECULAR_AA);
	ElementaryRxn* Re_aa = new ElementaryRxn(cl_aa,species.at(0),-2,species.at(1),1);
	cout << Re_aa->toString() << ", rate = " << Re_aa->getRate() << endl;
	cout << endl;
	delete Re_aa;

	// A + B -> C
	double cl_ab = 1.0;
//	RateElementary* rl_ab = new RateElementary(cl_ab,RateElementary::BIMOLECULAR_AB);
	vector<SimpleSpecies*> rSp_ab(species.begin(),species.begin()+2);
	vector<int> rSt_ab(2,-1);
	ElementaryRxn* Re_ab = new ElementaryRxn(cl_ab,rSp_ab,rSt_ab,species.at(2),1);
	cout << Re_ab->toString() << ", rate = " << Re_ab->getRate() << endl;
	cout << endl;
	delete Re_ab;

	// 3A -> B
	double cl_aaa = 1.0;
//	RateElementary* rl_aaa = new RateElementary(cl_aaa,RateElementary::TRIMOLECULAR_AAA);
	ElementaryRxn* Re_aaa = new ElementaryRxn(cl_aaa,species.at(0),-3,species.at(1),1);
	cout << Re_aaa->toString() << ", rate = " << Re_aaa->getRate() << endl;
	cout << endl;
	delete Re_aaa;

	// 2A + B -> C
	double cl_aab = 1.0;
//	RateElementary* rl_aab = new RateElementary(cl_aab,RateElementary::TRIMOLECULAR_AAB);
	vector<SimpleSpecies*> rSp_aab(species.begin(),species.begin()+2);
	vector<int> rSt_aab; rSt_aab.push_back(-2); rSt_aab.push_back(-1);
	ElementaryRxn* Re_aab = new ElementaryRxn(cl_aab,rSp_aab,rSt_aab,species.at(2),1);
	cout << Re_aab->toString() << ", rate = " << Re_aab->getRate() << endl;
	cout << endl;
	delete Re_aab;

	// A + B + C -> D
	double cl_abc = 1.0;
//	RateElementary* rl_abc = new RateElementary(cl_abc,RateElementary::TRIMOLECULAR_ABC);
	vector<SimpleSpecies*> rSp_abc(species.begin(),species.begin()+3);
	vector<int> rSt_abc; rSt_abc.push_back(-1); rSt_abc.push_back(-1); rSt_abc.push_back(-1);
	ElementaryRxn* Re_abc = new ElementaryRxn(cl_abc,rSp_abc,rSt_abc,species.at(3),1);
	cout << Re_abc->toString() << ", rate = " << Re_abc->getRate() << endl;
	cout << endl;
	delete Re_abc;

	// S -> P
	double kcat = 1.0, Km = 1.0;
	stoichSpecies.clear();
	stoichSpecies.insert( pair<SimpleSpecies*,int>(species[4],-1) );
	stoichSpecies.insert( pair<SimpleSpecies*,int>(species[5],1) );
	rateSpecies.clear();
	rateSpecies.push_back(species[4]);
	RateSaturation* rs = new RateSaturation(kcat,Km,rateSpecies,vector<int>(1,-1));
//	Reaction* Re_sat = new Reaction(species.at(4),-1,species.at(5),1,rs);
	Reaction* Re_sat = new Reaction(stoichSpecies,rateSpecies,rs);
	cout << Re_sat->toString() << ", rate = " << Re_sat->getRate() << endl;
	cout << endl;
	delete rs;
	delete Re_sat;

	// G -> G + M
	double Vmax = 1.0, Kh = 1.0, h = 2.0;
	stoichSpecies.clear();
	stoichSpecies.insert( pair<SimpleSpecies*,int>(species[7],1) );
	rateSpecies.clear();
	rateSpecies.push_back(species[6]);
	RateHill* rh = new RateHill(Vmax,Kh,h,rateSpecies,vector<int>(1,-1));
//	vector<SimpleSpecies*> pSp_hill(species.begin()+6,species.end()-1);
//	vector<int> pSt_hill; pSt_hill.push_back(1); pSt_hill.push_back(1);
//	Reaction* Re_hill = new Reaction(species.at(6),-1,pSp_hill,pSt_hill,rh);
	Reaction* Re_hill = new Reaction(stoichSpecies,rateSpecies,rh);
	cout << Re_hill->toString() << ", rate = " << Re_hill->getRate() << endl;
	cout << endl;
	delete rh;
	delete Re_hill;

	// Delete species
	for (unsigned int i=0;i < species.size();i++){
		delete species[i];
	}
}
