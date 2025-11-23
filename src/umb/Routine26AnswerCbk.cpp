/*
 * Routine26AnswerCbk.cpp
 *
 *  Created on: 24.09.2017
 *      Author: mateusz
 */

#include "Routine26AnswerCbk.h"

#include <stdint.h>

std::shared_ptr<spdlog::logger> Routine26AnswerCbk::logger;


Routine26AnswerCbk::Routine26AnswerCbk ()
{
	logger = spdlog::stdout_color_mt ("routine26a");
}

unsigned char Routine26AnswerCbk::parseAnswerFromSlave (UmbFrameRaw &in)
{
	unsigned char ret;

	ret = in.content[1];	// device status

	return ret;
}

std::shared_ptr<UmbFrameRaw>
Routine26AnswerCbk::createAnswerToMaster (uint8_t status, uint8_t device_status, std::shared_ptr<UmbFrameRaw> request)
{
	std::shared_ptr<UmbFrameRaw> out = std::make_shared<UmbFrameRaw>();

	out->fromClass = request->toClass;
	out->toClass = request->fromClass;

	out->fromId = request->toId;
	out->toId = request->fromId;

	out->cmdId = 0x26;

	logger->info("to master, status: {}, device status: {}", status, device_status);

	out->content.push_back(status);
	out->content.push_back(device_status);

	out->ln = out->content.size() + 2;

	return out;
}

Routine26AnswerCbk::~Routine26AnswerCbk ()
{
	// TODO Auto-generated destructor stub
}
