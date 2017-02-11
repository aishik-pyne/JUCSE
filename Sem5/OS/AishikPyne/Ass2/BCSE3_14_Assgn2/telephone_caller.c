#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/wait.h>
#define MAX_BUF 128
#define NUMBER_OF_CONF_CALLERS 3
#define CALLER_TO_RECEIVER "/tmp/myfifo_c2r"
#define RECEIVER_TO_CALLER "/tmp/myfifo_r2c"
#define READ_END 0
#define WRITE_END 1

int main()
{
int fd_c2r , fd_r2c , i,j;
char * myfifo_c2r = CALLER_TO_RECEIVER;
char * myfifo_r2c = RECEIVER_TO_CALLER;
char buf[MAX_BUF];
fd_c2r = open(myfifo_c2r , O_WRONLY);
fd_r2c = open(myfifo_r2c , O_RDONLY | O_NONBLOCK);
printf("You're the caller.\n");
char fifo_filename_tofork [128];
char fifo_filename_fromfork [128];
int forked_fifo[NUMBER_OF_CONF_CALLERS][2];
for(i=0;i<NUMBER_OF_CONF_CALLERS;i++)
{
sprintf(fifo_filename_tofork , "/tmp/FIFOtoFork%d",i);
unlink(fifo_filename_tofork);
if (mkfifo(fifo_filename_tofork ,0666)==-1)
{
printf("Unable to open fifo. Error\n");
abort();
}
sprintf(fifo_filename_fromfork , "/tmp/FIFOfromFork%d",i);
unlink(fifo_filename_fromfork);
if (mkfifo(fifo_filename_fromfork ,0666)==-1)
{
printf("Unable to open fifo. Error\n");
abort();
}
}
for(i=0;i<NUMBER_OF_CONF_CALLERS;i++) 
{
pid_t pid=fork();
if (pid <0)
{
printf("Error in forking. Exiting");
abort();
}
else if (pid!=0) 
{
sprintf(fifo_filename_tofork , "/tmp/FIFOtoFork%d",i);
sprintf(fifo_filename_fromfork , "/tmp/FIFOfromFork%d",i);
forked_fifo[i][0]=open(fifo_filename_tofork , O_WRONLY);
forked_fifo[i][1]=open(fifo_filename_fromfork , O_RDONLY |
O_NONBLOCK);
}
else
{
char** argv2=(char**)malloc(sizeof(char*)*5);
char str1[10];
sprintf(str1 ,"%d",i);
argv2[0]="gnome-terminal"; 
argv2[1]="-x";
argv2[2]="/home/baidik1/OSLab/telephone_receiver_secondary";
argv2[3]=str1;
argv2[4]=NULL;
sleep(2);
execvp(argv2[0], argv2);
exit(0);
}
}
for(i=0;i<10;i++)
{
printf("You: ");
char buffer[MAX_BUF +1];
fgets(buffer ,MAX_BUF ,stdin);
for(j=0;buffer[j]!='\0' && buffer[j]!='\n';j++);
buffer[j]='\0';
write(fd_c2r , buffer , MAX_BUF); 
for(j=0;j<NUMBER_OF_CONF_CALLERS;j++)
{
write(forked_fifo[j][0], buffer , MAX_BUF);
}
if (read(fd_r2c , buf , MAX_BUF)!=-1) 
{
printf("Received: %s\n", buf);
for(j=0;j<NUMBER_OF_CONF_CALLERS;j++)
{
write(forked_fifo[j][0], buf, MAX_BUF);
}
}
for(j=0;j<NUMBER_OF_CONF_CALLERS;j++) 
{
buf[0]='\0';
read(forked_fifo[j][1], buf , MAX_BUF);
printf("Received from conference caller %d: %s\n", j,buf);
}
}
int n=NUMBER_OF_CONF_CALLERS;
int status;
pid_t pid;
while(n>0)
{
pid=wait(&status);
fprintf(stderr ,"Child Process with PID = %ld exited with status 0x%x.\n",(long)pid ,status);
n--;
}
close(fd_r2c);
close(fd_c2r);
for(j=0;j<NUMBER_OF_CONF_CALLERS;j++) 
{
sprintf(fifo_filename_tofork , "/tmp/FIFOtoFork%d",j);
sprintf(fifo_filename_fromfork , "/tmp/FIFOfromFork%d",i);
close(forked_fifo[j][0]);
close(forked_fifo[j][1]);
unlink(fifo_filename_tofork);
unlink(fifo_filename_fromfork);
}
unlink(myfifo_c2r);
return 0;
}
