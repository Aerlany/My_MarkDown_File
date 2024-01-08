# Operating System



# Part 1. What’s an Operating System

## Definition

**What’s an Operating System?**

1. It's the program that runs all the time.
2. It's a **resource manager** 

   *Each program gets time or space with/ on the resource*
3. It's a **control program**

   *Control execution of  program to prevent error and improper use of the computer*
4. No universally accepted definition.

------

**Multi-programming is the first instance where the OS must make decisions for the users**

1. **Job scheduling** — decides which job should be loaded into the memory.
2. **Memory management** — because several programs in memory at the same time
3. **CPU scheduling** — choose one job among all the jobs are ready to run
4. **Process management** — make sure processes don’t offend each other



**NOTE**

**操作系统**（英语：**O**perating **S**ystem，缩写：**OS**）是指控制和管理整个计算机系统的硬件（Memory）和软件资源（Process），并合理地组织调度计算机的工作（Job Scheduling）和资源（CPU）的分配的[系统软件](https://zh.wikipedia.org/wiki/系统软件)[程序](https://zh.wikipedia.org/wiki/程序)，以提供给用户和其他软件方便的接口和环境。



## OS Services

**Helping the users:**

| 功能                     | 描述         |
| ------------------------ | ------------ |
| User interface           | 用户界面     |
| File system manipulation | 文件系统操作 |
| Program execution        | 程序运行     |
| Communication            | 交流         |
| I/O operation            | I/O控制      |
| Error detection          | 错误检测     |

**Keeping the system efficient:**

| 功能                    | 描述       |
| ----------------------- | ---------- |
| Resource allocation     | 资源分配   |
| Accounting              | 账户分户   |
| Protection and security | 保护和安全 |



-----

## Hardware

### **CPU Working Cycle** 

**(CPU工作流程)**

![image-20240108102140128](https://github.com/Aerlany/Images-of-mine/raw/main/PicGo/image-20240108102140128.png)

1. **Fetch** the first instruction from memory 	***从内存中取出操作码***
2. **Decode** it to determine its type and operands  ***解码来决定其类型和操作码***
3. **Execute** it



**Special CPU Registers** (寄存器)

1. **Program counter (PC) *程序计数器***: 

   ​	keeps the memory address of the next instruction to be fetched

   ​	*保存下一条要取的指令的内存地址*

2. **Stack pointer (SP) *堆栈指针***: 

   ​	point to the top of the current stack in memory

   ​	*指向内存中当前堆栈的顶部*

3. **Program status (PS)**: 

   ​	holds condition code bits and processor state 

   ​	*存储条件代码位和处理器状态*



------

### **System Bus**

**(系统总线)**

![image-20240108103238116](https://github.com/Aerlany/Images-of-mine/raw/main/PicGo/image-20240108103238116.png)

1. **Address Bus**: 

   ​	specifies  the memory locations (addresses) for the data transfers

   ​	*指定数据传输的内存地址*
2. **Data Bus**: holds the data transfered. Bidirectional

   ​	*保持数据双向传输*
3. **Control Bus**: 

   ​	contains various lines used to route timing and control signals throughout the system

​			*包含用于在整个系统中路由定时和控制信号的各种线路*



------

### **Controllers and Peripherals** 

**(控制器和外设)**

1. Peripherals are real devices controlled by controller chips
2. Controllers are processors like the CPU itself, have control registers
3. Device driver writes to the registers, thus control it
4. Controllers are connected to the CPU and to each other by a variety of buses 

**Translate**

1. 外设是由控制器芯片控制的真实设备

2. 控制器是像CPU本身一样的处理器，具有控制寄存器

3. 设备驱动程序写入寄存器，从而控制它

4. 控制器通过各种总线连接到CPU和彼此之间

   

------

### **Motherboard Chipsets** 

**(主板芯片组)**

![image-20221114213713317](https://github.com/Aerlany/Images-of-mine/raw/main/PicGo/image-20221114213713317.png)

------

**The northbridge**

1. receives a physical memory request
2. decides where to route it to RAM?  to video card? to ...?  **decision made via the memory address map**



**NOTE**

-  The CPU doesn’t know what it’s connected to
- The CPU talks to the outside world through its **pins**, some pins to transmit the **physical memory** address, other pins to transmit the **values**
- The CPU’s gateway to the world is the **front-side bus**



**Intel Core 2 QX6600** 

1. **33 pins** to transmit the physical memory address (**so there are 2^33 choices of memory locations**)
2. **64 pins** to send or receive data (**so data path is 64-bit wide, or 8-byte chunks**)
3. This allows the CPU to physically address 64 GiB of memory (2^33 × 8 B)



**Some physical memory addresses are mapped away!**



-----

## Bootstrapping

**A computer cannot run without first loading software but must be running before any software can be loaded.**

------

**Intel x86 Bootstrapping**

**1. BIOS (0xfffffff0)**

- POST ( Power-On-Self-Test )
- HardWare Init
- Find a boot device (FD, CD, HD...)
- Copy **sector zero**(MBR) to RAM (0x00007c00)



**2. MBR – the first 512 bytes, contains**:

- Small code (⩽ 446 Bytes)  e.g. **GRUB stage 1, for loading GRUB stage 2**
- the primary partition table (16 × 4 = 64 Bytes)
- **Its job is to load the 2nd stage boot loader.**



**3. GRUB stage 2 — load the OS kernel into RAM**

   ( GRand Unified Bootloader )



**4. StartUp**

**5. init — the first user-space program** (systemd)



------

## Interrupt

**Modern OS are Interrupt Driven**

1. **Hardware INT**（硬件中断）

   by send a signal to CPU 
2. **Software INT **（软件中断）

   by executing a **System Call**
3. **Trap (exception)** （异常捕获）

    a software-generated INT coursed by an error or by a specific
   request from an user program
4. **Interrupt vector**（中断向量）

   an array of pointers ☛ the memory addresses of interrupt handlers.
   This array is indexed by a unique device number

```sh
$ less /proc/devices
$ less /proc/interrupts
```

**Programmable Interrupt Controllers**

![image-20240108111832082](https://github.com/Aerlany/Images-of-mine/raw/main/PicGo/image-20240108111832082.png)

-----

## System Calls

A System Call i**s how a program requests a service from an OS kernel** and **provides the interface between a process and the OS**

*系统调用是指程序如何向操作系统内核请求服务，而内核提供进程和操作系统之间的接口*

```sh
$ man 2 intro
$ man 2 syscalls
```

![How a system call be made](https://github.com/Aerlany/Images-of-mine/raw/main/PicGo/image-20221115155055411.png)

**How a system call can be made**:

(1) User program traps to the kernel. 

(2) Operating system determines service number required.

(3) Operating system calls service procedure. 

(4) Control is returned to user program.



### **Example**

**Interrupt Vector Table** (**The very first 1 KiB of x86 memory**)

1. 256 entries × 4 B = 1 KiB
2. Each entry is a complete memory address (每一个条目都是一个完整的内存地址)
3. It’s populated by Linux and BIOS
4. Slot 80h: address of the kernel services dispatcher (☛ sys-call table) (内核服务派遣器的地址)



**System Call ( write )**

**pwrite, write — write on a file**

```c
$man 2 write
 
#include <unistd.h>
ssize_t pwrite(int fildes, const void *buf, size_t nbyte,off_t offset);
ssize_t write(int fildes, const void *buf, size_t nbyte);
```

```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main(int argc, char *argv[]) {
  write(1, "HelloWorld\n", 14);
  return EXIT_SUCCESS;
}
```



**System call (fork)**

**fork - create a child process**

```c
$man 2 fork

#include <sys/types.h>
#include <unistd.h>

pid_t fork(void);

```

*fork()  creates  a  new  process  by  duplicating the calling process.  The new process is referred to as the child process.  The calling  process  is  referred  to  as  the  parent process.*

```c
#include <stdio.h>
#include <unistd.h>
int main(int argc, char *argv[]) {
  printf("HelloWorld\n");
  fork();
  printf("Put a word\n");
}
```

```c
HelloWorld
Put a word
Put a word
```



**System call (exec)**

*The  exec()  family  of  functions  replaces  the current process image with a new process image.*  

```c
$man 3 exec

NAME
       execl, execlp, execle, execv, execvp, execvpe - execute a file

SYNOPSIS
       #include <unistd.h>

       extern char **environ;

       int execl(const char *path, const char *arg, ...
                       /* (char  *) NULL */);
       int execlp(const char *file, const char *arg, ...
                       /* (char  *) NULL */);
       int execle(const char *path, const char *arg, ...
                       /*, (char *) NULL, char * const envp[] */);
       int execv(const char *path, char *const argv[]);
       int execvp(const char *file, char *const argv[]);
       int execvpe(const char *file, char *const argv[],
                       char *const envp[]);

```

*Create a child process that does different things than the parent process*

```c
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  printf("Main Process ( %d ) saying Hello!\n", getpid());

  int a = fork();
  printf("fork() return in the Parent : %d\n", a);
  if (a == 0) {
    printf("fork() return in the Child : %d\n", a);
    printf("Child Process ( %d ) listing the source file...\n", getpid());

    execl("/bin/ls", "", NULL);

    /*execl()函数只有出错时有返回值*/
    puts("You can't see this unless execl() failed");
  } else {
    int i = 60;
    printf("Parent Process ( %d ) is sleeping for %d seconds\n", getpid(), i);
    printf("\n");
    sleep(i);
  }

  printf("Hello again from Process %d\n", getpid());

  return 0;
}

```

```sh
Main Process ( 265161 ) saying Hello!
Parent : 265162
Parent Process ( 265161 ) is sleeping for 60 seconds

Parent : 0
Child : 0
Child Process ( 265162 ) listing the source file...
01-fork.c  02-write.c  03-exec.c  a.out  FIFO_Example.c  pipe_Example.c  test.c
Hello again from Process 265161
```

*From this example, the order in which the fork() is run can be derived*

**Don’t invoke System call directly whenever possible !!!**



### **Hardware INT vs. Software INT**

![HW INT and SW INT](https://github.com/Aerlany/Images-of-mine/raw/main/PicGo/image-20221115222730359.png)



# Part 2. Process And Thread

## Processes

**Definition:** ***A process is an instance of a program in execution***  **(定义)**



Processes are like human being, they **are generated**, they are **have a lift**, they optionally generate one or more **child processes**, and eventually they **die**. But a small difference, sex is not common among processes, and each process has **just one parent**.

*There are two categories of processes in Unix, namely*

- **User processes**: They are operated in user mode.
- **Kernel processes**: They are operated in kernel mode.



**Process Control Block (PCB) (进程控制模块)**

**Implementation:**

1. *A process is the **collection of data structures** that fully describes how far the execution of the program has progressed.*

2. **Each Process is represented by a PCB** 

3. A PCB include : **process state, PID, program counter, registers, memory limits, list of open files.....**



**Process Creation** **(进程创建)**

![A Process Creation](https://github.com/Aerlany/Images-of-mine/raw/main/PicGo/image-20221116105610135.png)

**Attention:**

1. *When a process is created, it is almost identical ( 相同 )to its parent, It **receives a (logical) copy of** the parent’s address space, and **executes the same code** as the parent*

2. *The parent and child have **separate** ( 分开的,单独的 ) copies of the data (stack and heap)*



**Example**

1. fork() in c

```c
#include <stdio.h>
#include <unistd.h>
int main(int argc, char *argv[]) {
  printf("HelloWorld\n");
  fork();
  printf("Put a word\n");
}
```

```sh
HelloWorld
Put a word
Put a word
```

2. exec()

```c
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
    execlp("/bin/ls", "ls", NULL);
  } else {
    wait(NULL);
    puts("Child Complete");
    exit(EXIT_SUCCESS);
  }
  return 0;
}
```

```sh
01-fork.c  02-write.c  03-exec.c  04-exec.c  a.out  FIFO_Example.c  pipe_Example.c  test.c
Child Complete
```



**Process State Transition**



![image-20221116194207048](https://github.com/Aerlany/Images-of-mine/raw/main/PicGo/image-20221116194207048.png)

- **Ready:** The Process already has an execution condition, but does not get CPU and cannot be executed.
- **Running:** The Process has taken over the CPU, and is running at this time.
- **Blocked:** The state of a Process while waiting for a service, signal, external operation, etc.





**CPU Switch From Process To Process**

![image-20221118220923175](https://github.com/Aerlany/Images-of-mine/raw/main/PicGo/image-20221118220923175.png)



## Threads

### **Processes vs. Threads**

- **A process = a unit of resource ownership, used to group resources together**

  **A thread = a unit of scheduling, scheduled for execution on the CPU**



- **Multiple threads running in one process** (*share an address space and other resource*)

  **Multiple process running in one computer** (*share physical memory, disk, printers*)



- **No protection between threads**

  *Impossible* -- because process is the minimum unit of resource management

  *unnecessary* -- a process owned by a single



**Why Tread?**

- **Responsiveness**

  Good for **interactive** applications.

  A process with **multiple** threads make great server (e.g. a web server) 

  ( Have one server process, many "Worker" threads -- *if one thread blocks, others can still continue executing* )



- **Economy** -- Thread are cheap!

​		**Cheap to create** -- only need a stack and storage for registers

​		**Use very little resource** -- don't need new address space, global data, program code, or OS resource

​		**Switches are fast** -- only have to save/restore PC, SP, and registers

​		**Resource sharing** -- Threads can pass data via shared memory; no need for **IPC**

​		**Can take advantage of multiprocess**



​	**NOTE**

​	**进程间通信（IPC，InterProcess Communication）**是指在不同进程之间传播或交换信息。



**Thread Characteristics** (线程特性)

- **Thread States Transition**

​		*Same as process states transition*



- **Each Thread Has Its Own Stack**

​		A typical stack stores local data and call information for (usually nested) procedure calls.

​		Each thread generally has a different execution history.



### **POSIX Threads**

​	**IEEE: **The standard for writing **portable** threaded programs. The threads package it defines is called 	**Pthreads**, including over 60 function calls, supported by most UNIX systems.



​	**NOTE**

​	**POSIX**：可移植操作系统接口（Portable Operating System Interface of UNIX，缩写为 POSIX ）



![image-20221121163919209](https://github.com/Aerlany/Images-of-mine/raw/main/PicGo/image-20221121163919209.png)



**Pthreads**

​	***How to use pthread?***

```sh
#include<pthread.h>

$ gcc thread1.c -o thread1 -pthread
$ ./thread1
```

​	**Example**

```c
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void *hello(void *arg) {
  for (int i = 0; i < 20; i++) {
    puts("Thread say Hello");

    sleep(1);
  }
  return NULL;
}

int main(void) {
  pthread_t t;

  if (pthread_create(&t, NULL, hello, NULL)) {
  }

  if (pthread_join(t, NULL)) {
  }
  exit(EXIT_SUCCESS);
}
```

```c
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NUMBER_OF_PTHREAD 5

void *Hello(void *arg) {

  /*NOTE: 指针类型的转换不能如此使用*/
  /*printf("Tread %d saying Hello !!", (int)*arg);*/

  printf("Tread %d saying Hello !!\n", *(int *)arg);
  pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
  pthread_t t[NUMBER_OF_PTHREAD];

  int i;

  for (i = 0; i < NUMBER_OF_PTHREAD; i++) {
    printf("Main: Creating a now thread %d ...", i);

    if (pthread_create(&t[i], NULL, Hello, (void *)&i)) {
      printf("Error\n");
    }

    puts("Done!\n");
  }
  for (i = 0; i < NUMBER_OF_PTHREAD; i++) {
    printf("Joining thread %d ...", i);

    if (pthread_join(t[i], NULL)) {
      printf("Error\n");
    }

    puts("Done\n");
  }

  exit(EXIT_SUCCESS);
}
```



### **User-Level Threads vs. Kernel-level Threads**

|                   | User-Level Threads                                           | Kernel-level Threads                                     |
| ----------------- | ------------------------------------------------------------ | -------------------------------------------------------- |
| **Advantages**    | Simple **representation**                                    | **Kernel has full knowledge of all threads**             |
|                   | Simple **Management**                                        | **Good for applications that frequently block**          |
|                   | **Fast**                                                     |                                                          |
|                   | **Flexible**                                                 |                                                          |
|                   |                                                              |                                                          |
| **Disadvantages** | **Lack of coordination (配合) between threads and OS kernel** | **Significant overhead and increased kernel complexity** |
|                   | **Requires non-blocking system calls**                       | **Slow**                                                 |
|                   | **If one thread causes a page fault (interrupt!), the entire process blocks** |                                                          |

**User-level threads** *provide a library of functions to allow user processes to create and manage their own threads.*

​	**Advantages**

- No need to modify the OS

- Simple **representation**

  *each thread is represented simply by a PC, regs, stack, and a small TCB, all stored in the user process’ address space*

- Simple **Management**

  *creating a new thread, switching between threads, and synchronization between threads can all be done without intervention of the kernel*

- **Fast**

  *thread switching is not much more expensive than a procedure call*

- **Flexible**

  *CPU scheduling (among threads) can be customized to suit the needs of the algorithm --each process can use a different thread scheduling algorithm*

​	

​	**Disadvantages**

- **Lack of coordination (配合) between threads and OS kernel**

  *Process as a whole gets one time slice*

  *Same time slice, whether process has 1 or 1000 tread*

  *Also, up to each thread to **relinquish** control to other threads in that process*

- **Requires non-blocking system calls**

  *Otherwise, entire process will blocked in the kernel, even if there are runnable threads
  left in the process*

​		*part of motivation for user-level threads was not to have to modify the OS*

- **If one thread causes a page fault (interrupt!), the entire process blocks**



**Kernel-Level Threads** *kernel provides system calls to create and manage threads*

​	**Advantages**

- **Kernel has full knowledge of all threads**

  *Scheduler may choose to give a process with 10 threads more time than process with
  only 1 thread*

- **Good for applications that frequently block**

  

​	**Disadvantages**

- **Slow**

  *Thread operations are 100s of times slower than for user-level threads*

- **Significant overhead and increased kernel complexity** 

  *Kernel must manage and schedule threads as well as processes*

  *Requires a full thread control block (TCB) for each thread*



### Hybrid Implementations

**Combine the advantages of two**

![image-20221121214729515](https://github.com/Aerlany/Images-of-mine/raw/main/PicGo/image-20221121214729515.png)

### Programming Complications

1. **fork(): shall the child has the threads that its parent has?**
2. **What happens if one thread closes a file while another is still reading from it?**
3. **What happens if several threads notice that there is too little memory?**

***Sometimes, threads fix the symptom, but not the problem.*** (有时,线程可以修复症状,但不能解决问题。)



## Process Synchronization

### IPC (Interprocess Communication)

**IPC issues**

1. How one process can pass information to another (进程间怎样传递信息)
2. Be sure processes do not get into each other’s way (确保进程间不要相互踩踏/阻塞)
3. Proper sequencing when dependencies are present (存在依赖关系时的正确排序)



**Two models of IPC**

1. Shared memory
2. Message passing (e.g. sockets)

 

### Shared Memory

***Consumers don’t try to remove objects from Buffer when it is empty***

***Producers don’t try to add objects to the Buffer when it is full***

![image-20221122205131028](/home/user/.config/Typora/typora-user-images/image-20221122205131028.png)



**Circular Array**  (循环数组)

**Bounded-Buffer Problem**

![image-20221122205224274](https://github.com/Aerlany/Images-of-mine/raw/main/PicGo/image-20221122205224274.png)

![image-20221122205746278](/home/user/.config/Typora/typora-user-images/image-20221122205746278.png)



**Pipe**

```c
ls | wc -l
```

- A pipe is a byte stream
- **Unidirectional**
- **read()** would be blocked if nothing written at the other end

![image-20221122212733243](https://github.com/Aerlany/Images-of-mine/raw/main/PicGo/image-20221122212733243.png)



**Pipe instance**

```c
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
```



**Named Pipe (FIFO) (First Input First Output)**

**PIPEs pass data between related processes.**

**FIFOs pass data between any processes.**

```c
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
```



### **Message Queues**

![image-20221125153954761](https://github.com/Aerlany/Images-of-mine/raw/main/PicGo/image-20221125153954761.png)



```

```



Waitting for sometime











