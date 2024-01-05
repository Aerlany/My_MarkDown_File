/*************************************************************************
    > File Name: 02-write.c
    > Author: Aerlany
    > Mail: 1243535201@qq.com
    > Created Time: Tue 15 Nov 2022 05:12:00 PM CST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main(int argc, char *argv[]) {
  write(1, "HelloWorld\n", 14);
  return EXIT_SUCCESS;
}
