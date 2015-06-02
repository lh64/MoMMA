/*
 * nullTranslator.hh
 *
 *  Created on: Nov 6, 2010
 *      Author: Leonard Harris
 */

#ifndef NULLTRANSLATOR_HH_
#define NULLTRANSLATOR_HH_

#include "../../MoMMA.hh"

using namespace std;

namespace MoMMA{

	class NullTranslator : public Translator{
	public:
		NullTranslator(string name);
		~NullTranslator();
		virtual void translate(Data* inData);
	};
}

#endif /* NULLTRANSLATOR_HH_ */
