/*
 * UmbFrameStruct.h
 *
 *  Created on: 19.09.2017
 *      Author: mateusz
 */

#ifndef TYPES_UMBFRAMESTRUCTRAW_H_
#define TYPES_UMBFRAMESTRUCTRAW_H_

#include <vector>

struct UmbFrameRaw {

  private:
	UmbFrameRaw (const UmbFrameRaw &) = delete;
	UmbFrameRaw &operator= (const UmbFrameRaw &) = delete;

  public:
	UmbFrameRaw ()
		: protVersion (0), fromId (0), fromClass (0), ln (0), bytesRxed (0), cmdId (0),
		  checksumRxed (0), chceksumCorrectRX (0){};

	unsigned char protVersion;

	unsigned char fromId;		//!< device which the message is sent to
	unsigned char fromClass;	//!< device which the message is sent to

	unsigned char toId;		//!< device which the message is sent to
	unsigned char toClass;	//!< device which the message is sent to

	unsigned char ln; //!< this is always everything between STX and ETX, so content.size() + 2
	unsigned char bytesRxed;

	unsigned char cmdId;

	std::vector<unsigned char> content;	//!< payload, without command id and V10

	unsigned short checksumRxed;
	bool chceksumCorrectRX;
};

#endif /* TYPES_UMBFRAMESTRUCTRAW_H_ */
