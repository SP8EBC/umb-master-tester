/*
 * serial.cpp
 *
 *  Created on: 22.09.2017
 *      Author: mateusz
 */

#include "serial.h"
#include <cstring>
#include <iostream>
#include <stdint.h>
#include <string>
#include <sys/time.h>
#include <vector>

#include "../exceptions/NullPointerE.h"
#include "../exceptions/StartOfHeaderTimeoutEx.h"
#include "../exceptions/TimeoutE.h"

#include "../config/ProgramConfig.h"

#include "spdlog/fmt/bin_to_hex.h"

#define SOH 0x01
#define STX 0x02
#define ETX 0x03
#define EOT 0x04

#define V10 0x10

#define MASTER_ID 0x01

using namespace std;

serial::serial () : handle (-1)
{
	logger = spdlog::stdout_color_mt ("serial");
}

void serial::transmitUmb (UmbFrameRaw *in, uint16_t spoiledCrc)
{
	int i = 0;
	unsigned short crc = 0xFFFF;

	if (in == 0)
		throw NullPointerE ();

	const std::size_t size = in->ln + 15;

	char *txbuffer = new char[size];
	memset (txbuffer, 0x00, size);

	txbuffer[i++] = SOH;
	txbuffer[i++] = V10;
	txbuffer[i++] = in->toId;
	txbuffer[i++] = in->toClass << 4;
	txbuffer[i++] = in->fromId;
	txbuffer[i++] = in->fromClass << 4;
	txbuffer[i++] = in->ln;
	txbuffer[i++] = STX;
	//
	txbuffer[i++] = in->cmdId;
	txbuffer[i++] = V10;
	for (int j = 0; j < in->ln - 2; j++)
		txbuffer[i++] = in->content[j];
	//
	txbuffer[i++] = ETX;
	if (spoiledCrc == 0)
	{
		for (int j = 0; j < i; j++)
			crc = calc_crc (crc, txbuffer[j]);
		txbuffer[i++] = crc & 0xFF;
		txbuffer[i++] = (crc & 0xFF00) >> 8;
	}
	else
	{
		txbuffer[i++] = spoiledCrc & 0xFF;
		txbuffer[i++] = (spoiledCrc & 0xFF00) >> 8;
	}
	txbuffer[i++] = EOT;

	logger->trace ("TX: {:n}", spdlog::to_hex (txbuffer, txbuffer + size));

	write (handle, txbuffer, i);
}

std::shared_ptr<UmbFrameRaw> serial::receiveUmb (unsigned short max_timeout)
{
	uint8_t ln_rcv = 0;
	uint8_t rx_buf = 0;
	uint8_t n = 0;
	uint8_t pos = 0;
	struct timeval timeout, timeout_start;

	std::shared_ptr<UmbFrameRaw> out = std::make_shared<UmbFrameRaw> ();

	vector<uint8_t> rx;

	gettimeofday (&timeout_start, NULL);
	do {
		gettimeofday (&timeout, NULL);
		if (timeout.tv_sec - timeout_start.tv_sec > ProgramConfig::getTimeout ())
			throw StartOfHeaderTimeoutEx (); // TODO: zrobić rzucanie wyjątku

		n = read (handle, &rx_buf, 1);
	} while (rx_buf != SOH);

	rx.push_back (rx_buf);
	pos = 2;

	for (; pos <= 7; pos++) {
		gettimeofday (&timeout, NULL);
		if (timeout.tv_sec - timeout_start.tv_sec > ProgramConfig::getTimeout ()) {
			logger->error ("RX: {:n}", spdlog::to_hex (rx.begin (), rx.end ()));

			throw TimeoutE (); // TODO: zrobić rzucanie wyjątku
		}

		n = read (handle, &rx_buf, 1);
		if (n != 0)
			rx.push_back (rx_buf);
		else
			throw TimeoutE ();
	}

	ln_rcv = rx_buf;
	ln_rcv += 12;

	for (; pos <= ln_rcv; pos++) {
		gettimeofday (&timeout, NULL);
		if (timeout.tv_sec - timeout_start.tv_sec > ProgramConfig::getTimeout ()) {
			logger->error ("RX: {:n}", spdlog::to_hex (rx.begin (), rx.end ()));

			throw TimeoutE (); // TODO: zrobić rzucanie wyjątku
		}

		n = read (handle, &rx_buf, 1);
		if (n != 0)
			rx.push_back (rx_buf);
		else {
			logger->error ("RX: {:n}", spdlog::to_hex (rx.begin (), rx.end ()));

			throw TimeoutE ();
		}
	}

	logger->trace ("RX: {:n}", spdlog::to_hex (rx.begin (), rx.end ()));

	out->ln = ln_rcv - 12; // everything between STX & ETX -> cmdId + V10 + command payload
	out->bytesRxed = rx.size ();
	out->cmdId = rx[8];

	// first byte of command payload after cmdId and V10
	const std::vector<uint8_t>::const_iterator copy_from = rx.begin () + 10;
	const std::vector<uint8_t>::const_iterator copy_to =
		copy_from + (out->ln - 2); // minus cmdId and minus V10

	out->content.insert (out->content.begin (), copy_from, copy_to);

	out->protVersion = rx[1];
	out->toId = rx[2];
	out->toClass = rx[3] >> 4;
	out->fromId = rx[4];
	out->fromClass = rx[5] >> 4;


	const uint8_t crcL = rx[out->bytesRxed - 3];
	const uint8_t crcH = rx[out->bytesRxed - 2];

	out->checksumRxed = crcL | crcH << 8;

	unsigned short crc = 0xFFFF;

	for (int j = 0; j < (out->bytesRxed - 3); j++)
		crc = calc_crc (crc, rx[j]);

	if (crc == out->checksumRxed)
		out->chceksumCorrectRX = true;

	logger->info ("ln: {}, bytesRxed: {}, cmdId: 0x{:x}, deviceId: 0x{:x}, deviceClass: 0x{:x}",
				  out->ln,
				  out->bytesRxed,
				  out->cmdId,
				  out->fromId,
				  out->fromClass);

	return out;
}

serial::~serial ()
{
	// TODO Auto-generated destructor stub
}

void serial::init (string port)
{
	struct termios tty;
	struct termios tty_old;
	memset (&tty, 0, sizeof tty);

	logger->info ("Opening: {}", port);

	handle = open (port.c_str (), O_RDWR | O_NOCTTY);

	if (handle >= 0) {

		/* Error Handling */
		if (tcgetattr (handle, &tty) != 0) {
			logger->error ("Error {} from tcgetattr", errno);
		}

		/* Save old tty parameters */
		tty_old = tty;

		/* Set Baud Rate */

		tty.c_iflag &= ~(IMAXBEL | IXOFF | INPCK | BRKINT | PARMRK | ISTRIP | INLCR | IGNCR |
						 ICRNL | IXON | IGNPAR);
		tty.c_iflag |= IGNBRK;

		tty.c_oflag &= ~OPOST;
		tty.c_oflag &= ~CRTSCTS;

		tty.c_lflag &=
			~(ECHO | ECHOE | ECHOK | ECHONL | ICANON | ISIG | IEXTEN | NOFLSH | TOSTOP | PENDIN);
		tty.c_cflag &= ~(CSIZE | PARENB);
		tty.c_cflag |= CS8 | CREAD;
		tty.c_cc[VMIN] = 0;	 // bylo 80
		tty.c_cc[VTIME] = 3; // byo 3

		cfsetospeed (&tty, (speed_t)B19200);
		cfsetispeed (&tty, (speed_t)B19200);

		/* Make raw */
		//	cfmakeraw(&tty);

		/* Flush Port, then applies attributes */
		tcflush (handle, TCIFLUSH);
		if (tcsetattr (handle, TCSANOW, &tty) != 0) {
			logger->error ("Error {} from tcsetattr", errno);
		}
		else {
			logger->info ("Serial port configured");
		}
	}
	else {
		logger->error ("Serial port cannot be opened, errno: {}", errno);
	}
}

void serial::test_transmit ()
{
	for (uint8_t i = 0; i < 255; i++)
		write (handle, &i, 1);
}

short serial::checkCRC (uint8_t *pInputData)
{
	char ii, i = 0;
	unsigned short crc = 0xFFFF;
	ii = pInputData[6] + 12;
	for (i = 0; i < ii - 3; i++)
		crc = calc_crc (crc, pInputData[i]);
	if ((pInputData[ii - 2] == ((crc & 0xFF00) >> 8)) && (pInputData[ii - 3] == (crc & 0xFF)))
		return 0;
	else
		return -1;
}

unsigned short serial::calc_crc (uint16_t crc_buff, uint8_t input)
{
	unsigned char i;
	unsigned short x16;
	for (i = 0; i < 8; i++) {
		// XOR current D0 and next input bit to determine x16 value
		if ((crc_buff & 0x0001) ^ (input & 0x01))
			x16 = 0x8408;
		else
			x16 = 0x0000;
		// shift crc buffer
		crc_buff = crc_buff >> 1;
		// XOR in the x16 value
		crc_buff ^= x16;
		// shift input for next iteration
		input = input >> 1;
	}
	return (crc_buff);
}
