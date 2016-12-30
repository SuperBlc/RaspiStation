#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <errno.h>

#define SIZE 10
#define MINUTES 5
#define SECONDS 60
#define SHELLPATH  "/home/pi/LOT/source/curlUpload.sh "
char* getTime();

int main(int argc,char* argv[])
{
	//open serial
	char *serial_port="/dev/ttyUSB0";
	int fd = open(serial_port,O_RDWR);
	if(fd == -1)
	{
		perror("serial port open failed\n");
	}
	else
	{
		printf("open %s successfully\n",ttyname(fd));
	}

	struct termios options;
	int status;

	tcgetattr(fd,&options);
	options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
	options.c_cflag |= CLOCAL | CREAD;
	//set baud rate
	cfsetispeed(&options,B4800);
	cfsetospeed(&options,B4800);
	//set databits
	options.c_cflag &= ~CSIZE;
	options.c_cflag |= CS8;
	//set parity
	options.c_cflag &= ~PARENB;
	options.c_iflag &= ~INPCK;
	//set stop bits
	options.c_cflag &= ~CSTOPB;
	status = tcsetattr(fd,TCSANOW,&options);
	if(status != 0)
	{
		perror("tcsetattr fd");
		return;
	}

	int nread,nwrite;
	char rbuff[SIZE]; // reading buffer
	char wchar = '1'; // write a character to the UART
	int minute;		
	char command[80] = { 0 };
	while(1)
	{
		memset(rbuff,0,SIZE);
		nwrite = write(fd,&wchar,1);
		if(!nwrite)
		{
			printf("write error\n");
			close(fd);
			return -1;
		}
		
		if((nread = read(fd,rbuff,SIZE)) > 0) 
		{
			rbuff[nread] = '\0';
			strcat(command,SHELLPATH);
			strcat(command,rbuff);
			system(command);
		}
		memset(command,0,80);
		for(minute = 0; minute < MINUTES; minute++)
		{
			sleep(SECONDS);
		}
		
	}
	close(fd);

	return 0;
}

