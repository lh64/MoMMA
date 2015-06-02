/*
 * commTranslator.hh
 *
 *  Created on: Feb 13, 2010
 *      Author: Leonard Harris
 */

#ifndef COMMTRANSLATOR_HH_
#define COMMTRANSLATOR_HH_

#include "../../MoMMA.hh"
//#include "../../../../agent/data/data.hh"
//#include "../../translator.hh"

using namespace std;

namespace MoMMA{

	class CommTranslator : public Translator{
	public:
		CommTranslator(Data* localData);
		~CommTranslator();
		void translate(Data* inData);
	};
}

#endif /* COMMTRANSLATOR_HH_ */
