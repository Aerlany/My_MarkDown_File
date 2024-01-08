#include <asm-generic/socket.h>
#include <ctype.h>
#include <netinet/in.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>

// 打印宏
#define PRINTF(str) \
  printf("[%s -- %d] " #str ": %s \n", __func__, __LINE__, str);

// 文件存放路径
#define RESOURCE_PATH "/tmp/SunLight/HTML"

// 错误抛出
void error_exit(const char *str)
{
  perror(str);
  exit(EXIT_FAILURE);
}

// 实现网络的初始化
int startup(unsigned short *port)
{

  // 1.网络通信初始化
  // 2.创建套接字
  int server_socket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
  if (server_socket == -1)
  {
    error_exit("Create Socket");
  }

  // 3.设置端口复用
  int opt = 1;
  int ret = setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR,
                       (const char *)&opt, sizeof(opt));
  if (ret == -1)
  {
    error_exit("setsockopt");
  }

  // 4.绑定套接字
  // 配置服务器网络地址
  struct sockaddr_in server_addr;

  // 每个字节都用0填充
  memset(&server_addr, 0, sizeof(server_addr));
  server_addr.sin_family = PF_INET;
  server_addr.sin_port = htons(*port);
  // 接收所有请求
  server_addr.sin_addr.s_addr = INADDR_ANY;

  // 绑定Socket
  if (bind(server_socket, (struct sockaddr *)&server_addr,
           sizeof(server_addr)) < 0)
  {
    error_exit("bind");
  }

  // 动态分配一个端口
  int namelen = sizeof(server_addr);
  if (*port == 0)
  {
    if (getsockname(server_socket, (struct sockaddr *)&server_addr,
                    (socklen_t *)&namelen) < 0)
    {
      error_exit("getsockname");
    }

    *port = server_addr.sin_port;
  }

  // 5.创建监听队列
  if (listen(server_socket, SOMAXCONN) < 0)
  {
    error_exit("listen");
  }
  return server_socket;
}

// 读取浏览器请求中的一行
int get_line(int socket, char *buff, int size)
{
  char c = 0; // '\0'
  int i = 0;
  // \r\n区别
  //'\r'回车，回到当前行的行首，而不会换到下一行，如果接着输出的话，本行以前的内容会被逐一覆盖
  // '\n' 换行，换到当前位置的下一行，而不会回到行首

  // 经典算法
  while (i < size - 1 && c != '\n')
  {
    // recv function receive a message from a connected socket
    int n = recv(socket, &c, 1, 0);
    if (n > 0)
    {

      if (c == '\r')
      {
        n = recv(socket, &c, 1, MSG_PEEK);
        if (n > 0 && c == '\n')
        {
          recv(socket, &c, 1, 0);
        }
        else
        {
          c = '\n';
        }
      }
      buff[i++] = c;
    }
    else
    {
      c = '\n';
    }
  }
  buff[i] = 0;
  return i;
}

// 判断请求文件类型并匹配合适的响应文件格式
const char *getHeadType(const char *fileName)
{
  const char *ret = "text/html";
  const char *p = strrchr(fileName, '.');

  if (p == NULL)
  {
    return ret;
  }
  p++;
  if (!strcmp(p, "css"))
    ret = "text/css";
  else if (!strcmp(p, "jpg"))
    ret = "image/jpeg";
  else if (!strcmp(p, "png"))
    ret = "image/png";
  else if (!strcmp(p, "js"))
    ret = "text/javascript";

  return ret;
}

// 返回表头响应信息
void headers(int client, const char *file_type)
{
  char buff[1024];
  strcpy(buff, "HTTP/1.0 200 OK\r\n");
  send(client, buff, strlen(buff), 0);
  strcpy(buff, "Server: SunLightHttpServer/1.0\r\n");
  send(client, buff, strlen(buff), 0);

  strcpy(buff, "Content-type: ");
  strcat(buff, file_type);
  strcat(buff, "\r\n");
  send(client, buff, strlen(buff), 0);

  strcpy(buff, "\r\n");
  send(client, buff, strlen(buff), 0);
}

// 返回404界面
void not_found(int client)
{
  char buff[4096];
  FILE *resource = fopen("/tmp/SunLight/HTML/404.html", "r");

  headers(client, "text/html");
  while (1)
  {
    int ret = fread(buff, sizeof(char), sizeof(buff), resource);
    if (ret <= 0)
    {
      break;
    }
    send(client, buff, ret, 0);
  }
  return;
}

// 发送数据函数
void send_msg(int client, FILE *resource)
{
  char buff[4096];
  int count = 0;
  while (1)
  {
    int ret = fread(buff, sizeof(char), sizeof(buff), resource);
    if (ret <= 0)
    {
      break;
    }
    send(client, buff, ret, 0);
    count += ret;
  }
  printf("send [%d] bytes to client\n", count);
}

// 未实现界面
void unimplenment(int client);

// 静态资源发送
void server_file(int client, const char *path)
{
  char buff[1024];
  char cache[1024];
  int numchars = 1;
  char file_tyle[20];

  // 读取请求
  while (numchars > 0 && strcmp(buff, "\n"))
  {
    numchars = get_line(client, buff, sizeof(buff));
    PRINTF(buff);
  }

  // 发送资源
  // 打开文件
  FILE *resource;
  if (strstr(getHeadType(path), "text") != NULL)
  {
    resource = fopen(path, "r");
    printf("file is opened with r mode\n");
  }
  else
  {
    resource = fopen(path, "rb");
    printf("file is opened with rb mode\n");
  }
  if (resource == NULL)
  {
    // 404
    not_found(client);
  }
  else
  {
    // 发送header
    headers(client, getHeadType(path));
    // 发送请求资源
    send_msg(client, resource);
  }
  fclose(resource);
}

// 线程函数用于处理用户请求
void *accept_request(void *arg)
{
  char buff[1024]; // 1k
  int client = *(int *)arg;
  int numchars;

  get_line(client, buff, sizeof(buff));
  PRINTF(buff);

  int i, j = 0;
  char method[512];
  // 匹配请求方式
  while (!isspace(buff[i]) && j < sizeof(method) - 1)
  {
    method[j++] = buff[i++];
  }
  PRINTF(method);
  // 跳过与路径间的空格
  while (isspace(buff[i]) && i < sizeof(buff) - 1)
  {
    i++;
  }
  // 匹配请求路径
  char url[512];
  j = 0;
  while (!isspace(buff[i]) && j < sizeof(url) - 1)
  {
    url[j++] = buff[i++];
  }
  PRINTF(url);

  // 资源存放路径
  char path[512];
  strcat(path, RESOURCE_PATH);
  if (strcmp(url, "/") == 0)
  {
    strcat(path, "/index.html");
  }
  else
  {
    strcat(path, url);
  }
  PRINTF(path);

  // 排除路径类型是目录
  struct stat state;
  // 文件状态不存在
  if (stat(path, &state) == -1)
  {
    // 读取文件完毕
    while (numchars > 0 && strcmp(buff, "\n"))
    {
      numchars = get_line(client, buff, sizeof(buff));
    }

    // 404
    not_found(client);
  }
  else
  {
    // 文件类型是dir
    if ((state.st_mode & S_IFMT) == S_IFDIR)
    {
      // strcat(path, "/index.html");
      not_found(client);
    }
    else
    {
      // 发送资源
      server_file(client, path);
    }
  }

  shutdown(client, SHUT_RDWR);
  return NULL;
}

int main(int argc, char *argv[])
{

  unsigned short port = 8090;
  // 创建套接字
  int server_socket = startup(&port);
  printf("HTTP Server Started, listening Port %d \n", port);

  // 客户端链接
  struct sockaddr_in client_addr;
  int client_addr_len = sizeof(client_addr);

  while (1)
  {
    // 阻塞式等待用户通过浏览器发起访问
    int client_socket = accept(server_socket, (struct sockaddr *)&client_addr,
                               (socklen_t *)&client_addr_len);
    if (client_socket == -1)
    {
      error_exit("client_socket");
    }

    // 使用client_socket对用户进行访问
    // 使用多线程进行多用户交互
    pthread_t t;
    if (pthread_create(&t, NULL, accept_request, (void *)&client_socket) != 0)
    {
    }
  }

  return 0;
}
