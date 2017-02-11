#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#define MAX_BUF 128
#define NUMBER_OF_CONF_CALLERS 5
#define CALLER_TO_RECEIVER "/tmp/myfifo_c2r"
#define RECEIVER_TO_CALLER "/tmp/myfifo_r2c"
int main(int argc , char** argv)
{
int fd_c2r , fd_r2c , i,j;
char myfifo_c2r [128];
char myfifo_r2c [128];
sprintf(myfifo_c2r , "/tmp/FIFOtoFork%s",argv[1]);
sprintf(myfifo_r2c , "/tmp/FIFOfromFork%s",argv[1]);
char buf[MAX_BUF];

fd_c2r = open(myfifo_c2r , O_RDONLY);
fd_r2c = open(myfifo_r2c , O_WRONLY);
printf("Receiving a call in conference caller %s.\n",argv[1]);
for(i=0;i<10;i++)
{
read(fd_c2r , buf , MAX_BUF);
printf("Received: %s\n", buf); 
printf("You: ");
char buffer[MAX_BUF +1];
fgets(buffer ,MAX_BUF ,stdin);
for(j=0;buffer[j]!='\0' && buffer[j]!='\n';j++);
buffer[j]='\0';
write(fd_r2c , buffer , MAX_BUF); 
}
close(fd_r2c);
close(fd_c2r);
//unlink(myfifo_r2c);
return 0;
}