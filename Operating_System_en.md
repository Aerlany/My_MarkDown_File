# Operating System



# Part 1. What’s an Operating System

## Definition

**What’s an Operating System?**

1. It's the program that runs all the time.
2. It's a **resource manager** (Each program gets time or space with/ on the resource).
3. It's a **control program** (Control execution of  program to prevent error and improper use of the computer).
4. No universally accepted definition.



------

**Multi-programming is the first instance where the OS must make decisions for the users**

1. **Job scheduling** — decides which job should be loaded into the memory.
2. **Memory management** — because several programs in memory at the same time
3. **CPU scheduling** — choose one job among all the jobs are ready to run
4. **Process management** — make sure processes don’t offend each other



## OS Services

**Helping the users:**

1. User interface (用户界面)
2. File system manipulation (文件系统操作)
3. Program execution (程序运行)
4. Communication (交流)
5. I/O operation
6. Error detection (错误检测)



------

**Keeping the system efficient:**

1. Resource allocation (资源分配)
2. Accounting (账户分户)
3. Protection and security (保护和安全)





## Hardware

------

**CPU Working Cycle** (CPU工作周期)

1. **Fetch** the first instruction from memory
2. **Decode** it to determine its type and operands (解码来决定其类型和操作码)
3. **Execute** it



------

**Special CPU Registers** (寄存器)

1. **Program counter (PC)**: keeps the memory address of the next instruction to be fetched
2. **Stack pointer (SP)**: point to the top of the current stack in memory
3. **Program status (PS)**: holds condition code bits and processor state (存储条件代码位和处理器状态)



------

**System Bus** (系统总线)

1. **Address Bus**: specifies (指定) the memory locations (addresses) for the data transfers
2. **Data Bus**: holds the data transfered. Bidirectional
3. **Control Bus**: contains various lines used to route timing (路由定时) and control signals (控制信号) throughout the system



------

**Controllers and Peripherals** (控制器和外设)

1. Peripherals are real devices controlled by controller chips
2. Controllers are processors like the CPU itself, have control registers
3. Device driver writes to the registers, thus control it
4. Controllers are connected to the CPU and to each other by a variety of buses (控制器通过多种总线连接到CPU 和实现相互链接)



------

**Motherboard Chipsets** (主板芯片组)

![image-20221114213713317](/home/user/.config/Typora/typora-user-images/image-20221114213713317.png)

------

**The northbridge**

1. receives a physical memory request
2. decides where to route it to RAM?  to video card? to ...?  **decision made via the memory address map**



**NOTE**

-  The CPU doesn’t know what it’s connected to
- The CPU talks to the outside world through its **pins**, some pins to transmit the **physical memory** address, other pins to transmit the **values**
- The CPU’s gateway to the world is the **front-side bus**



------

**Intel Core 2 QX6600** 

1. **33 pins** to transmit the physical memory address (**so there are 2^33 choices of memory locations**)
2. **64 pins** to send or receive data (**so data path is 64-bit wide, or 8-byte chunks**)
3. This allows the CPU to physically address 64 GiB of memory (2^33 × 8 B)



**Some physical memory addresses are mapped away!**

**This is why 32-bit OSes have problems using 4 GiB of RAM.**



## Bootstrapping

**A computer cannot run without first loading software but must be running before any software can be loaded.**

------

**Intel x86 Bootstrapping**

**1. BIOS (0xfffffff0)**

- POST ( Power-On-Self-Test )
- HardWare Init
- Find a boot device (FD, CD, HD...)
- Copy **sector zero**(MBR) to RAM (0x00007c00)



**2. MBR – the first 512 bytes, contains**

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

1. **HW INT** by send a signal to CPU 
2. **SW INT ** by executing a **System Call**



**Trap (exception)** is a software-generated INT coursed by an error or by a specific request from an user program

**Interrupt vector** is a array of pointers what point to the memory address of **Interrupt Handlers**. 			**The array is indexed by a unique device number**

You can see it:

```sh
$ less /proc/devices
$ less /proc/interrupts
```



## System Calls

A System Call i**s how a program requests a service from an OS kernel** and **provides the interface between a process and the OS**

```sh
$ man 2 intro
$ man 2 syscalls
```

![System call](/home/user/Pictures/Screenshot from 2022-11-15 15-11-14.png)



![How a system call be made](/home/user/.config/Typora/typora-user-images/image-20221115155055411.png)

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

![HW INT and SW INT](/home/user/.config/Typora/typora-user-images/image-20221115222730359.png)



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

![A Process Creation](/home/user/.config/Typora/typora-user-images/image-20221116105610135.png)

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

![image-20221116194207048](/home/user/.config/Typora/typora-user-images/image-20221116194207048.png)

- **Ready:** The Process already has an execution condition, but does not get CPU and cannot be executed.
- **Running:** The Process has taken over the CPU, and is running at this time.
- **Blocked:** The state of a Process while waiting for a service, signal, external operation, etc.





**CPU Switch From Process To Process**

​	















