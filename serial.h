#ifndef SERIAL_H
#define SERIAL_H

#include <fcntl.h>
#include <cstring>
#include <termios.h>
#include <stdio.h>
#include <string>

using std::string;

int serialOpen(string uart, int baud);
int setSerialOpt(int fd,int nSpeed, int nBits, char nEvent, int nStop);

#endif
