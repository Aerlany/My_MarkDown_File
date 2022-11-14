# Operating System



# 1.What’s an Operating System

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

