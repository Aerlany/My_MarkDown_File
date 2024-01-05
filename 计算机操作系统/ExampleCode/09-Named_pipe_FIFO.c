#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define FIFO_NAME "/tmp/myfifo"

int main(int argc, char *argv[]) {
  int fd, i, mode = 0;
  char c;

  if (argc < 2) {
    puts("Error");
    exit(EXIT_FAILURE);
  }

  /*检测携带参数选择模式*/
  for (i = 1; i < argc; i++) {
    if (strncmp(*++argv, "O_RDONLY", 8) == 0)
      mode |= O_RDONLY;
    if (strncmp(*argv, "O_WRONLY", 8) == 0)
      mode |= O_WRONLY;
    if (strncmp(*argv, "O_NONBLOCK", 10) == 0)
      mode |= O_NONBLOCK;
  }

  /*判断FIFO文件是否存在*/
  if (access(FIFO_NAME, F_OK) == -1) {
    puts("myfifo be created");
    mkfifo(FIFO_NAME, 0777);
  }

  printf("Process %d : FIFO( fd %d, mode %d) opened. \n", getpid(),
         fd = open(FIFO_NAME, mode), mode);

  if ((mode == 0) | (mode == 2048))
    while (read(fd, &c, 1) == 1)
      putchar(c); /*通过read函数逐字读取打印*/
  if ((mode == 1) | (mode == 2049))
    while ((c = getchar()) != EOF)
      write(fd, &c, 1); /*获取屏幕输入写入到FIFO文件中*/
  exit(EXIT_SUCCESS);
}
