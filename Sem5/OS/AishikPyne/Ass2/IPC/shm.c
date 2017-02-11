#include <stdio.h>
#include <sys/shm.h>
#include <sys/stat.h>
int main ()
{
    int segment_id;
    char* shared_memory;
    struct shmid_ds shmbuffer;
    int segment_size;
    const int shared_segment_size = 0x6400; // 0x6400 is in binary which converts to 25600 bytes

    /* Allocate the shared memory segment */
    segment_id = shmget(IPC_PRIVATE, shared_segment_size, IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR);
    printf("New Allocated Memory: segment_id = %d\n", segment_id);



    /* Attach the shared memory segment. */
    shared_memory = (char*) shmat (segment_id, NULL, 0);
    printf("shared memory attached at address %p\n", shared_memory);


    /* Determine the segment’s size. */
    shmctl (segment_id, IPC_STAT, &shmbuffer);
    segment_size = shmbuffer.shm_segsz;
    printf ("segment size: %d\n", segment_size);
    /* Write a string to the shared memory segment. */
    sprintf (shared_memory, "Hello, world!.");

    /* Reattach the shared memory segment, at a different address. */
    shared_memory = (char*) shmat (segment_id, NULL, 0);
    printf ("shared memory reattached at address %p\n", shared_memory);
    /* Print out the string from shared memory. */
    printf ("%s\n", shared_memory);


    /* Detach the shared memory segment. */
    shmdt (shared_memory);


    /* Deallocate the shared memory segment */
    shmctl (segment_id, IPC_RMID, 0);

}
