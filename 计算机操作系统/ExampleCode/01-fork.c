/*************************************************************************
    > File Name: 01-fork.c
    > Author: Aerlany
    > Mail: 1243535201@qq.com
    > Created Time: Tue 15 Nov 2022 02:44:58 PM CST
 ************************************************************************/

#include <stdio.h>
#include <unistd.h>
int main(int argc, char *argv[]) {
  printf("HelloWorld\n");
  fork();
  printf("Put a word\n");
}
