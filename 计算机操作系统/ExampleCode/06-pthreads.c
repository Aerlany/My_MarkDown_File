#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NUMBER_OF_PTHREAD 5

void *Hello(void *arg) {

  /*NOTE: 指针类型的转换不能如此使用*/
  /*printf("Tread %d saying Hello !!", (int)*arg);*/

  printf("Tread %d saying Hello !!\n", *(int *)arg);
  pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
  pthread_t t[NUMBER_OF_PTHREAD];

  int i;

  for (i = 0; i < NUMBER_OF_PTHREAD; i++) {
    printf("Main: Creating a now thread %d ...", i);

    if (pthread_create(&t[i], NULL, Hello, (void *)&i)) {
      printf("Error\n");
    }

    puts("Done!\n");
  }
  for (i = 0; i < NUMBER_OF_PTHREAD; i++) {
    printf("Joining thread %d ...", i);

    if (pthread_join(t[i], NULL)) {
      printf("Error\n");
    }

    puts("Done\n");
  }

  exit(EXIT_SUCCESS);
}
