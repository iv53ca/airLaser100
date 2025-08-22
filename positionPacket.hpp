#ifndef POSITIONPACKETGUARD
#define POSITIONPACKETGUARD

#include <stdint.h>

class positionPacket
{
public:
	struct 
	{
		uint8_t header[42];
		uint8_t reserved1[187]; // 0x00
		uint8_t tempOfTopBoard; // 0 to 150 celsius
		uint8_t tempOfBottomBoard; // 0 to 150 celsius
		uint8_t tempOfLastADC; // 0 to 150 celsius
		uint16_t tempChangeSinceLastADC; // -150 to 150 celsius (2 bytes)
		uint32_t secondsSinceLastADC; // 0 to 2^32 -1 (4 bytes)
		uint8_t reasonForLastADC; // 0 to 4 (lookup in datasheet [page 61])
		uint8_t bitmaskOfCurrentADC; // (lookup in datasheet [page 61])
		uint32_t mSecSinceTOH; // timestamp since top of the hour (4 bytes)
		uint8_t PPSStatus; //(lookup in datasheet [page 62])
		uint8_t thermalStatus; // 0 - ok; 1 - thermal shutdown
		uint8_t lastShutdownTemp;
		uint8_t tempAtPowerUp;
		uint8_t NMEASentance[128]; // nmea GPRMC (or GPGGA)
		uint8_t reserved2[178]; // 0x00
	}packet;
	positionPacket();
	~positionPacket();
	bool readBytes(uint8_t *);

};

#endif // POSITIONPACKETGUARD
