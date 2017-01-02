#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <fcntl.h>

int main()
{
	int fd, err=0;
	
	fd = open("/dev/si4703_driver", O_RDWR);
	if(fd < 0)
	{
		perror("open:");
		return -1;
	}
	close(fd);
	return 0;
}
