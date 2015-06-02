/*
 * translators_MM1.hh
 *
 *  Created on: Dec 4, 2010
 *      Author: Leonard Harris
 */

#ifndef TRANSLATORS_MM1_HH_
#define TRANSLATORS_MM1_HH_

#include "../../../MoMMA.hh"
#include "../../../borrowed/primitiveData.hh"

using namespace std;

namespace MoMMA{

	class SlowTranslator_MM1 : public Translator{
	public:
		double kcat;
		SlowTranslator_MM1();
		SlowTranslator_MM1(DoublePtrData* localData, double kcat);
		~SlowTranslator_MM1(){}
		virtual void translate(Data* inData);
	};

	class FastTranslator_MM1 : public Translator{
	public:
		FastTranslator_MM1();
		FastTranslator_MM1(DoublePtrVectorData* localData);
		~FastTranslator_MM1(){}
		virtual void translate(Data* inData);
	};
}

#endif /* TRANSLATORS_MM1_HH_ */
