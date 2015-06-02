/*
 * trivialTranslator.hh
 *
 *  Created on: Feb 13, 2010
 *      Author: Leonard Harris
 */

#ifndef TRIVIALTRANSLATOR_HH_
#define TRIVIALTRANSLATOR_HH_

#include "../../MoMMA.hh"

using namespace std;

namespace MoMMA{

	class TrivialTranslator : public Translator{
	public:
		TrivialTranslator();
		TrivialTranslator(Data* localData);
		~TrivialTranslator(){}
		virtual void translate(Data* inData);
	};
}

#endif /* TRIVIALTRANSLATOR_HH_ */
