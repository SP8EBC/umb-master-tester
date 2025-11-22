/*
 * main.cpp
 *
 *  Created on: Nov 20, 2025
 *      Author: mateusz
 */

#include "serial/serial.h"

#include <boost/program_options.hpp>
#include <iostream>
#include <string>

#include <spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#include "exceptions/StartOfHeaderTimeoutEx.h"
#include "exceptions/TimeoutE.h"

#include "umb/Routine23Query.h"
#include "umb/Routine23AnswerCbk.h"

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
	goInit ("port,P",
			boost::program_options::value<std::string> (&portName),
			" : Serial port used for communication");
	goInit ("t,t",
			" : Set log level to trace, shows raw RX and TX serial data");

	od.add (generalOptions);

	std::cout << od << std::endl;

	boost::program_options::variables_map odVariablesMap;
	boost::program_options::store (boost::program_options::parse_command_line (argc, argv, od),
								   odVariablesMap);
	boost::program_options::notify (odVariablesMap);

	logger->info ("UMB master tester & slave simulator");

	if (odVariablesMap.count("t"))
	{
		spdlog::set_level (spdlog::level::trace);
	}

	/*
	 *	Mainly to initialize static loggers
	 */
	Routine23Query routine32q;
	Routine23AnswerCbk routine32a;

	if (portName.length () > 1) {
		logger->info ("opening user specified port {}", portName);
		port.init (portName);
	}
	else {
		port.init ("/dev/ttyUSB2");
	}

	while (true) {
		try {
			std::shared_ptr<UmbFrameRaw> frame = port.receiveUmb (1);

			if (frame->cmdId == 0x23u) {
				std::shared_ptr<Routine23FromMasterData> recvData =
					Routine23Query::parseQueryFromMaster (frame);
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
