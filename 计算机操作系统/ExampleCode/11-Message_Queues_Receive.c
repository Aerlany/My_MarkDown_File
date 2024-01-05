#include <fcntl.h>
#include <mqueue.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
int main(int argc, char *argv[]) {
  mqd_t queue;
  struct mq_attr attrs;
  char *msg_ptr;
  ssize_t recvd;
  size_t i;

  if (argc < 2) {
    puts("ERROR");
  }

  queue = mq_open(argv[1], O_RDONLY | O_CREAT, S_IRUSR | S_IWUSR, NULL);

  if (queue == (mqd_t)-1) {
    puts("Creat Error");
  }

  if (mq_getattr(queue, &attrs) == -1) {
    puts("Getattr Error");
  }

  msg_ptr = calloc(1, attrs.mq_msgsize);
  if (msg_ptr == NULL) {
    puts("msg_ptr is NULL");
  }

  recvd = mq_receive(queue, msg_ptr, attrs.mq_msgsize, NULL);

  if (recvd == -1) {
    puts("recvd is NULL");
  }
  printf("Message: ");
  for (i = 0; i < (ssize_t)recvd; i++) {
    putchar(msg_ptr[i]);
  }
  puts("");
}
