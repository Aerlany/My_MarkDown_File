#include <fcntl.h>
#include <limits.h>
#include <mqueue.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
int main(int argc, char *argv[]) {

  mqd_t queue;
  struct mq_attr attrs;
  size_t msg_len;

  if (argc < 3) {
    puts("param ERROR");
  }

  /*queue = mq_open(argv[1], O_RDONLY | O_CREAT, S_IRUSR | S_IWUSR, NULL);*/
  queue = mq_open(argv[1], O_RDONLY);

  if (queue == (mqd_t)-1) {
    puts("Open Error");
  }

  if (mq_getattr(queue, &attrs) == -1) {
    puts("get Error");
  }
  msg_len = strlen(argv[2]);

  if (msg_len > LONG_MAX || (long)msg_len > attrs.mq_msgsize) {
    puts("ERROR3");
  }

  if (mq_send(queue, argv[2], msg_len, 0) == -1) {
    puts("Message send failed");
  }

  return 0;
}
