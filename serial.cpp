#include "serial.h"

int serialOpen(string uart, int baud)
{
	int serialFd;
	if((serialFd = open(uart.c_str(), O_RDWR|O_NOCTTY|O_NDELAY|O_NONBLOCK))<0)
	{
		perror("serialopen failded");
		return -1;
	}
	else
	{
		if(0 == setSerialOpt(serialFd, baud, 8, 'N', 1))
			return serialFd;
		else
			return -1;
	}
}

int setSerialOpt(int fd,int nSpeed, int nBits, char nEvent, int nStop)
{
    struct termios newtio,oldtio;
    //读出原来的配置信息，按理说之所以读出来，是有部分数据不需要改，但感觉这里是这里对新的结构体配置，也没用到读出来的值
    if  ( tcgetattr( fd,&oldtio)  !=  0) { 	
	    perror("SetupSerial 1");
	    return -1;
    }
    memset(&newtio,0,sizeof( newtio ));
    //bzero( &newtio, sizeof( newtio ) );		//新结构体清0
    newtio.c_cflag  |=  CLOCAL | CREAD;
    newtio.c_cflag &= ~CSIZE;

    switch( nBits )
    {
    case 7:
	    newtio.c_cflag |= CS7;
	    break;
    case 8:
	    newtio.c_cflag |= CS8;
	    break;
    }
    /***		奇偶校验		***/
    switch( nEvent )
    {
    case 'O':
	    newtio.c_cflag |= PARENB;
	    newtio.c_cflag |= PARODD;
	    newtio.c_iflag |= (INPCK | ISTRIP);
	    break;
    case 'E': 
	    newtio.c_iflag |= (INPCK | ISTRIP);
	    newtio.c_cflag |= PARENB;
	    newtio.c_cflag &= ~PARODD;
	    break;
    case 'N':  
	    newtio.c_cflag &= ~PARENB;
	    break;
    }
    /***		设置波特率		***/
    switch( nSpeed )
    {
	case 2400:
		cfsetispeed(&newtio, B2400);
		cfsetospeed(&newtio, B2400);
		break;
	case 4800:
		cfsetispeed(&newtio, B4800);
		cfsetospeed(&newtio, B4800);
		break;
	case 9600:
		cfsetispeed(&newtio, B9600);
		cfsetospeed(&newtio, B9600);
		break;
	case 38400:
		cfsetispeed(&newtio, B38400);
		cfsetospeed(&newtio, B38400);
		break;
	case 57600:
		cfsetispeed(&newtio, B57600);
		cfsetospeed(&newtio, B57600);
		break;
	case 115200:
		cfsetispeed(&newtio, B115200);
		cfsetospeed(&newtio, B115200);
		break;
	case 460800:
		cfsetispeed(&newtio, B460800);
		cfsetospeed(&newtio, B460800);
		break;
	default:
		cfsetispeed(&newtio, B9600);
		cfsetospeed(&newtio, B9600);
		break;
    }
    /***		设置停止位		***/
    if( nStop == 1 )
	newtio.c_cflag &=  ~CSTOPB;
    else if ( nStop == 2 )
	newtio.c_cflag |=  CSTOPB;
    /*设置等待时间和最小接收字符*/
	newtio.c_cc[VTIME]  = 0;
	newtio.c_cc[VMIN] = 50;			//设置阻塞的最小字节数，阻塞条件下有效
    /*处理未接收字符*/ 
	tcflush(fd,TCIFLUSH);
    /*激活新配置*/
    if((tcsetattr(fd,TCSANOW,&newtio))!=0)
    {
		perror("com set error");
		return -1;
    }
    
    //	printf("set done!\n");
    return 0;
}

