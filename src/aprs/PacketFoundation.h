/*
 * AprsPacketFoundation.h
 *
 *  Created on: 11.09.2017
 *      Author: mateusz
 */

#ifndef APRS_PACKETFOUNDATION_H_
#define APRS_PACKETFOUNDATION_H_

#include <string>
#include <list>

#include "Call.h"

using namespace std;

class AprsPacketFoundation {

private:
	AprsCall source;
	AprsCall destination;
	list<AprsCall> digi;

public:
	AprsPacketFoundation(AprsCall* s, AprsCall* d) :
		source(s->getCall(), s->getSsid()),
		destination(d->getCall(), d->getSsid()) {}

	virtual ~AprsPacketFoundation();

	AprsCall getSource();
	AprsCall getDestination();
	list<AprsCall> getDigi();

	virtual string toString() = 0;
};

#endif /* APRS_PACKETFOUNDATION_H_ */
