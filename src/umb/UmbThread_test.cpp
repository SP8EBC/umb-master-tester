/*
 * UmbThread_test.cpp
 *
 *  Created on: 24.09.2017
 *      Author: mateusz
 */

#include "UmbThread.h"

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE UMBTHREAD
#include <boost/test/unit_test.hpp>

#include "../config/ProgramConfig.h"

BOOST_AUTO_TEST_CASE(a)
{
	serial s;
	ProgramConfig::setMasterId(1);
	ProgramConfig::readConfigFromFile();

	BOOST_REQUIRE_NO_THROW(s.init("/dev/ttyUSB0"));

	UmbThread *t;
	t = new UmbThread(&s, ProgramConfig::getMasterId(), ProgramConfig::getDevices());

//	BOOST_REQUIRE_NO_THROW(s.test_transmit());

	BOOST_REQUIRE_NO_THROW(t->serviceThread());

	delete t;

	ProgramConfig::setMasterId(1);


}
