/*
 * Routine23AnswerCbk_test.cpp
 *
 *  Created on: 20.09.2017
 *      Author: mateusz
 */

#include "Routine23AnswerCbk.h"

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE ROUTINE23CALLABACK
#include <boost/test/unit_test.hpp>

#include "../types/UmbFrameStructRaw.h"
#include "../types/ChannelType.h"
#include "../types/Integer.h"
#include "../types/Float.h"

BOOST_AUTO_TEST_CASE(signedshort)
{
	unsigned char c[] = {0x00, 0x64, 0x00, SIGNED_SHORT, 0xD4, 0xFE};
	UmbFrameRaw f;
	f.cmdId = 0x23;
	f.content = new unsigned char[6];
	memcpy(f.content, c, 6);

	ChannelValueFoundation* o = (ChannelValueFoundation*)Routine23AnswerCbk::parseAnswer(&f);

	BOOST_CHECK_EQUAL( ((Integer*)o)->toString(), "-300");
	BOOST_CHECK_EQUAL( ((Integer*)o)->getValue(), -300 );

	delete[] f.content;
}

BOOST_AUTO_TEST_CASE(unsignedchar)
{
	unsigned char c[] = {0x00, 0x64, 0x00, UNSIGNED_CHAR, 0xFE};
	UmbFrameRaw f;
	f.cmdId = 0x23;
	f.content = new unsigned char[6];
	memcpy(f.content, c, 6);

	ChannelValueFoundation* o = (ChannelValueFoundation*)Routine23AnswerCbk::parseAnswer(&f);

	BOOST_CHECK_EQUAL( ((Integer*)o)->toString(), "254");
	BOOST_CHECK_EQUAL( ((Integer*)o)->getValue(), 254 );

	delete[] f.content;
}

BOOST_AUTO_TEST_CASE(f)
{
	unsigned char c[] = {0x00, 0x64, 0x00, FLOAT, 0xB3, 0xEA, 0x26, 0x41};
	UmbFrameRaw f;
	f.cmdId = 0x23;
	f.content = new unsigned char[8];
	memcpy(f.content, c, 8);

	ChannelValueFoundation* o = (ChannelValueFoundation*)Routine23AnswerCbk::parseAnswer(&f);

	BOOST_CHECK_EQUAL( ((Float*)o)->toString(), "2.345");
	BOOST_CHECK_EQUAL( ((Float*)o)->getValue(), 2.345f );

	delete[] f.content;
}
