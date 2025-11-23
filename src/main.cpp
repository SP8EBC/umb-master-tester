/*
 * main.cpp
 *
 *  Created on: Nov 20, 2025
 *      Author: mateusz
 */

#include "serial/serial.h"

#include <boost/program_options.hpp>
#include <iostream>
#include <random>
#include <string>

#include <spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#include "exceptions/StartOfHeaderTimeoutEx.h"
#include "exceptions/TimeoutE.h"

#include "umb/Routine23AnswerCbk.h"
#include "umb/Routine23Query.h"
#include "umb/Routine26AnswerCbk.h"
#include "umb/Routine26Query.h"

#include "types/Float.h"
#include "types/Integer.h"
#include "types/UnsignedInteger.h"

static float stubbedWindspeed = 2.5f;
static float stubbedWindgusts = 5.1f;
static float stubbedWinddir = 99.0f;
static float stubbedTemp = 21.1f;
static float stubbedPressure = 990.0f;

static int8_t randomize = 0;
static std::random_device rd ("/dev/urandom");

static int8_t injectCrcErrors = -1;
static int8_t injectTimeout = -1;

static int8_t keepCrcErrors = -1;
static int8_t keepTimeout = -1;

static std::vector<std::shared_ptr<ChannelValueFoundation>>
createValues (std::vector<uint16_t> chnsNumber)
{
	std::vector<std::shared_ptr<ChannelValueFoundation>> out;

	std::uniform_int_distribution<int8_t> d (0, randomize);

	float randomizer = 1.0f;

	if (randomize > 0 && randomize < 100) {
		int8_t randomValue = d (rd);
		uint8_t shifted = randomValue + randomize;
		randomizer = (float)shifted * 0.01f;
	}

	for (uint16_t channel : chnsNumber) {
		switch (channel) {
		case 460: {
			const std::shared_ptr<ChannelValueFoundation> windspeed =
				std::make_shared<Float> (randomizer * stubbedWindspeed);
			out.push_back (windspeed);
			break;
		}
		case 440: {
			const std::shared_ptr<ChannelValueFoundation> windgusts =
				std::make_shared<Float> (randomizer * stubbedWindgusts);
			out.push_back (windgusts);

			break;
		}
		case 580: {
			const std::shared_ptr<ChannelValueFoundation> winddirection =
				std::make_shared<Float> (randomizer * stubbedWinddir);
			out.push_back (winddirection);

			break;
		}
		case 100: {
			const std::shared_ptr<ChannelValueFoundation> temperature =
				std::make_shared<Float> (randomizer * stubbedTemp);
			out.push_back (temperature);

			break;
		}
		case 300: {
			const std::shared_ptr<ChannelValueFoundation> pressure =
				std::make_shared<Float> (randomizer * stubbedPressure);
			out.push_back (pressure);

			break;
		}
		default: {
			const std::shared_ptr<ChannelValueFoundation> dummy = std::make_shared<Integer> (0);
			out.push_back (dummy);

			break;
		}
		}
	}

	return out;
}

int main (int argc, char *argv[])
{

	std::string portName;

	serial port;

	auto logger = spdlog::stdout_color_mt ("main");

	spdlog::set_pattern ("[%H:%M:%S.%e] [%n] [%^-%L-%$] %v");
	spdlog::set_level (spdlog::level::debug);

	boost::program_options::options_description od ("");

	boost::program_options::options_description generalOptions ("General Options");
	boost::program_options::options_description_easy_init goInit = generalOptions.add_options ();
	goInit ("port,p",
			boost::program_options::value<std::string> (&portName),
			" : Serial port used for communication");
	goInit (",v", " : Set log level to trace, shows raw RX and TX serial data");
	goInit ("temperature,T",
			boost::program_options::value<float> (&stubbedTemp),
			" : stubbed Temperature");
	goInit ("pressure,P",
			boost::program_options::value<float> (&stubbedPressure),
			" : stubbed Pressure");
	goInit ("wind,W",
			boost::program_options::value<float> (&stubbedWindspeed),
			" : stubbed average Windspeed");
	goInit ("gust,G",
			boost::program_options::value<float> (&stubbedWindgusts),
			" : stubbed Windgust");
	goInit ("direction,D",
			boost::program_options::value<float> (&stubbedWindgusts),
			" : stubbed Wind direction");
	goInit ("crc,c",
			boost::program_options::value<int8_t> (&injectCrcErrors),
			" : inject CRC error each X response");
	goInit ("timeout,t",
			boost::program_options::value<int8_t> (&injectTimeout),
			" : do not respond each X requests from master");
	goInit (",kc",
			boost::program_options::value<int8_t> (&keepCrcErrors),
			" : keep injecting CRC error for X responses");
	goInit (",kt",
			boost::program_options::value<int8_t> (&keepTimeout),
			" : keep not responding to X requests");

	od.add (generalOptions);

	std::cout << od << std::endl;

	boost::program_options::variables_map odVariablesMap;
	boost::program_options::store (boost::program_options::parse_command_line (argc, argv, od),
								   odVariablesMap);
	boost::program_options::notify (odVariablesMap);

	logger->info ("UMB master tester & slave simulator");

	if (odVariablesMap.count ("t")) {
		spdlog::set_level (spdlog::level::trace);
	}

	/*
	 *	Mainly to initialize static loggers
	 */
	Routine23Query routine23q;
	Routine23AnswerCbk routine23a;

	Routine26Query routine26q;
	Routine26AnswerCbk routine26a;

	if (portName.length () > 1) {
		logger->info ("opening user specified port {}", portName);
		port.init (portName);
	}
	else {
		port.init ("/dev/ttyUSB2");
	}

	/*
	 * Some parameters validation
	 */
	if (keepCrcErrors > injectCrcErrors) {
		throw std::runtime_error ("'kc' option value must be lower than 'crc'");
	}
	else if (injectCrcErrors > 0 && keepCrcErrors <= 0) {
		keepCrcErrors = 1; // user didn't provided a value, set sane default
	}
	else {
		;
	}

	if (keepTimeout > injectTimeout) {
		throw std::runtime_error ("'kt' option value must be lower than 'timeout'");
	}
	else if (injectTimeout > 0 && keepTimeout <= 0) {
		keepTimeout = 1; // user didn't provided a value, set sane default
	}
	else {
		;
	}

	uint32_t requestCounter = 0;
	uint32_t responseCounter = 0;

	int8_t crcErrorsCnt = 0;
	int8_t timeoutsCnt = 0;

	while (true) {
		bool spoilCrc = false;

		try {
			std::shared_ptr<UmbFrameRaw> frame = port.receiveUmb (1);

			requestCounter++;

			if ((injectTimeout > 0) && (requestCounter % injectTimeout == 0)) {
				timeoutsCnt = 1;
			}

			if (timeoutsCnt > 0 && timeoutsCnt <= keepTimeout) {
				logger->info ("Timeouting on purpose for {} time, will {} in total",
							  timeoutsCnt,
							  keepTimeout);
				continue;
			}

			responseCounter++;

			if ((injectCrcErrors > 0) && (responseCounter % injectCrcErrors == 0)) {
				crcErrorsCnt = 1;
			}

			if (crcErrorsCnt > 0 && crcErrorsCnt <= keepCrcErrors) {
				logger->info ("Spoiling CRC on purpose for {} time, will {} in total",
							  crcErrorsCnt,
							  keepCrcErrors);
				spoilCrc = true;
			}

			if (frame->cmdId == 0x23u) {

				std::shared_ptr<Routine23FromMasterData> recvData =
					Routine23Query::parseQueryFromMaster (frame);

				const auto channels = recvData->channelsNumbers;

				std::shared_ptr<UmbFrameRaw> response =
					Routine23AnswerCbk::createAnswerToMaster (0,
															  channels,
															  createValues (channels),
															  frame);
				if (spoilCrc) {
					port.transmitUmb (response.get (), 0xDEAD);
				}
				else {
					port.transmitUmb (response.get ());
				}
			}
			if (frame->cmdId == 0x26u) {
				std::shared_ptr<UmbFrameRaw> response =
					Routine26AnswerCbk::createAnswerToMaster (0, 0, frame);

				if (spoilCrc) {
					port.transmitUmb (response.get (), 0xDEAD);
				}
				else {
					port.transmitUmb (response.get ());
				}
			}

			usleep (1000);
		}
		catch (TimeoutE &ex) {
			logger->error ("TimeoutE");
		}
		catch (StartOfHeaderTimeoutEx &ex) {
			logger->error ("StartOfHeaderTimeoutEx");
		}
	}

	return 0;
}
