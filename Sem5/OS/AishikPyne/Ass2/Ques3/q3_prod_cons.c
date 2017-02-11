#include <stdio.h>          
#include <stdlib.h>         
#include <sys/types.h>      
#include <sys/shm.h>        
#include <sys/stat.h>
#include <errno.h>          
#include <semaphore.h>     
#include <fcntl.h>          
#include <sys/wait.h>
#include <unistd.h>
#define BUF_SIZE 25


void producer_main(int **buffer, sem_t **empty, sem_t **full, sem_t **mutex, sem_t **prod)
{
	int i;
	int *buf = *buffer;
	for (i = 1; i <= 60; i++)
	{
		sem_wait(*empty);
		sem_wait(*mutex);

		buf[buf[1]] = i;
		printf ("Producer %d produced %d at %d\n",getpid(), i, buf[1] );
		buf[1]++;
		buf[1]=(buf[1]>=BUF_SIZE+4)?4:buf[1];

		sem_post(*mutex);
		sem_post(*full);
	}
	sem_wait(*prod);
	printf ("Producer %d exits. BYE!!!\n", getpid());

}
void consumer_main(int **buffer, sem_t **empty, sem_t **full, sem_t **mutex, sem_t **prod)
{
	int i, j, flag=1;
	int *buf = *buffer;
	int val, exit;
	while (flag)
	{
		
		sem_wait(*full);
		sem_wait(*mutex);
		if (!buf[3])
		{
			buf[0] += buf[buf[2]];
			printf ("Consumer %d consumed %d at %d\n",getpid(), buf[buf[2]], buf[2] );
			//printf ("Current Total: %d\n", buf[0]);
			buf[buf[2]] = 0;
			buf[2]++;
			buf[2]=(buf[2]>=BUF_SIZE+4)?4:buf[2];
		}
		sem_getvalue(*prod,&val);
		//printf ("%d\n",val);
		//flag = 0;
		if (val==0)
		{
			flag = 0;
			for (j=4; j<(BUF_SIZE+4); j++)
			{
				if (buf[j] > 0) 
				{
					flag=1;
					break;
				}
			}
		}

		sem_post(*mutex);
		sem_post(*empty);
	}
	printf("Consumer %d exits. BYE!!!\n", getpid());
//	sem_post(*exits);
	buf[3] = 1;
	sem_post(*full); // allow other consumers to terminate normally

}
int main(int argc, char const *argv[])
{
	pid_t pid;
	int i, j, no_prod, no_cons, shmid;
	key_t shmkey;
	sem_t *full, *empty, *mutex, *prod;
	int *buffer;

	printf ("Enter no of producers: \n");
	scanf ("%d",&no_prod);
	printf ("Enter no of consumers: \n");
	scanf ("%d",&no_cons);


	//shared memory 
	shmkey = ftok ("/dev/null", 5);       /* valid directory name and a number */
    printf ("shmkey for p = %d\n", shmkey);
    shmid = shmget (shmkey, (BUF_SIZE+4)*sizeof (int), 0644 | IPC_CREAT); // 0th elem of buf to hold the total value
    if (shmid < 0){                           /* shared memory error check */
        perror ("shmget\n");
        exit (1);
    }

    buffer = (int *) shmat (shmid, NULL, 0);   /* attach p to shared memory */
    for (i=0; i<(BUF_SIZE+4); i++) buffer[i] = 0;
    buffer[1] = buffer[2] = 4;
    printf ("buffer=%d is allocated in shared memory.\n\n", *buffer);
	

	
	empty = sem_open ("eSem", O_CREAT | O_EXCL, 0644, BUF_SIZE-1);     
	full = sem_open ("fSem", O_CREAT | O_EXCL, 0644, 0);     
	mutex = sem_open ("mSem", O_CREAT | O_EXCL, 0644, 1);     
	prod = sem_open("pSem", O_CREAT | O_EXCL, 0644, no_prod);
	//exits = sem_open("xSem", O_CREAT | O_EXCL, 0644, 0);

	//fork producers and consumers
	for (i=0; i<(no_prod+no_cons); i++)
	{
		pid = fork();
		if (pid < 0)
		{
			sem_unlink("eSem");
			sem_close(empty);
			sem_unlink("fSem");
			sem_close(full);
			sem_unlink("mSem");
			sem_close(mutex);
			sem_unlink("pSem");
			sem_close(prod);
			//sem_unlink("xSem");
			//sem_close(exits);
			printf("Error forking\n");

		}

		else if (pid == 0) break;
	}

	if (pid != 0)
	{
		while (pid = waitpid (-1, NULL, 0))
		{
            if (errno == ECHILD)
                break;
        }
		printf ("\nParent: All children have exited.\n");
		printf ("Total: %d\n ", buffer[0]);
    
		shmdt (buffer);
		shmctl (shmid, IPC_RMID, 0);

		printf ("Shared memory detached\n");

		sem_unlink("eSem");
		sem_close(empty);
		sem_unlink("fSem");
		sem_close(full);
		sem_unlink("mSem");
		sem_close(mutex);
		sem_unlink("pSem");
		sem_close(prod);
		//sem_unlink("xSem");
		//sem_close(exits);
		exit(0);
	}
	else
	{
		if (i < no_prod)
		{
			//spawn producer
			producer_main(&buffer, &empty, &full, &mutex, &prod);
		}
		else
		{
			//spawn consumer
			consumer_main(&buffer, &empty, &full, &mutex, &prod);
		}
		exit(0);
	}

	return 0;
}