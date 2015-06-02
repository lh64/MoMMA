/*
 * translator.hh
 *
 *  Created on: Feb 4, 2010
 *      Author: Leonard Harris
 */

#ifndef TRANSLATOR_HH_
#define TRANSLATOR_HH_

#include "../MoMMA.hh"

using namespace std;

namespace MoMMA{

	class Translator{

	public:
		Translator();
		Translator(Data* localData);
		virtual ~Translator();
		void addData(Data* localData){ this->localData = localData; }
		Data* getData(){ return this->localData; }
		string getName(){ return this->localData->getName(); }
		virtual void translate(Data* inData);
		virtual void translate(Data inData);

	protected:
		Data* localData;
	};
}

#endif /* TRANSLATOR_HH_ */
