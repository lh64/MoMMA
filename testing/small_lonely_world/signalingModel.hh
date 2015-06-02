/*
 * signalingModel.hh
 *
 *  Created on: Oct 26, 2009
 *      Author: johnsekar
 */

#include "../../model_spec/simpleSpecies.hh"
#include "../../model_spec/simpleRxn.hh"

#ifndef SIGNALINGMODEL_HH_
#define SIGNALINGMODEL_HH_

using namespace std;

namespace MoMMA{

	class SignalingModel {

	public:
		int nSpecies;
		SimpleSpecies **species;
		int nRxns;
		SimpleRxn **reaction;

		SignalingModel();
		~SignalingModel();
	};
}


#endif /* SIGNALINGMODEL_HH_ */
