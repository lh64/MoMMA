/**
 * @file primitiveData.cpp
 *
 * this file contains the interfaces to the classes Data, ...
 *
 *
 * @date Oct 14, 2009  Last edited: Oct 14, 2009
 *
 * @author Michael Sneddon
 */

#include "primitiveData.hh"

using namespace MoMMA;


IntegerData::IntegerData(string dataName, int value) : Data(dataName,"IntegerType") {
	this->integerValue=value;
}

void IntegerData::printContent(ostream& out)
{
//	out<<"[DATA] type=\""<<datatype<<"\" name=\""<<dataName<<"\" value="<<integerValue << endl;
	out << this->integerValue;
}

DoubleData::DoubleData(string dataName, double value) : Data(dataName,"DoubleType") {
	this->doubleValue=value;
}
void DoubleData::printContent(ostream& out)
{
//	out<<"[DATA] type=\""<<datatype<<"\" name=\""<<dataName<<"\" value="<<doubleValue << endl;
	out << this->doubleValue;
}

DoublePtrData::DoublePtrData(string dataName, double* ptr) : Data(dataName,"DoublePtrType") {
	this->double_ptr = ptr;
}

void DoublePtrData::printContent(ostream& out) {
//	out << "[DATA] type=\""<<datatype<<"\" name=\""<<dataName<<"\" value="<<*double_ptr << endl;
	out << *this->double_ptr;
}

IntPtrData::IntPtrData(string dataName, int *ptr) : Data(dataName,"IntPtrType") {
	this->int_ptr = ptr;
}

void IntPtrData::printContent(ostream& out) {
//	out << "[DATA] type=\""<<datatype<<"\" name=\""<<dataName<<"\" value="<<*int_ptr << endl;
	out << *this->int_ptr;
}

BoolData::BoolData(string dataName, bool value) : Data(dataName,"BoolType") {
	this->boolValue=value;
}
void BoolData::printContent(ostream& out){
//	out<<"[DATA] type=\""<<datatype<<"\" name=\""<<dataName<<"\" value="<<boolValue << endl;
	out << this->boolValue;
}

IntVectorData::IntVectorData(string dataName, int number_of_elements) : Data(dataName,"IntVectorType") {
	this->vec.resize(number_of_elements);
}

void IntVectorData::printContent(ostream& out) {
//	out << "[DATA] type=\""<<datatype << "\" name=\""<<dataName<<"\" value=";
	for (unsigned int i=0;i < this->vec.size();i++)
		out << this->vec.at(i) << "\t";
//	out << endl;
}

IntPtrVectorData::IntPtrVectorData(string dataName, int number_of_elements) : Data(dataName,"IntPtrVectorType") {
	this->vec.resize(number_of_elements);
}

void IntPtrVectorData::printContent(ostream& out) {
//	out << "[DATA] type=\""<<datatype << "\" name=\""<<dataName<<"\" value=";
	for (unsigned int i=0;i < this->vec.size();i++)
		out << *this->vec.at(i) << "\t";
//	out << endl;
}

DoubleVectorData::DoubleVectorData(string dataName, int number_of_elements) : Data (dataName,"DoubleVectorType"){
	this->vec.resize(number_of_elements);
}

void DoubleVectorData::printContent(ostream& out) {
//	out << "[DATA] type=\""<<datatype << "\" name=\""<<dataName<<"\" value=";
	for (unsigned int i=0;i < this->vec.size();i++)
		out << this->vec.at(i) << "\t";
//	out << endl;
}

DoublePtrVectorData::DoublePtrVectorData(string dataName, int number_of_elements) : Data(dataName,"DoublePtrVectorType") {
	this->vec.resize(number_of_elements);
}

void DoublePtrVectorData::printContent(ostream& out) {
//	out << "[DATA] type=\""<<datatype << "\" name=\""<<dataName<<"\" value=";
	for (unsigned int i=0;i < this->vec.size();i++)
		out << *this->vec.at(i) << "\t";
//	out << endl;
}

DoubleMatrixData::DoubleMatrixData(string dataName, int xdim, int ydim) : Data(dataName, "DoubleMatrixType") {
	this->mat.resize(xdim);
	for (int i=0; i<xdim; i++)
		mat[i].resize(ydim);
}

void DoubleMatrixData::printContent(ostream& out) {
	for (unsigned int i=0; i<mat.size(); i++) {
		for (unsigned int j=0; j<mat[i].size(); j++)
			out << mat[i][j] << "\t";
		out << endl;
	}
}

void DoubleMatrixData::setDimensions(int xdim, int ydim) {
	this->mat.resize(xdim);
	for (int i=0; i<xdim; i++)
		mat[i].resize(ydim);
}

//********************

DoublePtrMatrixData::DoublePtrMatrixData(string dataName, int xdim, int ydim) : Data(dataName, "DoublePtrMatrixType") {
	this->mat.resize(xdim);
	for (int i=0; i<xdim; i++)
		mat[i].resize(ydim);
}

void DoublePtrMatrixData::printContent(ostream& out) {
	for (unsigned int i=0; i<mat.size(); i++) {
		for (unsigned int j=0; j<mat[i].size(); j++)
			out << *mat[i][j] << "\t";
		out << endl;
	}
}

void DoublePtrMatrixData::setDimensions(int xdim, int ydim) {
	this->mat.resize(xdim);
	for (int i=0; i<xdim; i++)
		mat[i].resize(ydim);
}

//********************

DoubleMatrixPtrData::DoubleMatrixPtrData(string dataName, vector<vector<double> >* mat) : Data(dataName,
																								"DoubleMatrixPtrType") {
	this->mat = mat;
}

void DoubleMatrixPtrData::printContent(ostream& out) {
	for (unsigned int i=0;i < this->mat->size();i++) {
		for (unsigned int j=0;j < this->mat[i].size();j++)
			out << this->mat->at(i)[j] << "\t";
		out << endl;
	}
}
