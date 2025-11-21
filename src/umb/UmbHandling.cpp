/*
 * UmbHandling.cpp
 *
 *  Created on: 19.09.2017
 *      Author: mateusz
 */

#include "UmbHandling.h"
#include "Routine26Query.h"
#include "Routine23Query.h"
#include "Routine26AnswerCbk.h"
#include "Routine23AnswerCbk.h"
#include "../types/UmbFrameStructRaw.h"
#include "../types/ChannelValueFoundation.h"
#include "../types/Float.h"
//#include "../aprs/Mappings.h"

#include <string>
#include <iostream>
#include <stdint.h>

UmbHandling::UmbHandling() {
	// TODO Auto-generated constructor stub

}

int UmbHandling::checkStatus(unsigned short deviceId, unsigned short deviceClass, serial& serialPort) {

	UmbFrameRaw f, o;
	memset (&f, 0x00, sizeof(f));

	Routine26Query::prepareQuery(deviceId, deviceClass, &f);
	serialPort.transmitUmb(&f);
	o = serialPort.receiveUmb(2);
	uint8_t s = Routine26AnswerCbk::parseAnswer(o);
	printf("status: %d", s);

	return 0;
}

int UmbHandling::testChannelQuery(serial& serialPort) {
	UmbFrameRaw f, o;
	memset (&f, 0x00, sizeof(f));

	Routine23Query::prepareQuery(0x64, 1, 8, &f);
	serialPort.transmitUmb(&f);
	o = serialPort.receiveUmb(2);
	ChannelValueFoundation *ch = (ChannelValueFoundation*)Routine23AnswerCbk::parseAnswer(o);

	Float *fl = (Float*)ch;
	std::cout << "temperatura: " << fl->toString() << endl;

	delete ch;

	return 0;
}

ChannelValueFoundation*  UmbHandling::channelQuery(unsigned short deviceId,
													unsigned short deviceClass, unsigned short channelNumber,
													serial& serialPort)
{
	UmbFrameRaw f, o;
	memset (&f, 0x00, sizeof(f));


	Routine23Query::prepareQuery(channelNumber, deviceId, deviceClass, &f);

	std::cout << "channelQuery - channel: " << channelNumber << " - ln: " << (int)f.ln <<  std::endl;

	serialPort.transmitUmb(&f);
	o = serialPort.receiveUmb(2);
	ChannelValueFoundation *ch = (ChannelValueFoundation*)Routine23AnswerCbk::parseAnswer(o);

	return ch;
}

UmbHandling::~UmbHandling() {
	// TODO Auto-generated destructor stub
}

