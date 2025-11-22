/*
 * Integer.cpp
 *
 *  Created on: 16.09.2017
 *      Author: mateusz
 */

#include "Integer.h"
#include "ChannelType.h"
#include "../aux/UnitsConversionMatrix.h"

#include <cmath>
#include <cstdio>
#include <sstream>

#include <boost/core/span.hpp>

using namespace std;

const string Integer::type = "int";

Integer::Integer ()
{
	// TODO Auto-generated constructor stub
	value = &this->store;
}

Integer::~Integer ()
{
	// TODO Auto-generated destructor stub
}

string Integer::getType ()
{
	return Integer::type;
}

string Integer::toAprsConvertedString (MeasurementUnit from, MeasurementUnit to)
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

int Integer::getValue () const
{
	return store;
}

Integer::Integer (int init)
{
	store = init;
	value = &this->store;
}

void Integer::putInto (std::vector<uint8_t> &vector, std::vector<uint8_t>::iterator &from)
{
	vector.push_back(UNSIGNED_INT);	// channel type

	// and its value
	void* ptr = &this->store;
	boost::span<uint8_t, sizeof(int32_t)> s((uint8_t*)ptr, sizeof(int32_t));
	vector.insert(from, s.begin(), s.end());
}

void Integer::setValue (int store)
{
	this->store = store;
}

string Integer::toString ()
{
	stringstream out;
	out << this->store;

	return out.str ();
}
