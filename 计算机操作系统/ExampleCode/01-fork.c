/*************************************************************************
    > File Name: 01-fork.c
    > Author: Aerlany
    > Mail: 1243535201@qq.com
    > Created Time: Tue 15 Nov 2022 02:44:58 PM CST
 ************************************************************************/
#include <errno.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
int main(int argc, char *argv[]) {
  printf("HelloWorld\n");
  printf("This is Main Process ( %d )\n", getpid());
  if (fork() < 0) {
    printf("Process Create Failed!!\n");
    perror("Error occor");
  }
  printf("Put a word\n");
  printf("This Process Id %d\n", getpid());
}
