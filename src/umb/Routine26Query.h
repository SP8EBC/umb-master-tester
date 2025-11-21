/*
 * Routine26Query.h
 *
 *  Created on: 23.09.2017
 *      Author: mateusz
 */

#ifndef UMB_ROUTINE26QUERY_H_
#define UMB_ROUTINE26QUERY_H_

#include "../types/UmbFrameStructRaw.h"

class Routine26Query {
public:
	static void prepareQuery(unsigned char deviceId,
							unsigned char deviceClass,
							UmbFrameRaw &out);

	Routine26Query();
	virtual ~Routine26Query();
};

#endif /* UMB_ROUTINE26QUERY_H_ */
