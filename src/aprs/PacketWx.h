/*
 * PacketWx.h
 *
 *  Created on: 11.09.2017
 *      Author: mateusz
 */

#ifndef APRS_PACKETWX_H_
#define APRS_PACKETWX_H_

#include "PacketFoundation.h"
#include "Mappings.h"

#include <string>

class AprsPacketWx: public AprsPacketFoundation {
private:
	unsigned short direction;
	float windspeed, gusts;

	float temperature;
	unsigned char humidity;
	unsigned short qnh, qfe;

	map<ChannelUsage, MeasurementUnit> &usageUnitMapping;
	map<ChannelUsage, void*> &usageValuesMapping;


public:
	AprsPacketWx(AprsCall* s, AprsCall* d, map<ChannelUsage, MeasurementUnit>& unit, map<ChannelUsage, void*>& values);
	virtual ~AprsPacketWx();

	string toString();
};

#endif /* APRS_PACKETWX_H_ */
