#ifndef PCAPREADERGUARDGUARD
#define PCAPREADERGUARDGUARD

/*
 * TODO : reWrite using buffer for ifstream (29.07.2021)
 */


#include <fstream>
#include <cstdint> //uint8_t

class PcapReader
{
public:
	std::ifstream file;
	uint8_t dataPacket[1248];
	uint8_t positionPacket[554];
	
	PcapReader();
	~PcapReader();
	PcapReader(char* filepath);
	bool open(char* filepath);
	bool getDataPacket();
	bool getPositionPacket();
};

#endif 