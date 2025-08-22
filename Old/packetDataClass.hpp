/*
*   ���� ���� ��� �� ������� �������� (19.10.20)
*
*
*
*/

#ifndef PACKETDATACLASS_H_INCLUDED
#define PACKETDATACLASS_H_INCLUDED

#include <fstream>
#include <iostream>
#include <tuple>
#include <cstdint>

using namespace std;

//_______�����_���_�����_��_�����_����______

template<int End = 0>
std::tuple<> parse(const uint8_t* data) {
    return std::make_tuple();
}

template<typename Type, typename ...Args>
auto parse(const uint8_t* data) {
    Type v = static_cast<const Type*>(static_cast<const void*>(data))[0];
    return std::tuple_cat(std::make_tuple(std::move(v)), parse<Args...>(data + sizeof(Type)));
}

//___________________________________________



union trnsferU //����� ��� �������� �������� ������
{
    uint16_t u16;
    uint32_t u32;
    char ch[4];
};



struct rawPacketData //��������� ��� �������� ������� ������
{
    struct
    {
        uint8_t data[42];
    }header; // ���������, �� ������ ���� �����������

    struct
    {
        uint16_t flag; //���� ������ ����� ������ (0xffee)
        uint16_t azimut; //������ ����� ������

        struct
        {
            uint16_t distance; //��������� �� �����
            uint8_t calibratedReflectivity; //"����" ���������� �������
        }DataPoint[32]; //32 ����� �� ����
    }DataBlock[12]; //12 ������ ������

    uint32_t timestamp; //����� ������� ������
    uint16_t factoryBytes; //���������� � ������ (���� �� ���������������)
};

//����� ��� ������������ ������ �� .pcap ����� ������
class rawLidarDataStream
{
public:
    bool notEnd = true;
    const char* fname; //��� �����
    ifstream pcapFile;
    rawLidarDataStream(){}; //�� ������������, �� �������!!!
    ~rawLidarDataStream(){pcapFile.close();};
    rawLidarDataStream(const char* filename);
    char* buffer; // ����� � ������� �������� ���� ����

    int length; //������ ������
    int counter = 0; //������� ������ � ������


    void getPacket(rawPacketData &packet); //����� ��� ������������ ��������� ������ ����� (���������� nmea ������)

    void getTime(char* timeData); // ����� ��� ������������ ���� nmea �������� (���������� ����� ������)



private:
    void init();

};


//�� ������������
struct lidarXYZ
{
    long long x, y, z;
};

//����� ��� ������������ ������ �� IE �����
//���� �������� �� ������� ������� � 25-�� ������
class IEdataStream
{
public:
    ifstream IEFile;
    string input; //�������� ������
    string last_input;//������ �� �������� (��� �������� ������������)


    //��� ������ ������, � ������� � ����� �������� (����� ������ �� ������������)
    //F - float; I - integer;
    double FgpsTime;
    unsigned long long IgpsTime;

    double FUTCTime;
    unsigned long long IUTCTime;

    double FEasting;
    unsigned long long IEasting;

    double FNorthing;
    unsigned long long INorthing;

    double FH_Ell;
    unsigned long long IH_Ell;

    double FRoll;
    long long IRoll;

    double FPitch;
    long long IPitch;

    double FHeading;
    long long IHeading;



    //______��� ������������� �� � ��� ������� ����� ����� ��� ������, ����� ����� ����������_____
    double last_FgpsTime;
    unsigned long long last_IgpsTime;

    double last_FUTCTime;
    unsigned long long last_IUTCTime;

    double last_FEasting;
    unsigned long long last_IEasting;

    double last_FNorthing;
    unsigned long long last_INorthing;

    double last_FH_Ell;
    unsigned long long last_IH_Ell;

    double last_FRoll;
    long long last_IRoll;

    double last_FPitch;
    long long last_IPitch;

    double last_FHeading;
    long long last_IHeading;



    double interp_FgpsTime;
    unsigned long long interp_IgpsTime;

    double interp_FUTCTime;
    unsigned long long interp_IUTCTime;

    double interp_FEasting;
    unsigned long long interp_IEasting;

    double interp_FNorthing;
    unsigned long long interp_INorthing;

    double interp_FH_Ell;
    unsigned long long interp_IH_Ell;

    double interp_FRoll;
    long long interp_IRoll;

    double interp_FPitch;
    long long interp_IPitch;

    double interp_FHeading;
    long long interp_IHeading;
    //_______


    IEdataStream(){}; //�� �������, �� �������������
    IEdataStream(const char* filename);
    ~IEdataStream(){IEFile.close();};
    void update(); // �������� ������ � ������;
    void interp(double timestamp); //������������������ ��� ������� �����



};


#endif // PACKETDATACLASS_H_INCLUDED
