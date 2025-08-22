#include "singleReturnPointPacket.hpp"
#include <cstddef>

/*
 * (int is from right to left)
 * 42 bytes of header(from left to right)
 * 12 datablocks of
 * 		0xffee flag (2 bytes)(from left to right)
 * 		azimuth (2 bytes)
 * 		2 firing sequenses of
 * 			16 datapoints of
 * 				distance (2 bytes)
 * 				reflcetivity (1 byte)
 * timestamp (4 bytes)
 * factory bytes (2 bytes)
 * 								[1248 bytes total]
 */

singleReturnPointPacket::singleReturnPointPacket()
{
	for(int i = 0; i < 42; i++)
	{
	packet.UDPHeader[i] = 0;
	}
	for(int i = 0; i < 12; i++)
	{
		packet.dataBlock[i].flag = 0;
		packet.dataBlock[i].azimuth = 0;
		for(int j = 0; j < 32; j++)
		{
			packet.dataBlock[i].firingSequence[j/16].channelDataPoint[j%16].distance = 0;
			packet.dataBlock[i].firingSequence[j/16].channelDataPoint[j%16].calibratedReflectivity = 0;
		}
	}
	packet.timeStamp = 0;
	packet.factoryBytes = 0;
}

singleReturnPointPacket::~singleReturnPointPacket()
{
	
}

bool singleReturnPointPacket::readBytes(uint8_t* packetBytes)
{
	std::size_t counter = 0;
	for(uint8_t i = 0; i < 42; i++)
	{
		packet.UDPHeader[i] = packetBytes[counter++]; 
	}
	for(uint8_t i = 0; i < 12; i++) //for each dataBlock (from 0 to 11)
	{
		packet.dataBlock[i].flag = 0;
		packet.dataBlock[i].flag |= packetBytes[counter++] << 8; 
		packet.dataBlock[i].flag |= packetBytes[counter++]; // its 0xFFEE
		
		if(packet.dataBlock[i].flag != 0xffee) return false; // if block starts with not a 0xffee - its an error
		
		packet.dataBlock[i].azimuth = 0;
		packet.dataBlock[i].azimuth |= packetBytes[counter++];
		packet.dataBlock[i].azimuth |= packetBytes[counter++] << 8;
		
		for (uint8_t j = 0; j < 32; j++) // 2 firing sequences of 16 datapoints (2 byte distance, 1 byte reflection)
		{
			packet.dataBlock[i].firingSequence[j/16].channelDataPoint[j%16].distance = 0;
			packet.dataBlock[i].firingSequence[j/16].channelDataPoint[j%16].distance |= packetBytes[counter++];
			packet.dataBlock[i].firingSequence[j/16].channelDataPoint[j%16].distance |= packetBytes[counter++] << 8;
			
			packet.dataBlock[i].firingSequence[j/16].channelDataPoint[j%16].calibratedReflectivity = 0;
			packet.dataBlock[i].firingSequence[j/16].channelDataPoint[j%16].calibratedReflectivity |= 
																							packetBytes[counter++];
		}
		
	}
		packet.timeStamp = 0;
		for(uint8_t j = 0; j < 4; j++)
			packet.timeStamp |= packetBytes[counter++] << 8*j;
		
		packet.factoryBytes = 0;
		for(uint8_t j = 0; j < 2; j++)
			packet.factoryBytes |= packetBytes[counter++] << 8*j;
	return true;
}

singleReturnPointPacket::singleReturnPointPacket(uint8_t* packetBytes)
{
	std::size_t counter = 0;
	for(uint8_t i = 0; i < 42; i++)
	{
		packet.UDPHeader[i] = packetBytes[counter++]; 
	}
	for(uint8_t i = 0; i < 12; i++) //for each dataBlock (from 0 to 11)
	{
		packet.dataBlock[i].flag = 0;
		packet.dataBlock[i].flag |= packetBytes[counter++] << 8; 
		packet.dataBlock[i].flag |= packetBytes[counter++]; // its 0xFFEE
		
		packet.dataBlock[i].azimuth = 0;
		packet.dataBlock[i].azimuth |= packetBytes[counter++];
		packet.dataBlock[i].azimuth |= packetBytes[counter++] << 8;
		
		for (uint8_t j = 0; j < 32; j++) // 2 firing sequences of 16 datapoints (2 byte distance, 1 byte reflection)
		{
			packet.dataBlock[i].firingSequence[j/16].channelDataPoint[j%16].distance = 0;
			packet.dataBlock[i].firingSequence[j/16].channelDataPoint[j%16].distance |= packetBytes[counter++];
			packet.dataBlock[i].firingSequence[j/16].channelDataPoint[j%16].distance |= packetBytes[counter++] << 8;
			
			packet.dataBlock[i].firingSequence[j/16].channelDataPoint[j%16].calibratedReflectivity = 0;
			packet.dataBlock[i].firingSequence[j/16].channelDataPoint[j%16].calibratedReflectivity |= 
																							packetBytes[counter++];
		}
		
	}
		packet.timeStamp = 0;
		for(uint8_t j = 0; j < 4; j++)
			packet.timeStamp |= packetBytes[counter++] << 8*j;
		
		packet.factoryBytes = 0;
		for(uint8_t j = 0; j < 2; j++)
			packet.factoryBytes |= packetBytes[counter++] << 8*j;
}
