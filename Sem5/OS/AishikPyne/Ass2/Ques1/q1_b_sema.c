#include <stdio.h>          /* printf()                 */
#include <stdlib.h>         /* exit(), malloc(), free() */
#include <sys/types.h>      /* key_t, sem_t, pid_t      */
#include <sys/shm.h>        /* shmat(), IPC_RMID        */
#include <sys/stat.h>
#include <errno.h>          /* errno, ECHILD            */
#include <semaphore.h>      /* sem_open(), sem_destroy(), sem_wait().. */
#include <fcntl.h>          /* O_CREAT, O_EXEC          */
#include <sys/wait.h>
#include <signal.h>
#include <unistd.h>

void sig_handler(int signo)
{
    if (signo ==  SIGINT)
    {
        // does not close the shared memory and semaphores
        printf("*****WARNING: Shared memory and semaphores not propoerly closed *****\n");
        _exit(EXIT_FAILURE);
    }
}
int main (int argc, char **argv){
    int i, j;                        /*      loop variables          */
    key_t shmkey;                 /*      shared memory key       */
    int shmid;                    /*      shared memory id        */
    sem_t *sem;                   /*      synch semaphore         *//*shared */
    pid_t pid;                    /*      fork pid                */
    int *p;                       /*      shared variable         *//*shared */
    unsigned int n;               /*      fork count              */
    unsigned int init_value=0;    /*      semaphore value         */

    if (signal(SIGINT, sig_handler) == SIG_ERR)
    printf("\ncan't catch SIGINT\n");

    /* initialize a shared variable in shared memory */
    shmkey = ftok ("/dev/null", 5);       /* valid directory name and a number */
    printf ("shmkey for p = %d\n", shmkey);
    shmid = shmget (shmkey, sizeof (int), 0644 | IPC_CREAT);
    if (shmid < 0){                           /* shared memory error check */
        perror ("shmget\n");
        exit (1);
    }

    p = (int *) shmat (shmid, NULL, 0);   /* attach p to shared memory */
    *p = 0;
    printf ("p=%d is allocated in shared memory.\n\n", *p);

    /********************************************************/

    n=2;

    /* initialize semaphores for shared processes */
    sem = sem_open ("pSem", O_CREAT | O_EXCL, 0644, init_value);
    /* name of semaphore is "pSem", semaphore is reached using this name */

    printf ("semaphores initialized.\n\n");

    //pid_t pids[2];
    /* fork child processes */
    for (i = 0; i < n; i++){
        pid = fork ();
        if (pid < 0) {
        /* check for error      */
            sem_unlink ("pSem");
            sem_close(sem);
            /* unlink prevents the semaphore existing forever */
            /* if a crash occurs during the execution         */
            printf ("Fork error.\n");
        }
        else if (pid == 0)
            break;                  /* child processes */
    }


    /******************   PARENT PROCESS   ****************/
    if (pid != 0){
        /* wait for all children to exit */
        while (pid = waitpid (-1, NULL, 0)){
            if (errno == ECHILD)
                break;
        }

        printf ("\nParent: All children have exited.\n");
        //sem_post(sem);
        /* shared memory detach */
        shmdt (p);
        shmctl (shmid, IPC_RMID, 0);

        /* cleanup semaphores */
        sem_unlink ("pSem");
        sem_close(sem);
        /* unlink prevents the semaphore existing forever */
        /* if a crash occurs during the execution         */
        exit (0);
    }
    /******************   CHILD PROCESS   *****************/
    else{
        if (i==0)
        {
            for (j=0; j<10; j++)
            {
                sem_wait (sem);           /* P operation */
                printf ("Child - X  PID - %d  Iteration - %d\n",getpid(), j);
                sleep(1);
            }
        }
        else if (i==1)
        {
            for (j=0; j<10; j++)
            {
                printf ("Child - Y  PID - %d  Iteration - %d\n",getpid(), j);
                sleep(1);
                sem_post(sem);
            }
        }
        exit (0);
    }
}
