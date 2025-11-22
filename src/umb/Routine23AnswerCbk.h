/*
 * Routine23AnswerCbk.h
 *
 *  Created on: 20.09.2017
 *      Author: mateusz
 */

#ifndef UMB_ROUTINE23ANSWERCBK_H_
#define UMB_ROUTINE23ANSWERCBK_H_

#include "../types/ChannelValueFoundation.h"
#include "../types/UmbFrameStructRaw.h"

#include <memory>

#include <spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

class Routine23AnswerCbk {
	static std::shared_ptr<spdlog::logger> logger;

  public:
	static std::shared_ptr<ChannelValueFoundation> parseAnswer (UmbFrameRaw &in);

	/**
	 * Create an answer which will be sent from this slave to master
	 * @param chnsNumber vector of channel numbers (should match with a request)
	 * @param chnsValues vector of values for each channel
	 * @param request frame sent by master to get both IDs and device classes from
	 * @return
	 */
	static std::shared_ptr<UmbFrameRaw>
	createAnswerToMaster (uint8_t status, std::vector<uint16_t> chnsNumber,
						  std::vector<std::shared_ptr<ChannelValueFoundation>> chnsValues,
						  std::shared_ptr<UmbFrameRaw> request);

	Routine23AnswerCbk ();
	virtual ~Routine23AnswerCbk ();
};

#endif /* UMB_ROUTINE23ANSWERCBK_H_ */
