/*
 * UnsignedInteger.cpp
 *
 *  Created on: Nov 21, 2025
 *      Author: mateusz
 */

#include "UnsignedInteger.h"
#include "../aux/UnitsConversionMatrix.h"

#include <cmath>
#include <cstdio>
#include <sstream>
// UnsignedInteger::UnsignedInteger ()
//{
//	// TODO Auto-generated constructor stub
// }
//
// UnsignedInteger::~UnsignedInteger ()
//{
//	// TODO Auto-generated destructor stub
// }

const string UnsignedInteger::type = "int";

UnsignedInteger::UnsignedInteger ()
{
	value = &this->store;
}

UnsignedInteger::~UnsignedInteger ()
{
}

string UnsignedInteger::getType ()
{
	return UnsignedInteger::type;
}

string UnsignedInteger::toAprsConvertedString (MeasurementUnit from, MeasurementUnit to)
{
	float output = (float)this->store * UnitsConversionMatrix::conversionMatrix[from][to];
	if (to == DEGF) {
		output += 32.0f;
	}

	char s[4] = {0, 0, 0, 0};

	sprintf (s, "%03d", (int)round (output));

	string o (s);

	return o;
}

int UnsignedInteger::getValue () const
{
	return store;
}

UnsignedInteger::UnsignedInteger (uint32_t init)
{
	store = init;
	value = &this->store;
}

void UnsignedInteger::putInto (std::vector<uint8_t> &vector, std::vector<uint8_t>::iterator &from)
{
}

void UnsignedInteger::setValue (int store)
{
	this->store = store;
}

string UnsignedInteger::toString ()
{
	stringstream out;
	out << this->store;

	return out.str ();
}
