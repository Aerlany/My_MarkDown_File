#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#define BUF_SIZE 10

int main(int argc, char *argv[]) {
  int pfd[2];
  char buf[BUF_SIZE];
  ssize_t numRead;

  pipe(pfd); // 创建 pipe进程
  switch (fork()) {
  case 0: // Child-read from pipe
    close(pfd[1]);
    for (;;) {
      if ((numRead = read(pfd[0], buf, BUF_SIZE) == 0))
        break;
      if (write(1, buf, numRead) != numRead) {
      }
    }
    puts("");

    close(pfd[0]);
    exit(EXIT_SUCCESS);

  default:
    close(pfd[0]); /* Read end is unused */
    if ((size_t)write(pfd[1], argv[1], strlen(argv[1])) != strlen(argv[1])) {
    }
    close(pfd[1]); /* Child will see EOF */
    wait(NULL);    /* Wait for child to finish */
    exit(EXIT_SUCCESS);
  }
}
