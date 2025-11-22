/*
 * PacketWx.cpp
 *
 *  Created on: 11.09.2017
 *      Author: mateusz
 */

#include <cstdio>
#include <cstring>

#include "PacketWx.h"
#include "PacketFoundation.h"
#include "Call.h"
#include "../config/ProgramConfig.h"
#include "../types/ChannelUsage.h"
#include "../types/MeasurementUnit.h"
#include "../types/Integer.h"
#include "../types/Float.h"
#include "../aux/UnitsConversionMatrix.h"



AprsPacketWx::~AprsPacketWx() {
	// TODO Auto-generated destructor stub
}

AprsPacketWx::AprsPacketWx(AprsCall* s, AprsCall* d,
		map<ChannelUsage, MeasurementUnit>& unit,
		map<ChannelUsage, std::shared_ptr<ChannelValueFoundation>>& values) :
										AprsPacketFoundation(s, d),
										usageUnitMapping(unit),
										usageValuesMapping(values)
{
	direction = 0;
	windspeed = 0.0f;
	gusts = 0.0f;
	temperature = 0.0f;
	humidity = 0;
	qnh = 0;
	qfe = 0;
}

string AprsPacketWx::toString() {
	char cout[190];
	memset(cout, 0x00, 190);

	if (usageValuesMapping[WINDDIR] == NULL) {
		usageValuesMapping[WINDDIR] = std::make_shared<Integer>(0);
	}
	if (usageValuesMapping[WINDSPEED] == NULL) {
		usageValuesMapping[WINDSPEED] = std::make_shared<Float>(0.0f);
	}
	if (usageValuesMapping[WINDGUSTS] == NULL) {
		usageValuesMapping[WINDGUSTS] = std::make_shared<Float>(0.0f);
	}
	if (usageValuesMapping[TEMPERATURE] == NULL) {
		usageValuesMapping[TEMPERATURE] = std::make_shared<Integer>(0);
	}
	if (usageValuesMapping[PRESSURE] == NULL) {
		usageValuesMapping[PRESSURE] = std::make_shared<Integer>(0);
	}
	if (usageValuesMapping[HUMIDITY] == NULL) {
		usageValuesMapping[HUMIDITY] = std::make_shared<Integer>(0);
	}

	float max_wind_speed = 0.0, temp;
	max_wind_speed = this->gusts * 0.1f;		// Wyszukiwane najwiekszej wartosci
	temp = this->windspeed;
	temp /= 0.45;																						// Konwersja na mile na godzine
	max_wind_speed /= 0.45;

	sprintf(cout, "!%s%s%c%s%s%c%s/%sg%st%sr...p...P...b%s0h%s\0",
							ProgramConfig::getLat().c_str(),
							ProgramConfig::getLatns().c_str(),
							'/',
							ProgramConfig::getLon().c_str(),
							ProgramConfig::getLonwe().c_str(),
							'_',
							/* kierunek */usageValuesMapping[WINDDIR]->toAprsConvertedString(usageUnitMapping[WINDDIR],MS).c_str(),
							/* predkosc*/usageValuesMapping[WINDSPEED]->toAprsConvertedString(usageUnitMapping[WINDSPEED],MPH).c_str(),
							/* porywy */usageValuesMapping[WINDGUSTS]->toAprsConvertedString(usageUnitMapping[WINDGUSTS],MPH).c_str(),
							/*temperatura */usageValuesMapping[TEMPERATURE]->toAprsConvertedString(usageUnitMapping[TEMPERATURE],DEGF).c_str(),
							usageValuesMapping[PRESSURE]->toAprsConvertedString(usageUnitMapping[PRESSURE],HPA).c_str(),
							/* wilgotnosc */usageValuesMapping[HUMIDITY]->toAprsConvertedString(HPA,HPA).substr(1, 2).c_str()
);

	string out(cout);

	return out;

}

