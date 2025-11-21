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

class Routine26AnswerCbk {
public:
	static unsigned char parseAnswer(UmbFrameRaw& in);

	Routine26AnswerCbk();
	virtual ~Routine26AnswerCbk();
};

#endif /* UMB_ROUTINE26ANSWERCBK_H_ */
