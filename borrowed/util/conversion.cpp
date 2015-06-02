/**
 * @file conversion.cpp
 *
 * Implementation of the conversion methods.
 *
 * @date Oct 14th, 2009   last edited: Oct 14th, 2009
 *
 * @author Michael Sneddon
 */




#include "conversion.hh"
#include "../exception.hh"

using namespace Util;

double Util::convertToDouble(const std::string& s)
{
	bool failIfLeftoverChars = true;
	std::istringstream i(s);
	double x;
	char c;
	if (!(i >> x) || (failIfLeftoverChars && i.get(c)))
		throw MoMMA::HiveException("Cannot convert string to double value.","Util::convertToDouble(\"" + s + "\")");
	return x;
}


int Util::convertToInt(const std::string& s)
{
	bool failIfLeftoverChars = true;
	std::istringstream i(s);
	int x;
	char c;
	if (!(i >> x) || (failIfLeftoverChars && i.get(c)))
		throw MoMMA::HiveException("Cannot convert string to int value.","Util::convertToInt(\"" + s + "\")");
	return x;
}


string Util::toString(double x)
{
	std::ostringstream o;
	if (!(o << x))
		throw MoMMA::HiveException("Cannot convert double to string value.","Util::toString(double x)");
	return o.str();
}


string Util::toString(int x)
{
	std::ostringstream o;
	if (!(o << x))
		throw MoMMA::HiveException("Cannot convert int to string value.","Util::toString(int x)");
	return o.str();
}
