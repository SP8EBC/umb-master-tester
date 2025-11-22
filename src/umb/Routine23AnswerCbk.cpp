/*
 * Routine23AnswerCbk.cpp
 *
 *  Created on: 20.09.2017
 *      Author: mateusz
 */

#include "Routine23AnswerCbk.h"
#include "../types/ChannelType.h"
#include "../types/Float.h"
#include "../types/Integer.h"
#include "../types/UnsignedInteger.h"

#include <cstring>
#include <stdint.h>

#include <cstdio>

std::shared_ptr<spdlog::logger> Routine23AnswerCbk::logger;

Routine23AnswerCbk::Routine23AnswerCbk ()
{
	logger = spdlog::stdout_color_mt ("routine23a");
}

std::shared_ptr<UmbFrameRaw>
Routine23AnswerCbk::createAnswerToMaster (uint8_t status, std::vector<uint16_t> chnsNumber,
										  std::vector<std::shared_ptr<ChannelValueFoundation>> chnsValues,
										  std::shared_ptr<UmbFrameRaw> request)
{
	std::shared_ptr<UmbFrameRaw> out = std::make_shared<UmbFrameRaw>();

	out->fromClass = request->toClass;
	out->toClass = request->fromClass;

	out->fromId = request->toId;
	out->toId = request->fromId;

	out->cmdId = 0x23;

	out->content.push_back(status);

	for (size_t i = 0 ; i < chnsNumber.size(); i++)
	{
		const uint16_t channel = chnsNumber[i];
		const std::shared_ptr<ChannelValueFoundation> value = chnsValues[i];

		out->content.push_back((uint8_t)(channel & 0xFF));
		out->content.push_back((uint8_t)((channel >> 8) & 0xFF));
		auto end = out->content.end();
		value->putInto(out->content, end);
	}

	return out;
}

Routine23AnswerCbk::~Routine23AnswerCbk ()
{
	// TODO Auto-generated destructor stub
}

std::shared_ptr<ChannelValueFoundation> Routine23AnswerCbk::parseAnswer (UmbFrameRaw &in)
{
	std::shared_ptr<ChannelValueFoundation> out;

	float ftemp = 0.0f;

	const std::vector<unsigned char> &content = in.content;

	uint8_t channelNumberL = content[1];
	uint8_t channelNumberH = content[2];

	unsigned short channelNumber = (channelNumberL | channelNumberH << 8);
	unsigned char channelType = content[3];

	switch (channelType) {
	case UNSIGNED_CHAR: {
		out = std::make_shared<UnsignedInteger> ((uint32_t)content[4]);

		break;
	}
	case SIGNED_CHAR: {
		out = std::make_shared<Integer> ((int32_t)content[4]);

		break;
	}
	case UNSIGNED_SHORT: {
		const uint8_t l = content[4];
		const uint8_t h = content[5];

		const uint16_t valueU16 = l | (h << 8);

		out = std::make_shared<UnsignedInteger> ((uint32_t)valueU16);

		break;
	}
	case SIGNED_SHORT: {
		const uint8_t l = content[4];
		const uint8_t h = content[5];

		const int16_t valueI16 = l | (h << 8);

		out = std::make_shared<Integer> ((int32_t)valueI16);

		break;
	}
	case UNSIGNED_INT: {
		const uint8_t l = content[4];
		const uint8_t ll = content[5];
		const uint8_t hh = content[6];
		const uint8_t h = content[7];

		const uint32_t valueU32 = l | (ll << 8) | (hh << 16) | (h << 24);

		out = std::make_shared<UnsignedInteger> ((uint32_t)valueU32);

		break;
	}
	case SIGNED_INT: {
		const uint8_t l = content[4];
		const uint8_t ll = content[5];
		const uint8_t hh = content[6];
		const uint8_t h = content[7];

		const int32_t valueI32 = l | (ll << 8) | (hh << 16) | (h << 24);

		out = std::make_shared<Integer> (valueI32);

		break;
	}
	case FLOAT: {

		memcpy (&ftemp, content.data () + 4, 4);
		out = std::make_shared<Float> (ftemp);

		break;
	}
	case DOUBLE: {

		memcpy (&ftemp, content.data () + 4, 4);
		out = std::make_shared<Float> (ftemp);

		break;
	}
	default: {
		out = std::make_shared<Float> (0.0f);
		break;
	}
	}

//	printf ("parseAnswer - kanal: %d - status: %d - ln: %d - chtype: %d - temp: %d - stemp: %d - "
//			"ftem: %f\r\n",
//			(*(in->content + 1) | *(in->content + 2) << 8),
//			(int)*(in->content),
//			(int)(in->ln),
//			*(in->content + 3),
//			temp,
//			stemp,
//			ftemp);
	return out;
}
