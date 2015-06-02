/**
 * @file primitiveData.hh
 *
 * this file contains the interfaces to the primitive Data classes, such as
 * Integer, Double, boolean, etc.
 *
 *
 * @date Oct 14, 2009  Last edited: Oct 23, 2009 Michael and Garrit
 *
 * @author Michael Sneddon
 */

#ifndef PRIMITIVEDATA_HPP_
#define PRIMITIVEDATA_HPP_


#include "data.hh"

#include <iostream>
#include <vector>

using namespace std;


namespace MoMMA
{


	/**
	 * @brief A data object to store integer values
	 * @date Oct 14, 2009 Last edited: Oct 14, 2009 by Garrit and Michael
	 * @author Michael Sneddon
	 */
	class IntegerData : public Data {
		public:
			IntegerData(string dataName, int value);
			virtual ~IntegerData() {};

			void printContent(ostream &out);

			int getInteger() const { return integerValue; };
			void setInteger(int newValue) { integerValue = newValue; };

			//*****
//			virtual Data* copyOf(){
//				return new IntegerData(this->getName(),this->getInteger());
//			}
			//*****

		private:
			int integerValue;
	};


	/**
	 * @brief A data object to store double values
	 * @date Oct 14, 2009 Last edited: Oct 14, 2009 by Garrit and Michael
	 * @author Garrit Jentsch
	 */
	class DoubleData : public Data {
		public:
			/// default-constructor
			DoubleData(string dataName, double value);

			virtual ~DoubleData() {};

			/// virtual method for print the content of a data item on sterr.
			void printContent(ostream &out);

			/// adding to the stored value
			void addToValue(double d) { doubleValue += d; };

			/// subtracting from the stored value
			void subtractFromValue(double d) { doubleValue -= d; };

			double getDouble() const { return doubleValue; };
			void setDouble(double newValue) { doubleValue = newValue; };

			//*****
//			virtual Data* copyOf(){
//				return new DoubleData(this->getName(),this->getDouble());
//			}
			//*****

		private:
				double doubleValue;

	};

	/// bullshit!
	class DoublePtrData : public Data {
	public:
		/// default-constructor
		DoublePtrData(string dataName, double* ptr);

		virtual ~DoublePtrData() {};

		void printContent(ostream& out);

		double* getDoublePtr() { return double_ptr; };

		void setDoublePtr(double* new_ptr) { double_ptr = new_ptr; };

		//*****
		virtual Data* convertToNonPtr(){
			return new DoubleData(this->getName(),*this->getDoublePtr());
		}
		//*****

	private:
		double* double_ptr;
	};

	//********************
	class IntPtrData : public Data {
	public:
		/// default-constructor
		IntPtrData(string dataName, int* ptr);

		virtual ~IntPtrData() {};

		void printContent(ostream& out);

		int* getIntPtr() { return int_ptr; };

		void setIntPtr(int* new_ptr) { int_ptr = new_ptr; };

		//*****
		virtual Data* convertToNonPtr(){
			return new IntegerData(this->getName(),*this->getIntPtr());
		}
		//*****

	private:
		int* int_ptr;
	};
	//********************

	/**
	 * @brief A data object to store bool values
	 * @date Oct 14, 2009 Last edited: Oct 14, 2009 by Garrit and Michael
	 * @author Michael Sneddon
	 */
	class BoolData : public Data {
		public:
			BoolData(string dataName, bool value);
			virtual ~BoolData() {};

			void printContent(ostream &out);


			bool getBool() const { return boolValue; };
			void setBool(bool newValue) { boolValue = newValue; };

		private:
			bool boolValue;
	};

	/**
	 * @brief A data object to store a simple int vector
	 * @date Oct, 21, 2009
	 * @author garrit jentsch
	 */
	class IntVectorData : public Data {
	public:
		/// default constructor
		IntVectorData(string dataName, int number_of_elements);

		virtual ~IntVectorData() {};

		void printContent(ostream &out);

		int getInt(int pos) const { return vec[pos]; };
		void setInt(int new_value, int pos) { vec[pos] = new_value; };
		void setNumElements(int num_ele) { vec.resize(num_ele); };
		int getNumElements() { return int(vec.size()); };
		void addElementToEnd(int new_value) { vec.push_back(new_value); };

	private:
		vector<int> vec;
	};

	//********************
	class IntPtrVectorData : public Data{
	public:
		IntPtrVectorData(string dataName, int number_of_elements);

		virtual ~IntPtrVectorData() {};

		void printContent(ostream &out);

		int* getIntPtr(int pos) const { return vec[pos]; };
		void setIntPtr(int* newPtr, int pos) { vec[pos] = newPtr; };
		void setNumElements(int num_ele) { vec.resize(num_ele); };
		int getNumElements() { return int(vec.size()); };
		void addElementToEnd(int* new_value) { vec.push_back(new_value); };

	private:
		vector<int*> vec;
	};
	//********************

	/**
	 * @brief A data object to store a double vector
	 * @date 10-22-09
	 * @author garrit
	 */
	class DoubleVectorData : public Data {
	public:
		/// default constructor
		DoubleVectorData(string dataName, int number_of_elements);

		virtual ~DoubleVectorData() {};

		void printContent(ostream &out);

		double getDouble(int pos) const { return vec[pos];};
		void setDouble(double new_value, int pos) { vec[pos] = new_value; };
		void setNumElements(int num_ele) { vec.resize(num_ele); };
		int getNumElements() { return int(vec.size()); };
		void addElementToEnd(double new_value) { vec.push_back(new_value); };

	private:
		vector<double> vec;
	};

	//********************
	class DoublePtrVectorData : public Data {
	public:
		/// default constructor
		DoublePtrVectorData(string dataName, int number_of_elements);

		virtual ~DoublePtrVectorData() {};

		void printContent(ostream &out);

		double* getDoublePtr(int pos) const { return vec[pos];};
		void setDoublePtr(double* newPtr, int pos) { vec[pos] = newPtr; };
		void setNumElements(int num_ele) { vec.resize(num_ele); };
		int getNumElements() { return int(vec.size()); };
		void addElementToEnd(double* new_ptr) { vec.push_back(new_ptr); };

	private:
		vector<double*> vec;
	};
	//********************

	/**
	 * @brief a simple matrix implementation with doubles
	 *
	 * @date 10-22-09
	 * @author garrit
	 */
	class DoubleMatrixData : public Data {
	public:
		DoubleMatrixData(string dataName, int xdim, int ydim);

		virtual ~DoubleMatrixData() {};

		void printContent(ostream &out);

		double getDouble(int xpos, int ypos) const { return mat[xpos][ypos]; };
		int getSizeXDim() { return int(mat.size()); };
		void setDouble(double newValue, int xpos, int ypos) { mat[xpos][ypos] = newValue; };
		void setDimensions(int xdim, int ydim);

	private:
		vector<vector<double> > mat;

	};

	//********************
	class DoublePtrMatrixData : public Data {
	public:
		DoublePtrMatrixData(string dataName, int xdim, int ydim);

		virtual ~DoublePtrMatrixData() {};

		void printContent(ostream &out);

		double* getDoublePtr(int xpos, int ypos) const { return mat[xpos][ypos]; };
		int getSizeXDim() { return int(mat.size()); };
		void setDoublePtr(double* newPtr, int xpos, int ypos) { mat[xpos][ypos] = newPtr; };
		void setDimensions(int xdim, int ydim);

	private:
		vector<vector<double*> > mat;

	};

	class DoubleMatrixPtrData : public Data {
	public:
		DoubleMatrixPtrData(string dataName, vector<vector<double> >* mat);
		virtual ~DoubleMatrixPtrData(){};
		void printContent(ostream &out);

		vector<vector<double> >* mat;
	private:

	};
	//********************
}


#endif /* PRIMITIVEDATA_HPP_ */
