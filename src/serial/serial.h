/*
 * serial.h
 *
 *  Created on: 22.09.2017
 *      Author: mateusz
 */

#ifndef SERIAL_SERIAL_H_
#define SERIAL_SERIAL_H_

#include <stdio.h>      // standard input / output functions
#include <stdlib.h>
#include <string.h>     // string function definitions
#include <unistd.h>     // UNIX standard function definitions
#include <fcntl.h>      // File control definitions
#include <errno.h>      // Error number definitions
#include <termios.h>    // POSIX terminal control definitions
#include <string>
#include <memory>

using namespace std;

#include "../types/UmbFrameStructRaw.h"

class serial {

	int handle;

	struct termios tty;
	struct termios tty_old;

public:
	void init(string port);
	void test_transmit();

	void transmitUmb(UmbFrameRaw *in);
	std::shared_ptr<UmbFrameRaw> receiveUmb(unsigned short max_timeout);

	short checkCRC(char* pInputData);
	unsigned short calc_crc(unsigned short crc_buff, unsigned char input);

	serial();
	virtual ~serial();
};

#endif /* SERIAL_SERIAL_H_ */
