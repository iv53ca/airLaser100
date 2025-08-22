#ifndef MAINFUNC_H_INCLUDED
#define MAINFUNC_H_INCLUDED

#include<string>

using namespace std;



//const double angPerShot = 0.0062208; //check if still needed
//^^^ �������, ������� ���������� �� �������

int MainScanFunc (
                  const char *str_to_Pcap,
                  const char *str_to_IE,
                  unsigned int uint_rays = 1,
                  unsigned int uint_packetSkip = 0
                  );



#endif // MAINFUNC_H_INCLUDED
