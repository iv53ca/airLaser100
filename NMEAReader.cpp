#include "NMEAReader.hpp"

NMEAReader::NMEAReader()
{
    for(int i = 0; i < 12; i++)
        pTime[i] = 0;
}

NMEAReader::~NMEAReader()
{
}

void NMEAReader::read(char* fullSentance)
{
    int counter = 0;
    int comaCounter = 0;
    while (comaCounter < 1)
    {
        if(fullSentance[counter++] == ',')
            comaCounter++;
    }
    for(int i = 0; i < 6; i++)
        pTime[i] = fullSentance[counter++];
    while (comaCounter < 9)
    {
        if(fullSentance[counter++] == ',')
            comaCounter++;
    }
    for(int i = 6; i < 12; i++)
        pTime[i] = fullSentance[counter++];
}

