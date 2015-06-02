/**
 * @file src/hive.cpp
 * @brief The main entry point for hive
 *
 * This file contains the main function and some other things.
 *
 * @author Michael Sneddon
 * @date Started: Oct 7, 2009    Last edited: Oct 14, 2009 by Michael and Garrit
 *
 * @todo Fill in the details. Memory cheching!!!
 *
 */

#include <string>
#include <time.h>

#include "MoMMA.hh"

#include "borrowed/exception.hh"
#include "borrowed/primitiveData.hh"
#include "borrowed/util/util.hh"

#include "testing/small_lonely_world/SLW.hh"
#include "testing/communication/commTest.hh"
#include "testing/tracking/trackTest.hh"
#include "testing/PhoQ_PhoP/PhoQ_PhoP.hh"
#include "testing/misc/copy.hh"
#include "testing/RateTest/rateTest.hh"
#include "testing/toy/toy.hh"
#include "testing/nested_SSA/nestedTest.hh"
#include "testing/heatbugs/heatbugs.hh"
#include "testing/PLA_Test/plaTest.hh"

using namespace std;
using namespace MoMMA;

void MoMMA::serialSetup(){
	cout << "MoMMA::serialSetup() not yet implemented. Exiting." << endl;
	exit(1);
}

/**
 *  Main method for hive.
 *
 *  @param argc number of arguments (this is the length of argv)
 *  @param argv[] pointer to char arrays (strings) that were passed as arguments
 *  @return zero if hive ran successfully, an error code if it did not
 */

int main(int argc, char *argv[]) {

//	SLW *S = new SLW();
//	CommTest* C = new CommTest();
//	TrackTest* T = new TrackTest();
//	PhoQ_PhoP* P = new PhoQ_PhoP();
//	RateTest* R = new RateTest();
//	TOY* toy = new TOY();
//	NestedTest* N = new NestedTest();
//	Heatbugs* HB = new Heatbugs();
	PLATest PLA;

/*
	Base b("b");
	ChildX cx("cx",3);
	ChildY cy("cy",2.2);

	cout << b.name << "\t"; b.hello();
	cout << cx.name << "\t" << cx.x << "\t"; cx.hello();
	cout << cy.name << "\t" << cy.y << "\t"; cy.hello();
	cout << endl;

	vector<Base*> copy;
	copy.push_back(b.copyOf());
	copy.push_back(cx.copyOf());
	copy.push_back(cy.copyOf());

	cout << copy.at(0)->name << "\t"; copy.at(0)->hello();
	cout << copy.at(1)->name << "\t"; copy.at(1)->hello();
	cout << copy.at(2)->name << "\t"; copy.at(2)->hello();
	cout << endl;
*/
	return 0;
}
