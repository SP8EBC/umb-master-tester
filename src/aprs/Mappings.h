/*
 * UsageUnitMapping.h
 *
 *  Created on: 26.09.2017
 *      Author: mateusz
 */

#ifndef TYPES_MAPPINGS_H_
#define TYPES_MAPPINGS_H_

#include "../types/MeasurementUnit.h"
#include "../types/ChannelUsage.h"
#include "../types/ChannelValueFoundation.h"

#include <map>

using namespace std;

class Mappings {
	//TODO: Naprawić wyciek pamięci!!!
public:
	static map<ChannelUsage, MeasurementUnit> usageUnitMapping;
	static map<ChannelUsage, void*> usageValuesMapping;

	Mappings();
	virtual ~Mappings();
};

#endif /* TYPES_MAPPINGS_H_ */
