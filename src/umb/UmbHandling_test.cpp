/*
 * UmbHandling_test.cpp
 *
 *  Created on: 19.09.2017
 *      Author: mateusz
 */

#include "UmbHandling.h"
//#include "../config/ProgramConfig.h"

#include <iostream>
using namespace std;

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE UMBHANDLING
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(a)
{
	serial s;
	ProgramConfig::setMasterId(1);

	BOOST_REQUIRE_NO_THROW(s.init("/dev/ttyUSB0"));

//	BOOST_REQUIRE_NO_THROW(s.test_transmit());

	BOOST_REQUIRE_NO_THROW(UmbHandling::testChannelQuery(s));


	ProgramConfig::setMasterId(1);


}

BOOST_AUTO_TEST_CASE(status)
{
	serial s;
	ProgramConfig::setMasterId(1);

	BOOST_REQUIRE_NO_THROW(s.init("/dev/ttyUSB0"));

	BOOST_REQUIRE_NO_THROW(UmbHandling::checkStatus(1, 8, s));
}

