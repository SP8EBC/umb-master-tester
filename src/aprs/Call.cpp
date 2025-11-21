/*
 * Call.cpp
 *
 *  Created on: 11.09.2017
 *      Author: mateusz
 */

#include "Call.h"

AprsCall::AprsCall(string call, char ssid) {
	// TODO Auto-generated constructor stub
	this->ssid = ssid;
	this->call = call;

}

AprsCall::~AprsCall() {
	// TODO Auto-generated destructor stub
}

string AprsCall::getCall() {
	return this->call;
}

char AprsCall::getSsid() {
	return this->ssid;
}
