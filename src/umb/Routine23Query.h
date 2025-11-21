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

class Routine23Query {
public:
	static void prepareQuery(unsigned short channelNumber,
							unsigned char deviceId,
							unsigned char deviceClass,
							UmbFrameRaw &out);

	Routine23Query();
	virtual ~Routine23Query();
};

#endif /* UMB_ROUTINE23QUERY_H_ */
