#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#define MAX_BUF 128
#define NUMBER_OF_CONF_CALLERS 5
#define CALLER_TO_RECEIVER "/tmp/myfifo_c2r"
#define RECEIVER_TO_CALLER "/tmp/myfifo_r2c"
int main(int argc , char** argv)
{
int fd_c2r , fd_r2c , i,j;
char * myfifo_c2r = CALLER_TO_RECEIVER; 
char * myfifo_r2c = RECEIVER_TO_CALLER;
char buf[MAX_BUF];
fd_c2r = open(myfifo_c2r , O_RDONLY); 
fd_r2c = open(myfifo_r2c , O_WRONLY);
printf("Receiving a call.\n");
for(i=0;i<10;i++)
{
if(read(fd_c2r , buf , MAX_BUF)!=-1)
printf("Received: %s\n", buf);
printf("You: ");
char buffer[MAX_BUF +1];
fgets(buffer ,MAX_BUF ,stdin);
for(j=0;buffer[j]!='\0' && buffer[j]!='\n';j++);
	buffer[j]='\0';
write(fd_r2c , buffer , MAX_BUF);
}
close(fd_c2r);
unlink(myfifo_r2c);
return 0;
}
