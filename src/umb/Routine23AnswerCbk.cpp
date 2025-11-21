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

#include <cstring>
#include <stdint.h>

#include <cstdio>

Routine23AnswerCbk::Routine23AnswerCbk ()
{
	// TODO Auto-generated constructor stub
}

Routine23AnswerCbk::~Routine23AnswerCbk ()
{
	// TODO Auto-generated destructor stub
}

std::shared_ptr<ChannelValueFoundation> Routine23AnswerCbk::parseAnswer (UmbFrameRaw &in)
{
	std::shared_ptr<ChannelValueFoundation> out;

	uint32_t temp = 0;
	int32_t stemp = 0;
	float ftemp = 0.0f;

	// TODO: ?????
	unsigned char ff[] = {0x40, 0x16, 0x14, 0x7b};
	uint8_t ffa[] = {0x7b, 0x14, 0x16, 0x40};
	void *f = &ff;

	const std::vector<unsigned char> &content = in.content;

	uint8_t channelNumberL = content[1];
	uint8_t channelNumberH = content[2];

	unsigned short channelNumber = (channelNumberL | channelNumberH << 8);
	unsigned char channelType = content[3];

	switch (channelType) {
	case UNSIGNED_CHAR:
	{
		out = std::make_shared<Integer>((uint32_t)content[4]);

		break;
	}
	case SIGNED_CHAR:
	{
		out = std::make_shared<Integer>((int32_t)content[4]);

		break;
	}
	case UNSIGNED_SHORT:
	{
		const uint8_t l = content[4];
		const uint8_t h = content[5];

		const uint16_t valueU16 = l | (h << 8);

		out = std::make_shared<Integer>((uint32_t)valueU16);

		break;
	}
	case SIGNED_SHORT:
	{
		const uint8_t l = content[4];
		const uint8_t h = content[5];

		const int16_t valueI16 = l | (h << 8);

		out = std::make_shared<Integer>((int32_t)valueI16);

		break;
	}
	case UNSIGNED_INT:
	{
		const uint8_t l = content[4];
		const uint8_t ll = content[5];
		const uint8_t hh = content[6];
		const uint8_t h = content[7];

		const uint32_t valueU32 = l | (ll << 8) | (hh << 16) | (h << 24);

		out = std::make_shared<Integer>((uint32_t)valueU32);

		break;
	}
	case SIGNED_INT:
	{
		return_value = new Integer ();
		stemp = (signed)((*(in->content + 4) | (*(in->content + 5) << 8) |
						  (*(in->content + 6) << 16) | (*(in->content + 7) << 24)));
		((Integer *)return_value)->setValue (temp);

		break;
	}
	case FLOAT:
	{
		return_value = new Float ();
		//			f = (float*)((*(in->content + 4) | (*(in->content + 5) << 8) |
		//(*(in->content + 6) << 16) | (*(in->content + 7) << 24))); 			ftemp =
		//*(float*)((void*)ff);
		memcpy (&ftemp, in->content + 4, 4);
		((Float *)return_value)->setValue (ftemp);

		break;
	}
	case DOUBLE:
	{
		return_value = new Float ();
		//*f = ((*(in->content + 4) | (*(in->content + 5) << 8) | (*(in->content + 6) << 16) |
		//(*(in->content + 7) << 24)));
		memcpy (&ftemp, in->content + 4, 4);
		((Float *)return_value)->setValue (ftemp);

		break;
	}
	default:
	{
		return_value = new Float ();
		((Float *)return_value)->setValue (0.0f);
		break;
	}
	}

	printf ("parseAnswer - kanal: %d - status: %d - ln: %d - chtype: %d - temp: %d - stemp: %d - "
			"ftem: %f\r\n",
			(*(in->content + 1) | *(in->content + 2) << 8),
			(int)*(in->content),
			(int)(in->ln),
			*(in->content + 3),
			temp,
			stemp,
			ftemp);
	return return_value;
}
