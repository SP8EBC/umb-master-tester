/*
 * Routine23Query.h
 *
 *  Created on: 20.09.2017
 *      Author: mateusz
 */

#ifndef UMB_ROUTINE23QUERY_H_
#define UMB_ROUTINE23QUERY_H_

#include "../types/ChannelValueFoundation.h"
#include "../types/UmbFrameStructRaw.h"

#include <memory>
#include <cstdint>

#include <spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>


struct Routine23FromMasterData {
	uint16_t deviceId;
	uint8_t deviceClass;
	std::vector<uint16_t> channelsNumbers;
};

class Routine23Query {
	static std::shared_ptr<spdlog::logger> logger;

  public:
	/**
	 * Prepare an UMB frame with a request from master to slave device
	 * @param channelNumber to get a value for
	 * @param deviceId of slave device to query
	 * @param deviceClass of slave device to query
	 * @param out
	 */
	static void prepareQuery (unsigned short channelNumber, unsigned char deviceId,
							  unsigned char deviceClass, UmbFrameRaw &out);

	/**
	 * Parse request received from the master device in case of emulating a slave
	 * @param received
	 * @return
	 */
	static std::shared_ptr<Routine23FromMasterData>
	parseQueryFromMaster (std::shared_ptr<UmbFrameRaw> &received);

	Routine23Query ();
	virtual ~Routine23Query ();
};

#endif /* UMB_ROUTINE23QUERY_H_ */
