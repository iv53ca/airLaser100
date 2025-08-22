#ifndef NMEAREADERGUARD
#define NMEAREADERGUARD

class NMEAReader
{
public:
	char pTime[12];
	NMEAReader();
	~NMEAReader();
	void read(char*);
};

#endif // NMEAREADERGUARD
