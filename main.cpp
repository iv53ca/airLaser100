#include <iostream>
#include "Old/MainFunc.hpp"
#include "Old/packetDataClass.hpp"
#include "PcapReader.hpp"
#include "positionPacket.hpp"
#include "singleReturnPointPacket.hpp"
#include "NMEAReader.hpp"

int main(int argc, char **argv)
{
	std::cout << "Programm Date 20.10.2021\n";
	std::cout << "file names \"pcap.pcap\" , \"IE.txt\"\n";
	
	char pcapFilePath[] = "pcap.pcap";

	char IEFilePath[] = "IE.txt";

	
	MainScanFunc(pcapFilePath, IEFilePath);
	/*
	char pcapFilePath[] = "pls.pcap";

	char pcapFilePath2[] = "plspls.pcap";
	bool win;
	PcapReader NewPcap(pcapFilePath);
	rawLidarDataStream oldPcap(pcapFilePath2);
	
	singleReturnPointPacket srpp;
	rawPacketData oldPacket;
	std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n" << std::endl;
	for(int i = 0; i < 2000; i++)
	{
		win = NewPcap.getDataPacket();
		srpp.readBytes(NewPcap.dataPacket);
		//=============
		oldPcap.getPacket(oldPacket);
		
		std::cout << oldPacket.timestamp << ", " << srpp.packet.timeStamp << ", " << win << std::endl; 
		
		
	}
	*/
	std::cout << "\nEND" << std::endl;
	
	return 0;
}
