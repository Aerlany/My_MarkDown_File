#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
int main(int argc, char *argv[]) {
  pid_t pid;
  pid = fork();
  if (pid < 0) {
    fprintf(stderr, "Fork failed");
    exit(EXIT_FAILURE);
  } else if (pid == 0) {
    sleep(10);
    execl("/bin/ls", "ls", "-la", NULL);
  } else {
    waitpid(pid, NULL, 0);
    puts("Child Complete");
    exit(EXIT_SUCCESS);
  }
  return 0;
}
