#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<fcntl.h>
#include<string.h>
#include<unistd.h>

int main()
{
	int fd, err=0;
	
	fd = open("/dev/si4703_driver", O_RDWR);
	if(fd < 0)
	{
		perror("open:");
		return -1;
	}
	char stringToSend[4] = "hi!";
	write(fd,stringToSend,strlen(stringToSend));
	close(fd);
	return 0;
}
