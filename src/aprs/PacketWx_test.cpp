/*
 * PacketWx_test.cpp
 *
 *  Created on: 11.09.2017
 *      Author: mateusz
 */

#include "PacketWx.h"
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE PACKETWX
#include <boost/test/unit_test.hpp>
#include <iostream>

#include "../config/ProgramConfig.h"
#include "../types/ChannelType.h"
#include "../types/ChannelUsage.h"

#include "../types/Integer.h"
#include "../types/Float.h"


#include "Mappings.h"

BOOST_AUTO_TEST_CASE(basic)
{

	AprsPacketWx* p;
	AprsCall s("nocall", 1), d("nocall", 10);

	ProgramConfig::readConfigFromFile();

	Mappings::usageUnitMapping[WINDDIR] = MS;
	Mappings::usageUnitMapping[WINDSPEED] = MS;
	Mappings::usageUnitMapping[WINDGUSTS] = MS;
	Mappings::usageUnitMapping[TEMPERATURE] = DEGC;
	Mappings::usageUnitMapping[PRESSURE] = HPA;


	Mappings::usageValuesMapping[WINDDIR] = (void*)new Integer(2);
	Mappings::usageValuesMapping[WINDSPEED] = (void*)new Float(3.2f);
	Mappings::usageValuesMapping[WINDGUSTS] = (void*)new Float(4.9f);
	Mappings::usageValuesMapping[TEMPERATURE] = (void*)new Float(-3.0f);
	Mappings::usageValuesMapping[PRESSURE] = (void*)new Float(1013.25f);

	p = new AprsPacketWx(&s, &d, Mappings::usageUnitMapping, Mappings::usageValuesMapping);

	string o = p->toString();

	std::cout << o << std::endl;

	BOOST_CHECK( o == "" );
}
