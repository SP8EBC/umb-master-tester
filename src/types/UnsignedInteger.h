/*
 * UnsignedInteger.h
 *
 *  Created on: Nov 21, 2025
 *      Author: mateusz
 */

#ifndef SRC_TYPES_UNSIGNEDINTEGER_H_
#define SRC_TYPES_UNSIGNEDINTEGER_H_

#include "ChannelValueFoundation.h"

#include <cstdint>

class UnsignedInteger : public ChannelValueFoundation {

	uint32_t store;

	static const string type;

public:
	UnsignedInteger();
	UnsignedInteger(uint32_t init);
	virtual ~UnsignedInteger();

	virtual string getType();
	virtual string toAprsConvertedString(MeasurementUnit from, MeasurementUnit to);
	virtual string toString();
	virtual void putInto (std::vector<uint8_t> &vector, std::vector<uint8_t>::iterator &from);

	int getValue() const;
	void setValue(int store);
};

#endif /* SRC_TYPES_UNSIGNEDINTEGER_H_ */
