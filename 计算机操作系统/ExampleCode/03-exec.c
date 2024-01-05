/*************************************************************************
    > File Name: 03-exec.c
    > Author: Aerlany
    > Mail: 1243535201@qq.com
    > Created Time: Tue 15 Nov 2022 05:38:44 PM CST
 ************************************************************************/

#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
  printf("Main Process ( %d ) saying Hello!\n", getpid());

  int a = fork();
  printf("fork() return in the Parent : %d\n", a);
  if (a == 0)
  {
    printf("fork() return in the Child : %d\n", a);
    printf("Child Process ( %d ) listing the source file...\n", getpid());

    execl("/bin/ls", "", NULL);

    /*execl()函数只有出错时有返回值*/
    puts("You can't see this unless execl() failed");
  }
  else
  {
    int i = 60;
    printf("Parent Process ( %d ) is sleeping for %d seconds\n", getpid(), i);
    printf("\n");
    sleep(i);
  }

  printf("Hello again from Process %d\n", getpid());

  return 0;
}
