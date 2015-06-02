/*
 * stringData.cpp
 *
 *  Created on: Jun 19, 2010
 *      Author: Leonard Harris
 */

#include <iostream>
#include <string>
#include "stringData.hh"

using namespace std;
using namespace MoMMA;

StringData::StringData(string dataName, string value) : Data(dataName,"StringType"){
	this->string_value = value;
}

void StringData::printContent(ostream& out) {
//	out << "[DATA] type=\""<<datatype<<"\" name=\""<<dataName<<"\" value="<<string_value << endl;
	out << this->string_value;
}

StringPtrData::StringPtrData(string dataName, string* ptr) : Data(dataName,"StringPtrType"){
	this->string_ptr = ptr;
}

void StringPtrData::printContent(ostream& out) {
//	out << "[DATA] type=\""<<datatype<<"\" name=\""<<dataName<<"\" value="<<*string_ptr << endl;
	out << *this->string_ptr;
}
