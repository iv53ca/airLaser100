/*
*   ���� ���� ��� �� ������� �������� (19.10.20)
*
*
*
*/


#include "packetDataClass.hpp"
#include <sstream>
#include <cmath>
#include <cstdint>




rawLidarDataStream::rawLidarDataStream(const char* filename)
{
    cout << "\ninside rawlidar data stream\n";
    pcapFile.open(filename, ios::in | ios::binary);
    cout << "\nopenfile\n";
    if (pcapFile)
    {
        cout << "\nsucsses in oppening file\n";

        // get length of file:
        pcapFile.seekg (0, pcapFile.end);
        length = pcapFile.tellg();
        pcapFile.seekg (0, pcapFile.beg);
        cout << "\nwhat_01, " << length << endl;
        cout << "\nFFS";



        buffer = new(std::nothrow) char [length];








        cout << "\nwhat_02\n";
//        cout << length;

        pcapFile.read (buffer,length);
        cout << "\nwhat_03\n";
        if (!pcapFile)
        {
            // An error occurred!
            // pcapFile.gcount() returns the number of bytes read.
            // calling pcapFile.clear() will reset the stream state
            // so it is usable again.
            cout << "ERR1ERR"<<endl;
        }
        cout << "\nstarting init()\n";
        init();

    }else{
        cout << "\nERROR : can't open pcap file !!!\n";
        cout << "\nlog : try'd opening file by path : ";
        cout << filename <<endl;
    }

}


void rawLidarDataStream::init()
{

    counter = 0;


}



void rawLidarDataStream::getPacket(rawPacketData &packet)
{
    if(counter >= length)
    {
        notEnd = false;
        return;
    }

    int ffCounter = 0;

    while (ffCounter < 6)
    {
        if(counter >= length)
        {
            notEnd = false;
            return;
        }
        if ((uint8_t)buffer[counter++] == 0xff)
        {
            ffCounter++;
        }else{
            ffCounter = 0;
        }
    }

    trnsferU trans;
    trans.u32 = 0;

    trans.ch[1] = buffer[counter+36];
    trans.ch[0] = buffer[counter+37];

//    cout << "\n\tLeBug : " <<hex<< trans.u16<<dec<<"\n";

    if(trans.u16 == 0xffee)
    {
        trans.u32 = 0;

        counter -= 6;




        for (int i = 0; i < 42; i++)
        {
            packet.header.data[i] = buffer[counter++];
        }

        for (int i = 0; i < 12; i++)
        {
            trans.ch[1] = buffer[counter++];
            trans.ch[0] = buffer[counter++];
            packet.DataBlock[i].flag = trans.u16;
            trans.u32 = 0;

            trans.ch[0] = buffer[counter++];
            trans.ch[1] = buffer[counter++];
            packet.DataBlock[i].azimut = trans.u16;
            trans.u32 = 0;

            for(int j = 0; j < 32; j++)
            {
                trans.ch[0] = buffer[counter++];
                trans.ch[1] = buffer[counter++];
                packet.DataBlock[i].DataPoint[j].distance = trans.u16;
                trans.u32 = 0;
                packet.DataBlock[i].DataPoint[j].calibratedReflectivity = buffer[counter++];

            }
        }

        trans.ch[0] = buffer[counter++];
        trans.ch[1] = buffer[counter++];
        trans.ch[2] = buffer[counter++];
        trans.ch[3] = buffer[counter++];
        packet.timestamp = trans.u32;
        trans.u32 = 0;

        trans.ch[1] = buffer[counter++];
        trans.ch[0] = buffer[counter++];
        packet.factoryBytes = trans.u16;
        trans.u32 = 0;
        if(counter >= length)
        {
            notEnd = false;
            return;
        }
    }else{
        getPacket(packet);
    }

}


void rawLidarDataStream::getTime(char* timeData) //����� ��� ������������ $GPRMC ��������� � ������� �� .pcap �����
{
    int ffCounter = 0;
    int comaCounter = 0;
    while (ffCounter < 6)
    {
        if ((uint8_t)buffer[counter++] == 0xff)
        {
            ffCounter++;
        }else{
            ffCounter = 0;
        }
    }

    trnsferU trans;
    trans.u32 = 0;

    trans.ch[3] = buffer[counter+242];
    trans.ch[2] = buffer[counter+243];
    trans.ch[1] = buffer[counter+244];
    trans.ch[0] = buffer[counter+245];

   // cout <<trans.ch[0]<<trans.ch[1]<<trans.ch[2]<<trans.ch[3]<<"\n";


    if(trans.u32 == 0x24475052)
    {
    //    cout <<"SUCCES\n";
        counter = counter+249;
        timeData[0] = buffer[counter++];
        timeData[1] = buffer[counter++];
        timeData[2] = buffer[counter++];
        timeData[3] = buffer[counter++];
        timeData[4] = buffer[counter++];
        timeData[5] = buffer[counter++];

        //counter+=12;//49
        while (comaCounter != 8)
        {
            if ((char)buffer[counter++] == ',')comaCounter++;
        }

        timeData[6] = buffer[counter++];
        timeData[7] = buffer[counter++];
        timeData[8] = buffer[counter++];
        timeData[9] = buffer[counter++];
        timeData[10] = buffer[counter++];
        timeData[11] = buffer[counter++];

        for(int i = 0; i < 12; i++)
        {
            cout<<timeData[i];
        }
        cout<<"\n";



    }else{
        getTime(timeData);
    }


}



IEdataStream::IEdataStream(const char* filename)
{
    IEFile.open(filename);
    for(int i = 0; i < 24; i++)
    {
        getline(IEFile, input);
    }
    update();
    update();
};

void IEdataStream::update()
{
    last_input = input;

    last_FgpsTime = FgpsTime;
    last_IgpsTime = IgpsTime;

    last_FUTCTime = FUTCTime;
    last_IUTCTime = IUTCTime;

    last_FEasting = FEasting;
    last_IEasting = IEasting;

    last_FNorthing = FNorthing;
    last_INorthing = INorthing;

    last_FH_Ell = FH_Ell;
    last_IH_Ell = IH_Ell;

    last_FRoll = FRoll;
    last_IRoll = IRoll;

    last_FPitch = FPitch;
    last_IPitch = IPitch;

    last_FHeading = FHeading;
    last_IHeading = IHeading;

    getline(IEFile, input);


    stringstream sinput;
    sinput.str(input);

    sinput >> FgpsTime;
    sinput >> FUTCTime;
    sinput >> FEasting;
    sinput >> FNorthing;
    sinput >> FH_Ell;
    sinput >> FRoll;
    sinput >> FPitch;
    sinput >> FHeading;



    IgpsTime = (trunc(FgpsTime * 100) * 10000);
    IUTCTime = (trunc(FUTCTime * 100) * 10000);
    IEasting = trunc(FEasting*1000);
    INorthing = trunc(FNorthing*1000);
    IH_Ell = trunc(FH_Ell*1000);
    IRoll = trunc(FRoll*10000);
    IPitch = trunc(FPitch*10000);
    IHeading = trunc(FHeading*10000);



}


void IEdataStream::interp(double timestamp)
{
    double delta_FgpsTime = FgpsTime - last_FgpsTime;
    unsigned long long delta_IgpsTime = IgpsTime - last_IgpsTime;

    double delta_FUTCTime = FUTCTime - last_FUTCTime;
    unsigned long long delta_IUTCTime = IUTCTime - last_IUTCTime;


    double delta_FEasting = FEasting - last_FEasting;
    //unsigned long long delta_IEasting = IEasting - last_IEasting;

    double delta_FNorthing = FNorthing - last_FNorthing;
    //unsigned long long delta_INorthing = INorthing - last_INorthing;

    double delta_FH_Ell = FH_Ell - last_FH_Ell;
    //unsigned long long delta_IH_Ell = IH_Ell - last_IH_Ell;


//_Angles

    double delta_FRoll = FRoll - last_FRoll;
	//delta_FRoll = delta_FRoll + (delta_FRoll < 180.)*360. - (delta_FRoll > 180.)*360.;
	
    //long long delta_IRoll = IRoll - last_IRoll;

    double delta_FPitch = FPitch - last_FPitch;
    //long long delta_IPitch = IPitch - last_IPitch;

    double delta_FHeading = FHeading - last_FHeading;
    //long long delta_IHeading = IHeading - last_IHeading;

//_EndOfAngles

    interp_FgpsTime = timestamp - last_FgpsTime;
//    interp_IgpsTime;

//    interp_FUTCTime;
//    interp_IUTCTime;

    interp_FEasting = last_FEasting + (delta_FEasting * (interp_FgpsTime / delta_FgpsTime));
//    interp_IEasting;

    interp_FNorthing = last_FNorthing + (delta_FNorthing * (interp_FgpsTime / delta_FgpsTime));
//    interp_INorthing;

    interp_FH_Ell = last_FH_Ell + (delta_FH_Ell * (interp_FgpsTime / delta_FgpsTime));
//    interp_IH_Ell;

    interp_FRoll = last_FRoll + (delta_FRoll * (interp_FgpsTime / delta_FgpsTime));
//    interp_IRoll;

    interp_FPitch = last_FPitch + (delta_FPitch * (interp_FgpsTime / delta_FgpsTime));
//    interp_IPitch;

    interp_FHeading = last_FHeading + (delta_FHeading * (interp_FgpsTime / delta_FgpsTime));
//    interp_IHeading;


}


