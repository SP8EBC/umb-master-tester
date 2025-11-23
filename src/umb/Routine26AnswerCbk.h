/*
 * Routine26AnswerCbk.h
 *
 *  Created on: 24.09.2017
 *      Author: mateusz
 */

#ifndef UMB_ROUTINE26ANSWERCBK_H_
#define UMB_ROUTINE26ANSWERCBK_H_

#include "../types/ChannelValueFoundation.h"
#include "../types/UmbFrameStructRaw.h"

#include <memory>

#include <spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

class Routine26AnswerCbk {
	static std::shared_ptr<spdlog::logger> logger;

  public:
	static unsigned char parseAnswerFromSlave (UmbFrameRaw &in);

	static std::shared_ptr<UmbFrameRaw> createAnswerToMaster (uint8_t status, uint8_t device_status,
															  std::shared_ptr<UmbFrameRaw> request);

	Routine26AnswerCbk ();
	virtual ~Routine26AnswerCbk ();
};

#endif /* UMB_ROUTINE26ANSWERCBK_H_ */
