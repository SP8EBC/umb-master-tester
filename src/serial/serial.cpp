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

#define SOH 0x01
#define STX 0x02
#define ETX 0x03
#define EOT 0x04

#define V10 0x10

#define MASTER_ID 0x01

using namespace std;

serial::serial ()
{
	// TODO Auto-generated constructor stubes
}

void serial::transmitUmb (UmbFrameRaw *in)
{
	int i = 0;
	unsigned short crc = 0xFFFF;

	if (in == 0)
		throw NullPointerE ();

	char *txbuffer = new char[in->ln + 15];
	memset (txbuffer, 0x00, in->ln + 15);

	txbuffer[i++] = SOH;
	txbuffer[i++] = V10;
	txbuffer[i++] = in->slaveId;
	txbuffer[i++] = in->slaveClass << 4;
	txbuffer[i++] = ProgramConfig::getMasterId ();
	txbuffer[i++] = 0xF0;
	txbuffer[i++] = in->ln;
	txbuffer[i++] = STX;
	//
	txbuffer[i++] = in->cmdId;
	txbuffer[i++] = V10;
	for (int j = 0; j < in->ln - 2; j++)
		txbuffer[i++] = *(in->content + j);
	//
	txbuffer[i++] = ETX;
	for (int j = 0; j < i; j++)
		crc = calc_crc (crc, txbuffer[j]);
	txbuffer[i++] = crc & 0xFF;
	txbuffer[i++] = (crc & 0xFF00) >> 8;
	txbuffer[i++] = EOT;

	printf ("serial::transmitUmb.txbuffer:");
	for (int j = 0; j < in->ln + 15; j++)
		printf (" 0x%x", txbuffer[j]);
	printf ("\r\n");

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
			printf ("serial::receiveUmb.rx:");
			for (unsigned j = 0; j < rx.size (); j++) {
				printf (" 0x%x", (unsigned)rx.at (j));
			}
			printf ("\r\n");

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

	printf ("serial::receiveUmb.ln_rcv: 0x%x\r\n", ln_rcv);

	for (; pos <= ln_rcv; pos++) {
		gettimeofday (&timeout, NULL);
		if (timeout.tv_sec - timeout_start.tv_sec > ProgramConfig::getTimeout ()) {
			printf ("serial::receiveUmb.rx:");
			for (unsigned j = 0; j < rx.size (); j++) {
				printf (" 0x%x", (unsigned)rx.at (j));
			}
			printf ("\r\n");

			throw TimeoutE (); // TODO: zrobić rzucanie wyjątku
		}

		n = read (handle, &rx_buf, 1);
		if (n != 0)
			rx.push_back (rx_buf);
		else {
			printf ("serial::receiveUmb.rx:");
			for (unsigned j = 0; j < rx.size (); j++) {
				printf (" 0x%x", (unsigned)rx.at (j));
			}
			printf ("\r\n");

			throw TimeoutE ();
		}
	}

	for (unsigned j = 0; j < rx.size (); j++) {
		printf (" 0x%x", (unsigned)rx.at (j));
	}
	printf ("\r\n");

	out->ln = ln_rcv - 12; // everything between STX & ETX -> cmdId + V10 + command payload
	out->bytesRxed = rx.size ();
	out->cmdId = rx[8];

	// memset (out->content, 0x00, out->ln - 2);
	// memcpy(out->content, data + 10, out->ln -2);
	// out->content.push_back(out->content.begin(), data+10, data + ())

	// first byte of command payload after cmdId and V10
	const std::vector<uint8_t>::const_iterator copy_from = rx.begin () + 10;
	const std::vector<uint8_t>::const_iterator copy_to =
		copy_from + (out->ln - 2); // minus cmdId and minus V10

	out->content.insert(out->content.begin(), copy_from, copy_to);

	out->slaveId = rx[4];
	out->slaveClass = rx[5] >> 4;
	out->protVersion = rx[1];

	const uint8_t crcL = rx[out->bytesRxed - 3];
	const uint8_t crcH = rx[out->bytesRxed - 2];

	out->checksumRxed = crcL | crcH << 8;

	unsigned short crc = 0xFFFF;

	for (int j = 0; j < (out->bytesRxed - 3); j++)
		crc = calc_crc (crc, rx[j]);

	if (crc == out->checksumRxed)
		out->chceksumCorrectRX = true;

	delete rx;

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

	handle = open (port.c_str (), O_RDWR | O_NOCTTY);

	/* Error Handling */
	if (tcgetattr (handle, &tty) != 0) {
		std::cout << "Error " << errno << " from tcgetattr: " << strerror (errno) << std::endl;
	}

	/* Save old tty parameters */
	tty_old = tty;

	/* Set Baud Rate */

	tty.c_iflag &= ~(IMAXBEL | IXOFF | INPCK | BRKINT | PARMRK | ISTRIP | INLCR | IGNCR | ICRNL |
					 IXON | IGNPAR);
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
		std::cout << "Error " << errno << " from tcsetattr" << std::endl;
	}

	std::cout << "Port serial skonfigurowany " << std::endl;
}

void serial::test_transmit ()
{
	for (uint8_t i = 0; i < 255; i++)
		write (handle, &i, 1);
}

short serial::checkCRC (char *pInputData)
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

unsigned short serial::calc_crc (unsigned short crc_buff, unsigned char input)
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
