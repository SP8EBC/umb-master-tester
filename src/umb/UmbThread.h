/*
 * UmbThread.h
 *
 *  Created on: 24.09.2017
 *      Author: mateusz
 */

#ifndef UMB_UMBTHREAD_H_
#define UMB_UMBTHREAD_H_

#include "../serial/serial.h"
#include "../config/UmbDevice.h"

#include <stdint.h>
#include <vector>

class UmbThread {

	serial* port;
	uint8_t masterId;
	vector<UmbDevice>* devs;

public:
	void serviceThread(void);

	UmbThread(serial* p, uint8_t master_id, vector<UmbDevice>* devices);
	virtual ~UmbThread();
};

#endif /* UMB_UMBTHREAD_H_ */
