/*
 * worldTranslator.hh
 *
 *  Created on: Feb 8, 2010
 *      Author: Leonard Harris
 */

#ifndef WORLDTRANSLATOR_HH_
#define WORLDTRANSLATOR_HH_

#include "../../MoMMA.hh"

using namespace std;

namespace MoMMA{

	class WorldTranslator : public Translator{
	public:
		WorldTranslator();
		WorldTranslator(Data* localData);
		~WorldTranslator();
		void translate(Data* inData);
	};
}

#endif /* WORLDTRANSLATOR_HH_ */
