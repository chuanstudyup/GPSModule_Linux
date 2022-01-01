// testMain.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
// g++ GPS.cpp testMain.cpp serial.cpp -o testMain

/* NMEA examples
$GNRMC,083712.40,A,3030.83159,N,11424.56558,E,0.150,,291221,,,A*65\r\n
$GNRMC,083712.60,A,3030.83159,N,11424.56559,E,0.157,,291221,,,A*61\r\n
$GNRMC,083712.80,A,3030.83158,N,11424.56558,E,0.033,,291221,,,A*6C\r\n
$GNGGA,083712.80,3030.83158,N,11424.56558,E,1,10,1.00,49.7,M,-10.6,M,,*5B\r\n
*/

#include <iostream>
#include <math.h>
#include "GPS.h"

using std::cout;
using std::endl;

int main()
{
	GPS gps;
	gps.init("/dev/ttyUSB0",38400);
	while(1)
	{
		gps.serialRead();
		cout<<"lat" << gps.lat << endl;
		cout<<"lng" << gps.lon << endl;
		cout<<"velocity" << gps.velocity << endl;
		cout<<"course" << gps.course << endl;
		cout<<"altitude" << gps.altitude << endl;
		cout<<"SVs" << static_cast<int>(gps.SVs) << endl;
		cout<<"HDOP" << gps.HDOP << endl;
		usleep(100000);
	}
	return 0;
}
