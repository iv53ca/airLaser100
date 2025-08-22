#ifndef singleReturnPointPacketGUARD
#define singleReturnPointPacketGUARD
/*
 * class for transfer from byte array of binary data packet to redable data
 * as input takes byte array of size 1248
 */



#include <cstdint> //uint8_t

class singleReturnPointPacket
{
public:
	struct 
	{
		uint8_t UDPHeader[42]; // udp + ip(?) header
		struct 
		{
			uint16_t flag; // 0xffee
			uint16_t azimuth; //represents an angle in hundredths of a degree
			struct 
			{
				struct 
				{
					uint16_t distance; // 2 mm granularity, 0==fail
					uint8_t calibratedReflectivity; // signal intensety from object
				}channelDataPoint[16];
			}firingSequence[2];
		}dataBlock[12];
		uint32_t timeStamp; // marking the moment of the first data point in the first firing sequence of the first
							// block; value is the number of microseconds elapsed since the top of the hour
		uint16_t factoryBytes; // lets you anderstand type of laser and type of data packet
	}packet;

	singleReturnPointPacket();
	singleReturnPointPacket(uint8_t* packetBytes);
	bool readBytes(uint8_t* packetBytes);
	~singleReturnPointPacket();

};

#endif // pointPacket
