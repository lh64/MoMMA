/*
 * rand2.hh
 *
 *  Created on: Feb 14, 2011
 *      Author: Leonard Harris
 */

#ifndef RAND2_HH_
#define RAND2_HH_

#include "../borrowed/util/rand.hh"

namespace Util{

	double RANDOM_POISSON(double xm);
	double RANDOM_BINOMIAL(double pp, int n);

}

#endif /* RAND2_HH_ */
