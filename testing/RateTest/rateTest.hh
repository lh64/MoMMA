/*
 * rateTest.h
 *
 *  Created on: Oct 5, 2010
 *      Author: Leonard Harris
 */

#ifndef RATETEST_HH_
#define RATETEST_HH_

#include <iostream>
#include <vector>
#include "../../model_spec/simpleSpecies.hh"
#include "../../model_spec/rateExpression.hh"
#include "../../model_spec/reaction.hh"
#include "../../model_spec/reactions/bioNetGenRxn.hh"

using namespace std;

namespace MoMMA{

	class RateTest {
	public:
		RateTest();
		~RateTest(){}
	};
}

#endif /* RATETEST_HH_ */
