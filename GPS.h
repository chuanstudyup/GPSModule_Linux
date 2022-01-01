#ifndef GPS_H
#define GPS_H

#include <string>
#include <iostream>
#include <vector>

using std::vector;
using std::string;
using std::cout;
using std::endl;

vector<string> testSplit(string srcStr, const string& delim);
unsigned char hexToDec(unsigned char hex);

class GPS
{
public:
	GPS();
	~GPS();
	void init(string serial, int baud);
	void serialRead();
	
	
	double lat, lon;
	float velocity, course, altitude;
	uint8_t SVs;
	float HDOP;
	
	
private:
	const string header = "$GN";  
	const string footer = "\r\n";
	string payload;
	
	int _serialFd;
	char _serialBuf[256];
	
    bool parse(string str, int &parseLen);
    void parseNAME(string);
	bool checkCRC();
};

#endif
