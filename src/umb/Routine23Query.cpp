/*
 * Routine23Query.cpp
 *
 *  Created on: 20.09.2017
 *      Author: mateusz
 */

#include "Routine23Query.h"

Routine23Query::Routine23Query() {
	// TODO Auto-generated constructor stub

}

Routine23Query::~Routine23Query() {
	// TODO Auto-generated destructor stub
}

void Routine23Query::prepareQuery(unsigned short channelNumber,
							unsigned char deviceId,
							unsigned char deviceClass,
							UmbFrameRaw &out)
{
	if (out != 0x00) {
		out->cmdId = 0x23U;
		out->slaveId = deviceId;
		out->slaveClass = deviceClass;

		out->content = new unsigned char[2];
		*(out->content) = (unsigned char)(channelNumber & 0xFF);
		*(out->content + 1) = (unsigned char)((channelNumber & 0xFF00) >> 8);

		out->ln = 0x04U;		// data length between STX and ETX
	}

}
