/*
 * UmbThread.cpp
 *
 *  Created on: 24.09.2017
 *      Author: mateusz
 */

#include "UmbThread.h"
#include "../config/ProgramConfig.h"
#include "../umb/UmbHandling.h"
#include "../aprs/Mappings.h"
#include "../aprs/PacketWx.h"
#include "../aprs/Call.h"
#include "../exceptions/TimeoutE.h"
#include "../exceptions/StartOfHeaderTimeoutEx.h"

#include <vector>
#include <iostream>
#include <fstream>
#include <unistd.h>

UmbThread::UmbThread(serial* p, uint8_t master_id, vector<UmbDevice>* devices)
																	: port(p),
																	  masterId(master_id),
																	  devs(devices)

{

}

void UmbThread::serviceThread(void)
{
	AprsPacketWx* p;
	AprsCall s("nocall", 1), d("nocall", 10);
	ofstream outputfile;

	unsigned char devicesNum = ProgramConfig::getDevicesNumber();
	vector<UmbDevice>::iterator itdevs = devs->begin();

	for (int id = 0; id < devicesNum; id++)
	{
		vector<DeviceChannel> *vc = itdevs[id].getChannels();
		vector<DeviceChannel>::iterator itchannels = vc->begin();

		for (int ic = 0; ic < (int)vc->size(); ic++)
		{
			DeviceChannel* channel = &itchannels[ic];
			unsigned int chnum = channel->getChannelNumber();
			ChannelUsage use = channel->getChannelUsage();

			sleep(1);

			try {
				ChannelValueFoundation *val = UmbHandling::channelQuery(itdevs[id].getDeviceId(),
																		itdevs[id].getDeviceClass(),
																		chnum,
																		*port);
				if (use != NONE) {
					Mappings::usageUnitMapping[use] = channel->getMeasurementUnit();
					Mappings::usageValuesMapping[use] = val;
				}

				printf("channel: %d, value: %s\r\n", chnum, val->toString().c_str());

			}
			catch (TimeoutE &ex) {
				printf("Timeout exception has been thrown during comm\r\n");
				return;
			}
			catch (StartOfHeaderTimeoutEx & ex) {
				printf("Timeout exception has been thrown while waiting for SOH\r\n");
				return;
			}

		}
	}

	p = new AprsPacketWx(&s, &d, Mappings::usageUnitMapping, Mappings::usageValuesMapping);

	string o = p->toString();
	std::cout << o << endl;

	outputfile.open(ProgramConfig::getOutputAprxFile().c_str());
	outputfile << o;
	outputfile.close();

	delete p;

}

UmbThread::~UmbThread() {
	map<ChannelUsage, void*>::iterator it = Mappings::usageValuesMapping.begin();

//	std:cout << "deleting" << endl;

	for (; it != Mappings::usageValuesMapping.end(); it++) {
		delete (ChannelValueFoundation*)it->second;
	}
}

