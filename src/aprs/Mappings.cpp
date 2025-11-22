/*
 * UsageUnitMapping.cpp
 *
 *  Created on: 26.09.2017
 *      Author: mateusz
 */

#include "Mappings.h"

map<ChannelUsage, MeasurementUnit> Mappings::usageUnitMapping;
map<ChannelUsage, std::shared_ptr<ChannelValueFoundation>> Mappings::usageValuesMapping;

Mappings::Mappings() {
	// TODO Auto-generated constructor stub

}

Mappings::~Mappings() {
	// TODO Auto-generated destructor stub
}

