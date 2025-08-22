#include "positionPacket.hpp"
#include <cstddef>

positionPacket::positionPacket()
{
	for(int i = 0; i < 187; i++)
		packet.reserved1[i] 		= 0;
	packet.tempOfTopBoard 			= 0;
	packet.tempOfBottomBoard 		= 0;
	packet.tempOfLastADC 			= 0;
	packet.tempChangeSinceLastADC 	= 0;
	packet.secondsSinceLastADC 		= 0;
	packet.reasonForLastADC 		= 0;
	packet.bitmaskOfCurrentADC 		= 0;
	packet.mSecSinceTOH 			= 0;
	packet. PPSStatus 				= 0;
	packet.thermalStatus 			= 0;
	packet.lastShutdownTemp 		= 0;
	packet.tempAtPowerUp 			= 0;
	for(int i = 0; i < 128; i++)
		packet.NMEASentance[i] 		= 0;
	for(int i = 0; i < 178; i++)
		packet.reserved2[i] 		= 0;
}

positionPacket::~positionPacket()
{
}

bool positionPacket::readBytes(uint8_t* packetBytes)
{
	std::size_t counter = 0;
	for(int i = 0; i < 42; i++)
		packet.header[i] = packetBytes[counter++];
	for(int i = 0; i < 187; i++)
		packet.reserved1[i] = packetBytes[counter++];
	packet.tempOfTopBoard = packetBytes[counter++];
	packet.tempOfBottomBoard = packetBytes[counter++];
	packet.tempOfLastADC = packetBytes[counter++];
	packet.tempChangeSinceLastADC = 0;
	packet.tempChangeSinceLastADC |= packetBytes[counter++];
	packet.tempChangeSinceLastADC |= packetBytes[counter++] << 8;
	packet.secondsSinceLastADC = 0;
	for(int i = 0; i < 4; i++)
		packet.secondsSinceLastADC |= packetBytes[counter++] << 8*i;
	packet.reasonForLastADC = packetBytes[counter++];
	packet.bitmaskOfCurrentADC = packetBytes[counter++];
	packet.mSecSinceTOH = 0;
	for(int i = 0; i < 4; i++)
		packet.mSecSinceTOH |= packetBytes[counter++] << 8*i;
	packet. PPSStatus = packetBytes[counter++];
	packet.thermalStatus = packetBytes[counter++];
	packet.lastShutdownTemp = packetBytes[counter++];
	packet.tempAtPowerUp = packetBytes[counter++];
	for(int i = 0; i < 128; i++)
		packet.NMEASentance[i] = packetBytes[counter++];
	for(int i = 0; i < 178; i++)
		packet.reserved2[i] = packetBytes[counter++];
	
	
	return true;
}
