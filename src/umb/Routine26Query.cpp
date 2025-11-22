/*
 * Routine26Query.cpp
 *
 *  Created on: 23.09.2017
 *      Author: mateusz
 */

#include "Routine26Query.h"

#include "../config/ProgramConfig.h"

Routine26Query::Routine26Query ()
{
	// TODO Auto-generated constructor stub
}

void Routine26Query::prepareQuery (unsigned char deviceId, unsigned char deviceClass,
								   UmbFrameRaw &out)
{

	out.cmdId = 0x26U;
	out.toId = deviceId;
	out.toClass = deviceClass;

	out.fromId =  ProgramConfig::getMasterId ();
	out.toId = 0xF0;

	out.content.push_back(0x00);

	out.ln = 0x02U; // data length between STX and ETX
}

Routine26Query::~Routine26Query ()
{
	// TODO Auto-generated destructor stub
}
