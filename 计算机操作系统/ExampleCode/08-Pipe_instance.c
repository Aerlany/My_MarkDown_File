#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define BUF_SIZE 10

int main(int argc, char *argv[]) {
  int pfd[2]; /*Pipe file descriptors*/
  char buf[BUF_SIZE];
  ssize_t numRead;

  // Create the pipe
  pipe(pfd);

  switch (fork()) {
  case 0:          /*Child - read from pipe*/
    close(pfd[1]); /*write end is unused*/

    for (;;) { /* Read data from pipe and echo on stdout  */
      if ((numRead = read(pfd[0], buf, BUF_SIZE)) == 0) {
        break;
      }
      if (write(1, buf, numRead)) {
      }
      puts("");

      close(pfd[0]);
      _exit(EXIT_SUCCESS);
    }

  default:
    /* parent - write to pipe  */
    close(pfd[0]); /*read end is unused*/

    if (write(pfd[1], argv[1], strlen(argv[1])) != strlen(argv[1])) {
      puts("Error");
    }

    close(pfd[1]);

    wait(NULL); /* wait for Child finish */
    exit(EXIT_SUCCESS);
  }
}
