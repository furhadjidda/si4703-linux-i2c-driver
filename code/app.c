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
	unsigned int nc = 0;
	nc = 981; //this is 101.1 The Fox In Kansas City Classic Rock!!
	nc *= 10;  //this math is for USA FM only
	nc -= 8750;
	nc /= 20;
	
	fd = open("/dev/i2cchar", O_RDWR);
	if(fd < 0)
	{
		perror("open:");
		return -1;
	}


	char list1[] = {0,0,0,0,0,0,0,0,0,0,129,0};
	write(fd,list1,sizeof(list1));
	sleep(1);

	char list2[] = {64,1};
	write(fd,list2,sizeof(list2));
	sleep(1);

	char list3[] = {64,1,0,0,0,0,0,1};
	write(fd,list3,sizeof(list3));
	sleep(1);

	char list4[] = {64,1,128,nc};
	write(fd,list4,sizeof(list4));
	sleep(1);

	char list5[] = {64,1,0,nc};
	write(fd,list5,sizeof(list5));
	sleep(1);

	close(fd);
	return 0;
}
