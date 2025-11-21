/*
 * Routine26Query.cpp
 *
 *  Created on: 23.09.2017
 *      Author: mateusz
 */

#include "Routine26Query.h"

Routine26Query::Routine26Query() {
	// TODO Auto-generated constructor stub

}

void Routine26Query::prepareQuery(unsigned char deviceId, unsigned char deviceClass, UmbFrameRaw& out)
{

	if (out != 0x00) {
		out->cmdId = 0x26U;
		out->slaveId = deviceId;
		out->slaveClass = deviceClass;

		out->content = new unsigned char[1];
		*(out->content) = 0x00;

		out->ln = 0x02U;		// data length between STX and ETX
	}

}

Routine26Query::~Routine26Query() {
	// TODO Auto-generated destructor stub
}

