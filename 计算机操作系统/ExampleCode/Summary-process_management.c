#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <wait.h>
int main(int argc, char *argv[]) {
  pid_t child_pid;
  printf("This is main process ( %d )\n", getpid());

  // fork() 创建一个子进程，运行语句往下的语句
  child_pid = fork();
  printf("fork() return in parent process ( %d )\n", child_pid);
  // fork() 在父进程中的返回值为 创建的子进程的pid
  // 但在 子进程中的返回值为 0 | 1

  // 只有子进程调用
  if (child_pid == 0) {
    printf("fork() return in child process ( %d )\n", child_pid);
    printf("This is child process ( %d )\n", getpid());
    // 运行一个命令或脚本来代替子进程
    /*execl("/bin/ls", "ls", "-la", NULL);*/

    int count = 1;
    while (1) {
      sleep(1);
      printf("The child process sleep %d s...\n", count);
      count++;
      if (count > 10) {
        // exit(int status) 用于退出调用的进程
        exit(EXIT_FAILURE);
      }
    }

  }
  // 只有父进程调用
  else {
    // 用于储存子进程退出状态
    int status;
    // 父进程等待子进程结束
    pid_t waitpid_return = waitpid(child_pid, &status, 0);
    printf("The child process exit with status %d\n", status);
    // 函数返回值为 子进程id
    printf("waitpid() return %d\n", waitpid_return);
  }
}
