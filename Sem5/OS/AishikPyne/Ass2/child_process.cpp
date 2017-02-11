#include <iostream>
#include <stdlib.h>
#include <cstdlib>
#include <pthread.h>
#include <unistd.h>
using namespace std;

#define NUM_THREADS 2

void *PrintHello(void *threadid) {
   long tid;
   tid = (long)threadid;
   for(int iter =0;iter<10;iter++){
      cout << "Thread ID, " << tid << " Iteration: " << iter << endl;
      int sleep_time = rand() % 10 + 1;
      sleep(sleep_time);
   }
   pthread_exit(NULL);
}

int main () {
   pthread_t threads[NUM_THREADS];
   int rc;
   int i;

   for( i = 0; i < NUM_THREADS; i++ ) {
      cout << "main() : creating thread, " << i << endl;
      rc = pthread_create(&threads[i], NULL, PrintHello, (void *)i);

      if (rc) {
         cout << "Error:unable to create thread," << rc << endl;
         exit(-1);
      }
   }
   pthread_exit(NULL);
}
