/*
 * Routine26AnswerCbk.cpp
 *
 *  Created on: 24.09.2017
 *      Author: mateusz
 */

#include "Routine26AnswerCbk.h"

#include <stdint.h>

Routine26AnswerCbk::Routine26AnswerCbk ()
{
	// TODO Auto-generated constructor stub
}

unsigned char Routine26AnswerCbk::parseAnswer (UmbFrameRaw &in)
{
	unsigned char ret;

	ret = in.content[1];

	return ret;
}

Routine26AnswerCbk::~Routine26AnswerCbk ()
{
	// TODO Auto-generated destructor stub
}
