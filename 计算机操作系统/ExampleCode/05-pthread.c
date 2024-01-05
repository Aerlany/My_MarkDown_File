#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void *hello(void *arg) {
  for (int i = 0; i < 20; i++) {
    puts("Thread say Hello");

    sleep(1);
  }
  return NULL;
}

int main(void) {
  pthread_t t;

  if (pthread_create(&t, NULL, hello, NULL)) {
  }

  if (pthread_join(t, NULL)) {
  }
  exit(EXIT_SUCCESS);
}
