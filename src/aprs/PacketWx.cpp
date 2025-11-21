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
		map<ChannelUsage, void*>& values) :
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
		usageValuesMapping[WINDDIR] = new Integer(0);
	}
	if (usageValuesMapping[WINDSPEED] == NULL) {
		usageValuesMapping[WINDSPEED] = new Float(0.0f);
	}
	if (usageValuesMapping[WINDGUSTS] == NULL) {
		usageValuesMapping[WINDGUSTS] = new Float(0.0f);
	}
	if (usageValuesMapping[TEMPERATURE] == NULL) {
		usageValuesMapping[TEMPERATURE] = new Integer(0);
	}
	if (usageValuesMapping[PRESSURE] == NULL) {
		usageValuesMapping[PRESSURE] = new Integer(0);
	}
	if (usageValuesMapping[HUMIDITY] == NULL) {
		usageValuesMapping[HUMIDITY] = new Integer(0);
	}

	float max_wind_speed = 0.0, temp;
	unsigned char wind_speed_mph, wind_gusts_mph;
	max_wind_speed = this->gusts * 0.1f;		// Wyszukiwane najwiekszej wartosci
	temp = this->windspeed;
	temp /= 0.45;																						// Konwersja na mile na godzine
	max_wind_speed /= 0.45;
	if ((temp - (short)temp) >= 0.5)												// Zaokraglanie wartosci
		/* Odejmuje od wartosci zmiennoprzecinkowej w milach nad godzine wartosc
			 po zrzutowaniu na typ short czyli z odcienta czescia po przecinku.
			 Jezeli wynik jest wiekszy albo rowny 0.5 to trzeba zaokraglic w gore */
		wind_speed_mph = (short)temp + 1;
	else
		/* A jezeli jest mniejsza niz 0.5 to zaokraglamy w dol */
		wind_speed_mph = (short)temp;
	if ((max_wind_speed - (short)max_wind_speed) >= 0.5)
		/* Analogiczna procedura ma miejsce dla porywow wiatru*/
		wind_gusts_mph = (short)max_wind_speed + 1;
	else
		wind_gusts_mph = (short)max_wind_speed;
	sprintf(cout, "!%s%s%c%s%s%c%s/%sg%st%sr...p...P...b%s0h%s\0",
							ProgramConfig::getLat().c_str(),
							ProgramConfig::getLatns().c_str(),
							'/',
							ProgramConfig::getLon().c_str(),
							ProgramConfig::getLonwe().c_str(),
							'_',
							/* kierunek */static_cast<ChannelValueFoundation*>(usageValuesMapping[WINDDIR])->toAprsConvertedString(usageUnitMapping[WINDDIR],MS).c_str(),
							/* predkosc*/static_cast<ChannelValueFoundation*>(usageValuesMapping[WINDSPEED])->toAprsConvertedString(usageUnitMapping[WINDSPEED],MPH).c_str(),
							/* porywy */static_cast<ChannelValueFoundation*>(usageValuesMapping[WINDGUSTS])->toAprsConvertedString(usageUnitMapping[WINDGUSTS],MPH).c_str(),
							/*temperatura */static_cast<ChannelValueFoundation*>(usageValuesMapping[TEMPERATURE])->toAprsConvertedString(usageUnitMapping[TEMPERATURE],DEGF).c_str(),
							static_cast<ChannelValueFoundation*>(usageValuesMapping[PRESSURE])->toAprsConvertedString(usageUnitMapping[PRESSURE],HPA).c_str(),
							/* wilgotnosc */static_cast<ChannelValueFoundation*>(usageValuesMapping[HUMIDITY])->toAprsConvertedString(HPA,HPA).substr(1, 2).c_str()
);

	string out(cout);

	return out;

}

