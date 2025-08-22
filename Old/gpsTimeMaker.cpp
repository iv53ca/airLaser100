#include "gpsTimeMaker.hpp"
#include <iostream>

//*
// TODO(tkemper) : seriously!777!?? just remove one / from the previous line.
int LcharToInt(char input)
{
    switch (input)
    {
    case '0':
        return 0;
    case '1':
        return 1;
    case '2':
        return 2;
    case '3':
        return 3;
    case '4':
        return 4;
    case '5':
        return 5;
    case '6':
        return 6;
    case '7':
        return 7;
    case '8':
        return 8;
    case '9':
        return 9;
    }
	return -100;
}
/*/
int LcharToInt(char input)
{
    return input - '0';
}
//*/

// TODO(tkemper) : tell someone who actually knows the subject about this nonsense
int getGPSHour(char* timeData)
{
    int year, month, day, hour, minut, second;

    day     = LcharToInt(timeData[6])*10 + LcharToInt(timeData[7]);
    month   = LcharToInt(timeData[8])*10 + LcharToInt(timeData[9]);
    year    = LcharToInt(timeData[10])*10 + LcharToInt(timeData[11]);
    hour    = LcharToInt(timeData[0])*10 + LcharToInt(timeData[1]);
    minut   = LcharToInt(timeData[2])*10 + LcharToInt(timeData[3]);
    second  = LcharToInt(timeData[4])*10 + LcharToInt(timeData[5]);



    std::cout <<"DEBUG :\n\tyear "<<year<<"\n\tmonth "<<month<<"\n\tday "<<day<<"\n\thour "<<hour<<std::endl;

    std::tm time_in = { 0, 0, hour, // second, minute, hour
      day, month-1, 2000 + year - 1900 }; // 1-based day, 0-based month, year since 1900

    std::time_t time_temp = std::mktime(&time_in);

    const std::tm * time_out = std::localtime(&time_temp);

    int output = (time_out->tm_wday)*24*60*60 + hour*60*60;
	std::cout <<"DEBUG : current hour = " << output <<std::endl;
    return output;
}







