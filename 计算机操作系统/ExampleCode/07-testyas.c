#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#define NUMBER_OF_THREADS 5
void *hello(void *tid) {
  printf("Hello from thread %d\n", *(int *)tid);
  pthread_exit(NULL);
}
int main(void) {
  pthread_t t[NUMBER_OF_THREADS];
  int status, i;
  for (i = 0; i < NUMBER_OF_THREADS; i++) {
    printf("Main: creating thread %d ...", i);
    if ((status = pthread_create(&t[i], NULL, hello, (void *)&i))) {
    }
    puts("done.");
  }
  for (i = 0; i < NUMBER_OF_THREADS; i++) {
    printf("Joining thread %d ...", i);
    if (pthread_join(t[i], NULL)) {
    }
    puts("done.");
  }
  exit(0);
}
