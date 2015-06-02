/*
 * stringData.hh
 *
 *  Created on: Feb 12, 2010
 *      Author: Leonard Harris
 */

#ifndef STRINGDATA_HH_
#define STRINGDATA_HH_

#include "../../MoMMA.hh"
//#include "../../../../agent/data/data.hh"

#include <iostream>
#include <vector>

using namespace std;


namespace MoMMA{

	class StringData : public Data{
	public:
		StringData(string dataName, string value);

		virtual ~StringData(){}

		void printContent(ostream& out);

		string getString(){ return this->string_value; }

//		virtual Data* copyOf(){
//			return new StringData(this->getName(),this->getString());
//		}

	private:
		string string_value;
	};

	class StringPtrData : public Data{
	public:
		/// default-constructor
		StringPtrData(string dataName, string* ptr);

		virtual ~StringPtrData(){}

		void printContent(ostream& out);

		string* getStringPtr(){ return string_ptr; };

		void setStringPtr(string* new_ptr){ string_ptr = new_ptr; };

		virtual Data* convertToNonPtr(){
			return new StringData(this->getName(),*this->getStringPtr());
		}

	private:
		string* string_ptr;
	};
}

#endif /* STRINGDATA_HH_ */
