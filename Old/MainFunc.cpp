
#include <iostream>
#include "gpsTimeMaker.hpp" // ��������� ���� ��� gps �������� ��������� ����
#include <cmath>
#include <fstream>
#include <iomanip>
#include "matrixDeadline.hpp"

//TODO(tkemper) : https://en.cppreference.com/w/cpp/header/numbers
#define PI 3.14159265

#define leapSeconds 18 //�������� ������� ����� gpsTime � utcTime

#include "packetDataClass.hpp"


#include "MainFunc.hpp"


#include "PcapReader.hpp"
#include "positionPacket.hpp"
#include "singleReturnPointPacket.hpp"
#include "NMEAReader.hpp"



int MainScanFunc (
                  const char *str_to_Pcap,
                  const char *str_to_IE,
                  unsigned int uint_rays,
                  unsigned int uint_packetSkip
                  )
{

    int vAngle[] = {-15, 1, -13, 3, -11, 5, -9, 7, -7, 9, -5, 11, -3, 13, -1, 15}; //���� ���������� ������ �� ������� ����

    double matrixRoll[3][3];
    double matrixPitch[3][3];
    double matrixHeading[3][3];
    double matrixMultiply[3][3];
    double matrixMultiplySecond[3][3];
    double matrixTranspose[3][3];

    //double RPM = 300.; // check if needed

    double Time_PerShot = 0.000002304; 

    double Time_Per16Shot = 0.000055296; 

    long long currentHour = 0; 
    int secPerHour = 3600;

    double PointTime; 

    double alpha, omega, k, radius; // One name per task !

    double LidX, LidY, LidZ;

    double LocX, LocY, LocZ;

    double UTMX, UTMY, UTMZ;

    double azimutDelta;


    cout << str_to_Pcap;
	char* filename = (char*)str_to_Pcap;
    PcapReader pcap(filename); // �� ����� ������ ����������� ������ ������




    // TODO(tkemper) : make this as a parameter.
    std::ofstream ofs; //���� XYZ ���������
    ofs.open ("XYZ.txt", std::ofstream::out);
		
	pcap.getPositionPacket();
	pcap.getDataPacket();
	pcap.getDataPacket();
	
	singleReturnPointPacket srpp;
	srpp.readBytes(pcap.dataPacket);
	positionPacket posPac;
	NMEAReader nmea;

	
    IEdataStream IEDS(str_to_IE); 

    unsigned int pointPerPac, pacOfSet; 

    pointPerPac = uint_rays;
    pointPerPac = 16;

    pacOfSet = uint_packetSkip;

    //TODO(tkemper) : spaces against binary operators!! This applies to many more lines of code here.
    cout << "\n\t" << pacOfSet << "\n";

    long long pcount = -1;

    for(unsigned int i = 0; i < pacOfSet; i++)
    {
        pcap.getDataPacket();
        pcount++;
    }
	for(int i = 0; i < 20; i++)
	
		

	pcap.getPositionPacket();
	posPac.readBytes(pcap.positionPacket);
	nmea.read((char*)posPac.packet.NMEASentance);
    cout << "DEBUG : "<<currentHour<<endl;
    currentHour = getGPSHour(nmea.pTime);
	//________
	//cout << "hardcore current hour override\n";
	//cout << "please enter correct GPS seconds of week : ";
	//cin >> currentHour;
	//_______
    cout << "DEBUG : "<<currentHour<<endl;


    uint32_t PREVtimestamp = srpp.packet.timeStamp;

    double skipPointTime = (double)currentHour + (double)PREVtimestamp* 1e-6 + leapSeconds ;

    int skipedPackets = 0;

	cout << "DEBUG SKIP POINT TIME = " << skipPointTime;
	
    while(IEDS.FgpsTime > skipPointTime) //����������
    {
		pcap.getDataPacket();
		srpp.readBytes(pcap.dataPacket);
        skipedPackets++;
        skipPointTime = (double)currentHour + (double)srpp.packet.timeStamp* 1e-6 + leapSeconds ;
    }
    cout <<"\nskiped "<<skipedPackets<<" packets"<<endl;


    
    while (pcap.getDataPacket())
    {
        srpp.readBytes(pcap.dataPacket);
		pcount++;

		if (srpp.packet.timeStamp < PREVtimestamp)
		{
		PREVtimestamp = srpp.packet.timeStamp;
	
		currentHour+= 3600;
		cout << "\n\tNEW HOUR\n";
		}else{
		PREVtimestamp = srpp.packet.timeStamp;
	
	
		if(pcount % 10000 == 0)cout << "packet "<<pcount<<endl;
		

	
			//��������� ���� � ��� x_x
	
			for(int i = 0; i < 11; i++) //deleted 12-th datablock
			{
				for(int j = 0; j < pointPerPac; j++) //� ������ ��������� 32 �����
				{
					if( 1) // getting to central rays (numbers 1 and 14)
					{
						if(pointPerPac == 1) j++;
						
						if(srpp.packet.dataBlock[i].firingSequence[j/16].channelDataPoint[j%16].distance != 0) 
						{
							//__________/����_������������_������������__________________
							if(i != 11)
							{
								azimutDelta = srpp.packet.dataBlock[i+1].azimuth*0.01 + 
							( (srpp.packet.dataBlock[i].azimuth > srpp.packet.dataBlock[i+1].azimuth)*360. ) - 
							srpp.packet.dataBlock[i].azimuth*0.01;
							
							
								if(azimutDelta > 360.) azimutDelta -= 360.;
								azimutDelta = azimutDelta / (Time_Per16Shot*2.);
							}
							alpha = srpp.packet.dataBlock[i].azimuth*0.01 + azimutDelta*(Time_Per16Shot*((int)j/16) + 
							(double)Time_PerShot*(j%16)); // maybe shoud "...(double)Time_PerShot*((j-1)%16))"
							
							if (alpha >= 360.) alpha -= 360.;
							//__________����_������������_������������/__________________
	
	
							omega = vAngle[j%16]; //� ��������
							
							//VERTICAL CORRECTION!!!!!!!
							radius = srpp.packet.dataBlock[i].firingSequence[j/16].channelDataPoint[j%16].distance*0.002; 
							
	
							//LidX = radius * cos(omega*PI/180.)*sin(alpha*PI/180.);
							LidX =  - radius * cos(omega*PI/180.)*sin(alpha*PI/180.);
							LidY = radius * cos(omega*PI/180.)*cos(alpha*PI/180.);
							LidZ = radius * sin(omega*PI/180.);
							
							
							PointTime = (double)currentHour + (double)srpp.packet.timeStamp* 1e-6 + 
								Time_Per16Shot*(2.*i + (double)((int)j/16)) + (double)Time_PerShot*(j%16) + leapSeconds;
	
	
							LocX =  LidX;
							LocY =  LidZ;
							LocZ =  LidY;
							if( sqrt((LocX*LocX) + (LocY*LocY)) < 55. )
							{
								while(IEDS.FgpsTime < PointTime) //����������
								{
									IEDS.update();
					//      	         cout<<"\tupdate"<<PointTime<<"\n";
								}
								IEDS.interp(PointTime); //�������� ������������
		
								alpha   = IEDS.interp_FPitch; // ������� �������
								omega   = IEDS.interp_FRoll;
								k       = IEDS.interp_FHeading;
								if (k > 360.) k -= 360.;
		
								getRoll(matrixRoll, omega);
								getPitch(matrixPitch, alpha);
								getYaw(matrixHeading, k);
								multiply(matrixRoll, matrixPitch, matrixMultiply);
								multiply(matrixMultiply, matrixHeading, matrixMultiplySecond);
								transpose(matrixMultiplySecond, matrixTranspose);
								finalMultiply(matrixTranspose, LocX, LocY, LocZ, UTMX, UTMY, UTMZ);
		
								UTMX += IEDS.interp_FEasting;
		
								UTMY += IEDS.interp_FNorthing;
		
								UTMZ += IEDS.interp_FH_Ell;
		
								//lebug <<fixed<<setprecision(8)<< IEDS.FEasting <<" "<<IEDS.FNorthing<<" "<<IEDS.FH_Ell<<" "<<IEDS.FHeading<<"\n";
								
								ofs <<setprecision(8)<<fixed<< UTMX <<" "<<UTMY<<" "<<UTMZ<<" "<<
									+srpp.packet.dataBlock[i].firingSequence[j/16].channelDataPoint[j%16].calibratedReflectivity
									<<" "<< +k <<"\n";
							}//if( sqrt((LocX*LocX) + (LocY*LocY)) < 55. )
	
	

						}
					}
	
	
	
	
	
	
	
				}
			}
		}
	
	
	
    }




    cout << "\n\tdone" <<endl;

    ofs.close();







    return 0;
}