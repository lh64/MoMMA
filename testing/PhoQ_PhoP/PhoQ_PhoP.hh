/*
 * PhoQ_PhoP.hh
 *
 *  Created on: Aug 22, 2010
 *      Author: Leonard Harris
 */

#ifndef PHOQ_PHOP_HH_
#define PHOQ_PHOP_HH_

#include "autoregModel.hh"
#include "phosphoModel.hh"
#include "fullModel.hh"

#include "PhoQ_PhoP_Gillespie.hh"
#include "PhoQ_PhoP_Euler.hh"

#include "../../MoMMA.hh"

using namespace std;

namespace MoMMA{

	class PhoQ_PhoP {
	public:
		PhoQ_PhoP();
		~PhoQ_PhoP(){}
	};
}

#endif /* PHOQ_PHOP_HH_ */
