#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#define MAX_BUF 128
#define CALLER_TO_RECEIVER "/tmp/myfifo_c2r"
#define RECEIVER_TO_CALLER "/tmp/myfifo_r2c"
int main(int argc , char** argv)
{
unlink(CALLER_TO_RECEIVER);
unlink(RECEIVER_TO_CALLER);
char* fifo_filename1=CALLER_TO_RECEIVER;
if (mkfifo(fifo_filename1 ,0666)==-1) 
{
printf("Unable to open fifo. Error\n");
abort();
}
char* fifo_filename2=RECEIVER_TO_CALLER;//S_IRUSR|S_IWUSR
if (mkfifo(fifo_filename2 ,0666)==-1)
{
printf("Unable to open fifo. Error\n");
abort();
}
pid_t pid;
if ((pid=fork()) <0)
{
printf("Error while forking. Abort\n");
abort();
}
else if (pid==0)
{
char** argv2=(char**)malloc(sizeof(char*)*5);
argv2[0]="gnome-terminal";
argv2[1]="-x";
argv2[2]="/home/baidik1/OSLab/telephone_caller";
argv2[3]=NULL;
execvp(argv2[0], argv2);
}
else 
{
char** argv2=(char**)malloc(sizeof(char*)*5);
argv2[0]="gnome-terminal";
argv2[1]="-x";
argv2[2]="/home/baidik1/OSLab/telephone_receiver";
argv2[3]=NULL;
sleep(2);
execvp(argv2[0], argv2);
}
return 0;
}

