#include  <stdio.h>
#include  <string.h>
#include  <sys/types.h>
#include  <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define   MAX_COUNT  10
#define   BUF_SIZE   100

void  main(void)
{
     pid_t  pid;
     int    i;
     char   buf[BUF_SIZE];
     int parent_pid = getpid();
     printf("Parent Id is %d\n", parent_pid);
     fork();
     int child_pid = getpid();
     if(parent_pid == child_pid)
          fork();

     if(parent_pid!=getpid()){
       for (i = 1; i <= MAX_COUNT; i++) {
            printf("This line is from child pid %d, Iteration = %d\n", getpid()%10, i);
            int sleep_time = rand() % 5 + 1;
            sleep(sleep_time);
       }
     }
}
