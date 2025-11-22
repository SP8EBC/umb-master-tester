/*
 * UmbHandling.cpp
 *
 *  Created on: 19.09.2017
 *      Author: mateusz
 */

#include "UmbHandling.h"
#include "../types/ChannelValueFoundation.h"
#include "../types/Float.h"
#include "../types/UmbFrameStructRaw.h"
#include "Routine23AnswerCbk.h"
#include "Routine23Query.h"
#include "Routine26AnswerCbk.h"
#include "Routine26Query.h"
// #include "../aprs/Mappings.h"

#include <iostream>
#include <stdint.h>
#include <string>

UmbHandling::UmbHandling ()
{
	// TODO Auto-generated constructor stub
}

int UmbHandling::checkStatus (unsigned short deviceId, unsigned short deviceClass,
							  serial &serialPort)
{

	UmbFrameRaw f;

	Routine26Query::prepareQuery (deviceId, deviceClass, f);
	serialPort.transmitUmb (&f);
	std::shared_ptr<UmbFrameRaw> o = serialPort.receiveUmb (2);
	if (o) {
		uint8_t s = Routine26AnswerCbk::parseAnswer (*o);
		printf ("status: %d", s);
	}

	return 0;
}

int UmbHandling::testChannelQuery (serial &serialPort)
{
	UmbFrameRaw f;

	Routine23Query::prepareQuery (0x64, 1, 8, f);
	serialPort.transmitUmb (&f);

	std::shared_ptr<UmbFrameRaw> o = serialPort.receiveUmb (2);
	if (o) {
		std::shared_ptr<ChannelValueFoundation> ch = Routine23AnswerCbk::parseAnswer (*o);

		std::cout << "temperatura: " << ch->toString () << endl;
	}

	return 0;
}

std::shared_ptr<ChannelValueFoundation> UmbHandling::channelQuery (unsigned short deviceId,
																   unsigned short deviceClass,
																   unsigned short channelNumber,
																   serial &serialPort)
{
	UmbFrameRaw f;

	std::shared_ptr<ChannelValueFoundation> ch;

	Routine23Query::prepareQuery (channelNumber, deviceId, deviceClass, f);

	std::cout << "channelQuery - channel: " << channelNumber << " - ln: " << (int)f.ln << std::endl;

	serialPort.transmitUmb (&f);
	std::shared_ptr<UmbFrameRaw> o = serialPort.receiveUmb (2);
	if (o) {
		ch = Routine23AnswerCbk::parseAnswer (*o);

		std::cout << "temperatura: " << ch->toString () << endl;
	}

	return ch;

}

UmbHandling::~UmbHandling ()
{
	// TODO Auto-generated destructor stub
}
