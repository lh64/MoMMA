/*
 * cellTranslator.hh
 *
 *  Created on: Feb 5, 2010
 *      Author: Leonard Harris
 */

#ifndef CELLTRANSLATOR_HH_
#define CELLTRANSLATOR_HH_

#include "../../MoMMA.hh"

using namespace std;

namespace MoMMA{

	class CellTranslator : public Translator{
	public:
		CellTranslator();
		CellTranslator(Data* localData);
		~CellTranslator();
		void translate(Data* inData);
	};
}

#endif /* CELLTRANSLATOR_HH_ */
