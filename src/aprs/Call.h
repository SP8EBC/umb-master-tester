/*
 * Call.h
 *
 *  Created on: 11.09.2017
 *      Author: mateusz
 */

#ifndef APRS_CALL_H_
#define APRS_CALL_H_

#include <string>

using namespace std;

class AprsCall {
private:
	string call;
	char ssid;

public:
	AprsCall(string call, char ssid);
	virtual ~AprsCall();

	string getCall();
	char getSsid();
};

#endif /* APRS_CALL_H_ */
