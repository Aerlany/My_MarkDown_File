# An excellent c Web programming project borrows from TinyHttp



## Create a server-side socket

Network-based communication requires the creation of a "Socket" first.

**tip**: The Socket is equivalent to a "network socket", and communication through the network is to send and receive information through this "socket", which is equivalent to the telephone line slot of a telepone.

****

**But How to create a socket?**

**1. Socket() function under Linux**

```c
#include<sys/socket.h>

int socket(int domain, int type, int protocol);
```

-  **domain** ( Specifies the communications domain in which a socket is to be created ), commonly used are `AF_INET` and `AF_INET6`, `AF_INET` represents an `IPv4` address, such as `127.0.0.1`, `AF_INET6` represents an `IPv6` address, such as  `1030::C9B4:FF12:48AA:1A2B`

-  **type** ( Specifies the type of socket to be created ), commonly used are `SOCK_STREAM ` and `SOCK_DGRAM` 

-  **protocol**  ( Specifies a particular protocol to be used with the socket ), commonly used are `IPPROTO_TCP` and `IPPTOTO_UDP`, respectively/separately represents `TCP` and `UDP` transport protocol

```c
int startup(unsigned short *port){
    //create socket
    int server_socket = socket(PF_INET, SOCK_STREAM, 0);
    
}
```

