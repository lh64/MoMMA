/*
 * trackTranslator.hh
 *
 *  Created on: Apr 22, 2010
 *      Author: Leonard Harris
 */

#ifndef TRACKTRANSLATOR_HH_
#define TRACKTRANSLATOR_HH_

#include "../../MoMMA.hh"

using namespace std;

namespace MoMMA{

	class TrackTranslator : public Translator{
	public:
		double N,M,L;
		TrackTranslator(Data* localData, double N, double M, double L);
		~TrackTranslator();
		void translate(Data* inData);
	};
}

#endif /* TRACKTRANSLATOR_HH_ */
