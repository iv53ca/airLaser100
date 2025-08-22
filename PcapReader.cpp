#include "PcapReader.hpp"

//#define ERRMSG ERROR in file __FILE__, line __LINE__ :

PcapReader::PcapReader()
{
	for(int i = 0; i < 1248; i++)
	{
		dataPacket[i] = 0;
		if (i < 554) positionPacket[i] = 0;
	}
}

PcapReader::~PcapReader()
{
	file.close();
}

PcapReader::PcapReader(char* filepath) : file{ filepath, std::ios::in | std::ios::binary }
{
	for(int i = 0; i < 1248; i++)
	{
		dataPacket[i] = 0;
		if (i < 554) positionPacket[i] = 0;
	}
}

bool PcapReader::open(char* filepath)
{
	file.open(filepath, std::ios::in | std::ios::binary);
	return file.is_open();
}

bool PcapReader::getDataPacket()
{
	bool success = false;
	uint8_t ffCounter = 0;
	bool reading = true;
	uint8_t buff = file.get();
	while(reading && file.good())
	{
		for(int i = 0 ; i < 1248; i++)
			dataPacket[i] = 0;

		while ((ffCounter < 6) && (file.good()))
		{
			if(buff == 0xff)
				ffCounter++;
			else
				ffCounter = 0;
			buff = file.get();
		}
		for(int i = 0; i < 6; i++)
			dataPacket[i] = 0xff;

		for(int i = 6; (i < 44 && file.good()); i++)
		{
			dataPacket[i] = buff;
			buff = file.get();
		}

		if(dataPacket[42] == 0xff && dataPacket[43] == 0xee)
		{
			reading = false;
			for(int i = 44; (i < 1248 && file.good()); i++)
			{
				dataPacket[i] = buff;
				buff = file.get();
			}
		}
	}
	if (file.good()) success = true;
	return success;
}

bool PcapReader::getPositionPacket()
{

	uint8_t ffCounter = 0;
	bool reading = true;
	bool success = false;
	uint8_t buff = file.get();
	while(reading && (file.good()))
	{
		for(int i = 0 ; i < 554; i++)
		    positionPacket[i] = 0;
		while ((ffCounter < 6)&&file.good())
		{
			if(buff == 0xff)
				ffCounter++;
			else
				ffCounter = 0;
			buff = file.get();
		}
		for(int i = 0; i < 6; i++)
			positionPacket[i] = 0xff;
		for(int i = 6; ((i < 254)&&(file.good())); i++)
		{
			positionPacket[i] = buff;
			buff = file.get();
		}
		if((positionPacket[43] == 0x00)&&
		(positionPacket[248] == '$')&&
		(positionPacket[249] == 'G')&&
		(positionPacket[250] == 'P')&&
		(positionPacket[251] == 'R')&&
		(positionPacket[252] == 'M')&&
		(positionPacket[253] == 'C'))
		{
			reading = false;
			for(int i = 254; ((i < 554)&&(file.good())); i++)
			{
				positionPacket[i] = buff;
				buff = file.get();
			}
		}
	}
	if (file.good()) success = true;
	return success;
}
