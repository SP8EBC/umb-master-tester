/*
 * Routine23Query.cpp
 *
 *  Created on: 20.09.2017
 *      Author: mateusz
 */

#include "Routine23Query.h"

#include "../config/ProgramConfig.h"

std::shared_ptr<spdlog::logger> Routine23Query::logger;

Routine23Query::Routine23Query ()
{
	logger = spdlog::stdout_color_mt ("routine23q");
}

Routine23Query::~Routine23Query ()
{
	// TODO Auto-generated destructor stub
}

void Routine23Query::prepareQueryToSlave (unsigned short channelNumber, unsigned char deviceId,
								   unsigned char deviceClass, UmbFrameRaw &out)
{
	out.cmdId = 0x23U;
	out.toId = deviceId;
	out.toClass = deviceClass;

	out.fromId =  ProgramConfig::getMasterId ();
	out.toId = 0xF0;

	out.content.push_back ((unsigned char)(channelNumber & 0xFF));
	out.content.push_back ((unsigned char)((channelNumber & 0xFF00) >> 8));

	out.ln = 0x04U; // data length between STX and ETX
}

std::shared_ptr<Routine23FromMasterData>
Routine23Query::parseQueryFromMaster (std::shared_ptr<UmbFrameRaw> &received)
{
	std::shared_ptr<Routine23FromMasterData> out = std::make_shared<Routine23FromMasterData>();

	std::vector<uint8_t>::const_iterator beginOfChannels = received->content.begin();

	// each channel is 2 bytes wide.
	// ln in this case is:: cmdId + V10 + (channel * n), where 'n' is number of requested chns
	const std::size_t numChannels = (received->content.size()) / 2;

	for (std::size_t i = 0; i < numChannels; i++) {
		uint8_t l = *beginOfChannels;
		uint8_t h = *(beginOfChannels + 1);

		const uint16_t ch = l | (h << 8);

		out->channelsNumbers.push_back(ch);

		logger->info("from master, channel: {}", ch);
	}

	out->deviceClass = received->fromClass;
	out->deviceId = received->fromId;

	return out;
}
