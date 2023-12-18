# Linux常用技巧

## 一、Linux systemd

Systemd 是一系列工具的集合， 包括了一个专用的系统日志管理服务：Journald。这个服务的设计初衷是克服现有 Syslog 服务的日志内容易伪造和日志格式不统一等缺点，Journald 用 二进制格式 保存所有的日志信息，因而日志内容很难被手工伪造。Journald 还提供了一个 journalctl 命令来查看日志信息，这样就使得不同服务输出的日志具有相同的排版格式， 便于数据的二次处理。

![img](https://github.com/Aerlany/Images-of-mine/raw/main/PicGo/sipbixvm4ttae_291341aa0bb34e00ad3e2aa0b2b96cb1.png)

### 1.Systemd Unit

Systemd 可以管理所有系统资源，不同的资源统称为 Unit（单位）。

在 Systemd 的生态圈中，Unit 文件统一了过去各种不同系统资源配置格式，例如服务的启/停、定时任务、设备自动挂载、网络配置、虚拟内存配置等。而 Systemd 通过不同的文件后缀来区分这些配置文件。

```
.automount：用于控制自动挂载文件系统，相当于 SysV-init 的 autofs 服务

.device：对于 /dev 目录下的设备，主要用于定义设备之间的依赖关系

.mount：定义系统结构层次中的一个挂载点，可以替代过去的 /etc/fstab 配置文件

.path：用于监控指定目录或文件的变化，并触发其它 Unit 运行

.scope：这种 Unit 文件不是用户创建的，而是 Systemd 运行时产生的，描述一些系统服务的分组信息

.service：封装守护进程的启动、停止、重启和重载操作，是最常见的一种 Unit 文件

.slice：用于表示一个 CGroup 的树，通常用户不会自己创建这样的 Unit 文件

.snapshot：用于表示一个由 systemctl snapshot 命令创建的 Systemd Units 运行状态快照

.socket：监控来自于系统或网络的数据消息，用于实现基于数据自动触发服务启动

.swap：定义一个用户做虚拟内存的交换分区

.target：用于对 Unit 文件进行逻辑分组，引导其它 Unit 的执行。它替代了 SysV-init 运行级别的作用，并提供更灵活的基于特定设备事件的启动方式

.timer：用于配置在特定时间触发的任务，替代了 Crontab 的功能
```



Unit 文件按照 Systemd 约定，应该被放置指定的三个系统目录之一中。这三个目录是有优先级的，如下所示，越靠上的优先级越高。因此，在三个目录中有同名文件的时候，只有优先级最高的目录里的那个文件会被使用。

```tex
/etc/systemd/system：系统或用户自定义的配置文件

/run/systemd/system：软件运行时生成的配置文件

/usr/lib/systemd/system：系统或第三方软件安装时添加的配置文件。
```

Systemd 默认从目录 /etc/systemd/system/ 读取配置文件。但是，里面存放的大部分文件都是符号链接，指向目录 /usr/lib/systemd/system/，真正的配置文件存放在那个目录。

### 2.Unit 和 Target

Unit 是 Systemd 管理系统资源的基本单元，可以认为每个系统资源就是一个 Unit，并使用一个 Unit 文件定义。在 Unit 文件中需要包含相应服务的描述、属性以及需要运行的命令。

Target 是 Systemd 中用于指定系统资源启动组的方式，相当于 SysV-init 中的运行级别。

简单说，Target 就是一个 Unit 组，包含许多相关的 Unit 。启动某个 Target 的时候，Systemd 就会启动里面所有的 Unit。从这个意义上说，Target 这个概念类似于”状态点”，启动某个 Target 就好比启动到某种状态。

### 3.Unit 文件结构

```
[Unit]
Description=Hello World
After=docker.service
Requires=docker.service

[Service]
TimeoutStartSec=0
ExecStartPre=-/usr/bin/docker kill busybox1
ExecStartPre=-/usr/bin/docker rm busybox1
ExecStartPre=/usr/bin/docker pull busybox
ExecStart=/usr/bin/docker run --name busybox1 busybox /bin/ sh -c "while true; do echo Hello World; sleep 1; done"
ExecStop="/usr/bin/docker stop busybox1"
ExecStopPost="/usr/bin/docker rm busybox1"

[Install]
WantedBy=multi-user.target
```

Unit 和 Install 段：所有 Unit 文件通用，用于配置服务（或其它系统资源）的描述、依赖和随系统启动的方式

Service 段：服务（Service）类型的 Unit 文件（后缀为 .service）特有的，用于定义服务的具体管理和操作方法

```bash
Description：描述这个 Unit 文件的信息

Documentation：指定服务的文档，可以是一个或多个文档的 URL 路径

Requires：依赖的其它 Unit 列表，列在其中的 Unit 模板会在这个服务启动时的同时被启动。并且，如果其中任意一个服务启动失败，这个服务也会被终止

Wants：与 Requires 相似，但只是在被配置的这个 Unit 启动时，触发启动列出的每个 Unit 模块，而不去考虑这些模板启动是否成功

After：与 Requires 相似，但是在后面列出的所有模块全部启动完成以后，才会启动当前的服务

Before：与 After 相反，在启动指定的任务一个模块之间，都会首先确证当前服务已经运行

Binds To：与 Requires 相似，失败时失败，成功时成功，但是在这些模板中有任意一个出现意外结束或重启时，这个服务也会跟着终止或重启

Part Of：一个 Bind To 作用的子集，仅在列出的任务模块失败或重启时，终止或重启当前服务，而不会随列出模板的启动而启动

OnFailure：当这个模板启动失败时，就会自动启动列出的每个模块

Conflicts：与这个模块有冲突的模块，如果列出的模块中有已经在运行的，这个服务就不能启动，反之亦然
```

### 4.Unit 段

```
Description：描述这个 Unit 文件的信息

Documentation：指定服务的文档，可以是一个或多个文档的 URL 路径

Requires：依赖的其它 Unit 列表，列在其中的 Unit 模板会在这个服务启动时的同时被启动。并且，如果其中任意一个服务启动失败，这个服务也会被终止

Wants：与 Requires 相似，但只是在被配置的这个 Unit 启动时，触发启动列出的每个 Unit 模块，而不去考虑这些模板启动是否成功

After：与 Requires 相似，但是在后面列出的所有模块全部启动完成以后，才会启动当前的服务

Before：与 After 相反，在启动指定的任务一个模块之间，都会首先确证当前服务已经运行

Binds To：与 Requires 相似，失败时失败，成功时成功，但是在这些模板中有任意一个出现意外结束或重启时，这个服务也会跟着终止或重启

Part Of：一个 Bind To 作用的子集，仅在列出的任务模块失败或重启时，终止或重启当前服务，而不会随列出模板的启动而启动

OnFailure：当这个模板启动失败时，就会自动启动列出的每个模块

Conflicts：与这个模块有冲突的模块，如果列出的模块中有已经在运行的，这个服务就不能启动，反之亦然
```

### 5.Install 段

这部分配置的目标模块通常是特定运行目标的 .target 文件，用来使得服务在系统启动时自动运行。这个区段可以包含三种启动约束：

```
WantedBy：和 Unit 段的 Wants 作用相似，只有后面列出的不是服务所依赖的模块，而是依赖当前服务的模块。它的值是一个或多个 Target，当前 Unit 激活时（enable）符号链接会放入 /etc/systemd/system 目录下面以 <Target 名> + .wants 后缀构成的子目录中，如 “/etc/systemd/system/multi-user.target.wants/“

$ find /etc/systemd/system/* -type d
/etc/systemd/system/default.target.wants
/etc/systemd/system/getty.target.wants
/etc/systemd/system/graphical.target.wants
/etc/systemd/system/multi-user.target.wants
/etc/systemd/system/network-online.target.wants
/etc/systemd/system/paths.target.wants
/etc/systemd/system/shutdown.target.wants
/etc/systemd/system/sockets.target.wants
/etc/systemd/system/sysinit.target.wants
/etc/systemd/system/timers.target.wants

RequiredBy：和 Unit 段的 Wants 作用相似，只有后面列出的不是服务所依赖的模块，而是依赖当前服务的模块。它的值是一个或多个 Target，当前 Unit 激活时，符号链接会放入 /etc/systemd/system 目录下面以 <Target 名> + .required 后缀构成的子目录中

Also：当前 Unit enable/disable 时，同时 enable/disable 的其他 Unit

Alias：当前 Unit 可用于启动的别名
```

SysV-init 运行级别与 Systemd Target 对应的 Unit 文件

![1832b220aa754cd18c504acc7686a560.png](https://github.com/Aerlany/Images-of-mine/raw/main/PicGo/sipbixvm4ttae_04ff0852a1fb4660beb8179cf6927faa.png)

通过 systemctl list-units --type=target 命令可以获取当前正在使用的运行目标

```
$ systemctl list-units --type=target
UNIT                   LOAD   ACTIVE SUB    DESCRIPTION
basic.target           loaded active active Basic System
cryptsetup.target      loaded active active Encrypted Volumes
getty.target           loaded active active Login Prompts
graphical.target       loaded active active Graphical Interface
local-fs-pre.target    loaded active active Local File Systems (Pre)
local-fs.target        loaded active active Local File Systems
multi-user.target      loaded active active Multi-User System
network-online.target  loaded active active Network is Online
network.target         loaded active active Network
nss-user-lookup.target loaded active active User and Group Name Lookups
paths.target           loaded active active Paths
remote-fs-pre.target   loaded active active Remote File Systems (Pre)
remote-fs.target       loaded active active Remote File Systems
slices.target          loaded active active Slices
sockets.target         loaded active active Sockets
sound.target           loaded active active Sound Card
swap.target            loaded active active Swap
sysinit.target         loaded active active System Initialization
time-sync.target       loaded active active System Time Synchronized
timers.target          loaded active active Timers
LOAD   = Reflects whether the unit definition was properly loaded.
ACTIVE = The high-level unit activation state, i.e. generalization of SUB.
SUB    = The low-level unit activation state, values depend on unit type.
20 loaded units listed. Pass --all to see loaded but inactive units, too.
To show all installed unit files use 'systemctl list-unit-files'.
```

### 6.Service 段

用来 Service 的配置，只有 Service 类型的 Unit 才有这个区块。它的主要字段分为服务生命周期和服务上下文配置两个方面。

#### 6.1 服务生命周期控制相关

```
Type：定义启动时的进程行为，它有以下几种值：

Type=simple：默认值，执行ExecStart指定的命令，启动主进程


Type=forking：以 fork 方式从父进程创建子进程，创建后父进程会立即退出


Type=oneshot：一次性进程，Systemd 会等当前服务退出，再继续往下执行


Type=dbus：当前服务通过D-Bus启动


Type=notify：当前服务启动完毕，会通知Systemd，再继续往下执行


Type=idle：若有其他任务执行完毕，当前服务才会运行


RemainAfterExit：值为 true 或 false（默认）。当配置为 true 时，Systemd 只会负责启动服务进程，之后即便服务进程退出了，Systemd 也仍然会认为这个服务还在运行中。这个配置主要是提供给一些并非常驻内存，而是启动注册后立即退出，然后等待消息按需启动的特殊类型服务使用的。

ExecStart：启动当前服务的命令

ExecStartPre：启动当前服务之前执行的命令

ExecStartPos：启动当前服务之后执行的命令

ExecReload：重启当前服务时执行的命令

ExecStop：停止当前服务时执行的命令

ExecStopPost：停止当其服务之后执行的命令

RestartSec：自动重启当前服务间隔的秒数

Restart：定义何种情况 Systemd 会自动重启当前服务，可能的值包括 always（总是重启）、on-success、on-failure、on-abnormal、on-abort、on-watchdog

TimeoutStartSec：启动服务时等待的秒数，这一配置对于使用 Docker 容器而言显得尤为重要，因其第一次运行时可能需要下载镜像，严重延时会容易被 Systemd 误判为启动失败杀死。通常，对于这种服务，将此值指定为 0，从而关闭超时检测

TimeoutStopSec：停止服务时的等待秒数，如果超过这个时间仍然没有停止，Systemd 会使用 SIGKILL 信号强行杀死服务的进程
```

#### 6.2 服务上下文配置相关

```
Environment：为服务指定环境变量

EnvironmentFile：指定加载一个包含服务所需的环境变量的列表的文件，文件中的每一行都是一个环境变量的定义

Nice：服务的进程优先级，值越小优先级越高，默认为 0。其中 -20 为最高优先级，19 为最低优先级

WorkingDirectory：指定服务的工作目录

RootDirectory：指定服务进程的根目录（/ 目录）。如果配置了这个参数，服务将无法访问指定目录以外的任何文件

User：指定运行服务的用户

Group：指定运行服务的用户组

MountFlags：服务的 Mount Namespace 配置，会影响进程上下文中挂载点的信息，即服务是否会继承主机上已有挂载点，以及如果服务运行执行了挂载或卸载设备的操作，是否会真实地在主机上产生效果。可选值为 shared、slaved 或 private

shared：服务与主机共用一个 Mount Namespace，继承主机挂载点，且服务挂载或卸载设备会真实地反映到主机上

slave：服务使用独立的 Mount Namespace，它会继承主机挂载点，但服务对挂载点的操作只有在自己的 Namespace 内生效，不会反映到主机上

private：服务使用独立的 Mount Namespace，它在启动时没有任何任何挂载点，服务对挂载点的操作也不会反映到主机上
```

LimitCPU / LimitSTACK / LimitNOFILE / LimitNPROC 等：限制特定服务的系统资源量，例如 CPU、程序堆栈、文件句柄数量、子进程数量等



注意：如果在 ExecStart、ExecStop 等属性中使用了 Linux 命令，则必须要写出完整的绝对路径。对于 ExecStartPre 和 ExecStartPost 辅助命令，若前面有个 “-” 符号，表示忽略这些命令的出错。因为有些 “辅助” 命令本来就不一定成功，比如尝试清空一个文件，但文件可能不存在。

### 7. Unit 文件占位符和模板

#### 7.1 Unit 文件占位符

在 Unit 文件中，有时会需要使用到一些与运行环境有关的信息，例如节点 ID、运行服务的用户等。这些信息可以使用占位符来表示，然后在实际运行被动态地替换实际的值。

```
%n：完整的 Unit 文件名字，包括 .service 后缀名

%p：Unit 模板文件名中 @ 符号之前的部分，不包括 @ 符号

%i：Unit 模板文件名中 @ 符号之后的部分，不包括 @ 符号和 .service 后缀名

%t：存放系统运行文件的目录，通常是 “run”

%u：运行服务的用户，如果 Unit 文件中没有指定，则默认为 root

%U：运行服务的用户 ID

%h：运行服务的用户 Home 目录，即 %{HOME} 环境变量的值

%s：运行服务的用户默认 Shell 类型，即 %{SHELL} 环境变量的值

%m：实际运行节点的 Machine ID，对于运行位置每个的服务比较有用

%b：Boot ID，这是一个随机数，每个节点各不相同，并且每次节点重启时都会改变

%H：实际运行节点的主机名

%v：内核版本，即 “uname -r” 命令输出的内容

%%：在 Unit 模板文件中表示一个普通的百分号
```

#### 7.2 Unit 模板

在现实中，往往有一些应用需要被复制多份运行。例如，用于同一个负载均衡器分流的多个服务实例，或者为每个 SSH 连接建立一个独立的 sshd 服务进程。



Unit 模板文件的写法与普通的服务 Unit 文件基本相同，不过 Unit 模板的文件名是以 @ 符号结尾的。通过模板启动服务实例时，需要在其文件名的 @ 字符后面附加一个参数字符串。



示例：apache@.service

apache@.service 模板

```
[Unit]
Description=My Advanced Service Template
After=etcd.service docker.service
[Service]
TimeoutStartSec=0
ExecStartPre=-/usr/bin/docker kill apache%i
ExecStartPre=-/usr/bin/docker rm apache%i
ExecStartPre=/usr/bin/docker pull coreos/apache
ExecStart=/usr/bin/docker run --name apache%i -p %i:80 coreos/apache /usr/sbin/apache2ctl -D FOREGROUND
ExecStartPost=/usr/bin/etcdctl set /domains/example.com/%H:%i running
ExecStop=/usr/bin/docker stop apache1
ExecStopPost=/usr/bin/docker rm apache1
ExecStopPost=/usr/bin/etcdctl rm /domains/example.com/%H:%i
[Install]
WantedBy=multi-user.target
```

启动 Unit 模板的服务实例

在服务启动时需要在 @ 后面放置一个用于区分服务实例的附加字符参数，通常这个参数用于监控的端口号或控制台 TTY 编译号。

```
$ systemctl start apache@8080.service
```

Systemd 在运行服务时，总是会先尝试找到一个完整匹配的 Unit 文件，如果没有找到，才会尝试选择匹配模板。例如上面的命令，System 首先会在约定的目录下寻找名为 apache@8080.service 的文件，如果没有找到，而文件名中包含 @ 字符，它就会尝试去掉后缀参数匹配模板文件。对于 apache@8080.service，systemd 会找到 apache@.service 模板文件，并通过这个模板文件将服务实例化。





## 二、systemctl 

#### 1、列出所有服务

```
systemctl list-unit-files --type service -all
```

```
systemctl list-unit-files --state=enabled
```



#### 2、启动服务

要在 Linux 中启动服务，你只需使用它的名字：

```javascript
systemctl start <service-name>
```

复制

#### 3、停止服务

要停止 systemd 服务，可以使用 `systemctl` 命令的 `stop` 选项：

```javascript
systemctl stop <service-name>
```

复制

#### 4、重启服务

要重启 systemd 服务，可以使用：

```javascript
systemctl restart <service-name>
```

复制

#### 5、检查服务状态

你可以通过打印服务状态来确认你已经成功执行特定操作：

```javascript
systemctl status <service-name>
```

#### 6.自启动服务

```javascript
systemctl enable <service-name>
```

#### 7.停止自启动

```javascript
systemctl disable <service-name>
```

#### 8.查看是否自启

```bash
systemctl is-enabled <service-name>
```

## 三、mysql安装步骤

#### 1.更新 yum

在使用`yum`安装 MySQL 前，先更新 yum

```javascript
yum update -y
```

#### 2. 添加 MySQL 的 yum 仓库源

Mysql 仓库源地址: https://dev.mysql.com/downloads/repo/yum/

选择 CentOS 7 版本的 mysql 源

![img](https://github.com/Aerlany/Images-of-mine/raw/main/PicGo/6445c514ea6bd681d45752ed5afeb29b.png)

 对应的命令操作为: 安装 `wget` 工具:

```javascript
sudo yum install -y wget 
```

使用 `wget` 下载 mysql yum 源:

```javascript
wget https://dev.mysql.com/get/mysql80-community-release-el7-3.noarch.rpm
```

添加 mysql yum 源(在 wget 的下载目录,紧接着上一命令,则无需调整):

```javascript
sudo yum localinstall mysql80-community-release-el7-3.noarch.rpm
```

安装 `yum` 工具 `yum-utils` :

```javascript
sudo yum install -y yum-utils
```

查看可用的 mysql :

```javascript
yum repolist enabled | grep "mysql.*-community.*"
```

此时会看到当前可用的 MySQL 版本为 `mysql80`, 这是因为最新 mysql 最新版为 `8.0` 版本

#### 3.查看所有的 mysql 版本

```javascript
yum repolist all | grep mysql
```

查询结果:

![img](https://github.com/Aerlany/Images-of-mine/raw/main/PicGo/8b501f8e4ccb6b6ff03ae76ab1908510.png)

#### 3.2 启用指定版本的 mysql

在 **2.2** 中可以看到目前启用(`enable`)的是 `mysql80`,如果需要安装 mysql 5.7 ,则需要先禁用(`disable`) mysql8.0,然后启用(`enable`)mysql5.7 禁用 mysql8.0:

```javascript
sudo yum-config-manager --disable mysql80-community
```



启用 mysql 5.7

```javascript
sudo yum-config-manager --enable mysql57-community
```



校验当前启用(`enable`)的 mysql 版本是否为 5.7:

```javascript
yum repolist enabled | grep mysql
```



查询结果:

![img](https://github.com/Aerlany/Images-of-mine/raw/main/PicGo/0c1576b962b24f830bd8fb38a8063155.png)

 从结果中可以看出，当前启用的 mysql 版本为 5.7,没有问题

#### 4. 安装 mysql

在步骤 **3** 中已经设置启用的mysql版本为 5.7,接下来则直接进行安装

安装 mysql

```javascript
sudo yum install -y mysql-community-server
```



待命令执行结束，安装即完成 启动 mysql 服务:

```javascript
sudo service mysqld start
```



查看 mysql 服务状态:

```javascript
sudo service mysqld status
```



#### 5 .MySQL 初始化设置

从 MySQL 5.7 开始，mysql 安装之后，会默认随机生成一个临时密码,因此登录之后需要修改密码

查看生成的初始密码:

```javascript
sudo grep 'temporary password' /var/log/mysqld.log
```



使用初始密码进行登录:

```javascript
mysql -u root -p
```



登录成功之后设置新密码:

```javascript
ALTER USER 'root'@'localhost' IDENTIFIED BY 'MyNewPass4!';
```

设置密码安全性（以支持简单密码）

```sql
set global validate_password_policy = 'LOW';
```

```sql
set global validate_password_length = 6;
```

设置完记得刷新权限

```sql
flush privileges;
```



**注意**: 设置的**新密码必须包含大写字母、小写字母、数字、标点符号，且密码长度至少为 8**

密码设置之后安装即完成

#### 6. 设置 MySQL开机启动

MySLQ 安装完成之后运行的服务名称为: `mysqld` CentOS 7 使用 `systemctl` 命令工具操作服务:

| 启动  | 停止 | 重启    | 开机启动 | 关闭开机启动 |
| :---- | :--- | :------ | :------- | :----------- |
| start | stop | restart | enable   | disable      |

开机启动命令:

```javascript
systemctl enable mysqld
```



#### 7 .设置远程连接

登录 mysql(使用新设置的密码)

```javascript
mysql -u root -p
```



登录成功之后执行以下命令:

```javascript
GRANT ALL PRIVILEGES ON *.* TO 'root'@'%' IDENTIFIED BY 'yourNewPassword' WITH GRANT OPTION;
```



其中 `yourNewPassword` 即为刚才设置的新密码 刷新权限

```javascript
FLUSH PRIVILEGES;
```



到这里远程连接已经设置成功

#### 8 .配置文件

mysql 的配置文件目录为:

```javascript
/etc/my.cnf
```



## 四、Linux Crontab 定时任务

`linux内置的cron进程能帮我们实现这些需求，cron搭配shell脚本，非常复杂的指令也没有问题`。

**cron介绍**
*我们经常使用的是crontab命令是cron table的简写，它是cron的配置文件，也可以叫它作业列表，我们可以在以下文件夹内找到相关配置文件。*

`/var/spool/cron/` 	目录下存放的是每个用户包括root的crontab任务，每个任务以创建者的名字命名
`/etc/crontab` 			这个文件负责调度各种管理和维护任务。
`/etc/cron.d/` 			这个目录用来存放任何要执行的crontab文件或脚本。
我们还可以把脚本放在/etc/cron.hourly、/etc/cron.daily、/etc/cron.weekly、/etc/cron.monthly目录中，让它每小时/天/星期、月执行一次。

**crontab的使用**

```sh
crontab [-u username]　　　　//省略用户表表示操作当前用户的crontab
    -e      (编辑工作表)
    -l      (列出工作表里的命令)
    -r      (删除工作作)
```

我们用crontab -e进入当前用户的工作表编辑，是常见的vim界面。每行是一条命令。

crontab的命令构成为 时间+动作，其时间有`分、时、日、月、周`五种，操作符有

```java
* 	取值范围内的所有数字
/ 	每过多少个数字
- 	从X到Z
,   散列数字
```



## 五、Linux 命令行操作和查看u盘

**1、查看系统磁盘挂载情况**

```sh
sudo fdisk -l
```

```sh
Disk /dev/nvme0n1：477 GiB，512110190592 字节，1000215216 个扇区
单元：扇区 / 1 * 512 = 512 字节
扇区大小(逻辑/物理)：512 字节 / 512 字节
I/O 大小(最小/最佳)：512 字节 / 512 字节
磁盘标签类型：gpt
磁盘标识符：014C97E3-B16D-4D67-A3E4-267491B1C960

设备                起点       末尾      扇区   大小 类型
/dev/nvme0n1p1      2048     206847    204800   100M EFI 系统
/dev/nvme0n1p2    206848     239615     32768    16M Microsoft 保留
/dev/nvme0n1p3    239616  209969151 209729536   100G Microsoft 基本数据
/dev/nvme0n1p4 209969152  477030399 267061248 127.4G Microsoft 基本数据
/dev/nvme0n1p5 477032448  737697791 260665344 124.3G Microsoft 基本数据
/dev/nvme0n1p6 737699840  739796991   2097152     1G Linux 文件系统
/dev/nvme0n1p7 739796992  998371327 258574336 123.3G Linux LVM
/dev/nvme0n1p8 998371328 1000214527   1843200   900M Windows 恢复环境


Disk /dev/mapper/cl-root：70 GiB，75161927680 字节，146800640 个扇区
单元：扇区 / 1 * 512 = 512 字节
扇区大小(逻辑/物理)：512 字节 / 512 字节
I/O 大小(最小/最佳)：512 字节 / 512 字节


Disk /dev/mapper/cl-swap：7.8 GiB，8313110528 字节，16236544 个扇区
单元：扇区 / 1 * 512 = 512 字节
扇区大小(逻辑/物理)：512 字节 / 512 字节
I/O 大小(最小/最佳)：512 字节 / 512 字节


Disk /dev/mapper/cl-home：45.6 GiB，48913973248 字节，95535104 个扇区
单元：扇区 / 1 * 512 = 512 字节
扇区大小(逻辑/物理)：512 字节 / 512 字节
I/O 大小(最小/最佳)：512 字节 / 512 字节


Disk /dev/sda：58.6 GiB，62914560000 字节，122880000 个扇区
单元：扇区 / 1 * 512 = 512 字节
扇区大小(逻辑/物理)：512 字节 / 512 字节
I/O 大小(最小/最佳)：512 字节 / 512 字节
磁盘标签类型：dos
磁盘标识符：0x0009188d

设备       启动  起点      末尾      扇区  大小 Id 类型
/dev/sda1  *     2048 122879999 122877952 58.6G  c W95 FAT32 (LBA)
# 可以看到我们插入的u盘设备
```

**2.创建磁盘挂载目录**

我们一般将u盘目录创建到`/mnt`目录

```sh
sudo mkdir /mnt/test
```

将U盘挂载到该目录

```sh
sudo mount /dev/sda1 /mnt/test
```

进入到该目录就可以访问U盘内容

如果需要卸载U盘

```sh
sudo umount /mnt/test
```

## 六、Linux  nginx 安装指南

安装epel-release源

```sh
sudo yum install epel-release
```

下载nginx

```sh
sudo yum install nginx
```

检查安装

```sh
nginx -vnginx -v
```

**nginx 配置**

```sh
# nginx 配置文件
vim /etc/nginx/nginx.conf
```

```sh
# For more information on configuration, see:
#   * Official English Documentation: http://nginx.org/en/docs/
#   * Official Russian Documentation: http://nginx.org/ru/docs/

user nginx;
worker_processes auto;
error_log /var/log/nginx/error.log;
pid /run/nginx.pid;

# Load dynamic modules. See /usr/share/doc/nginx/README.dynamic.
include /usr/share/nginx/modules/*.conf;

events {
    worker_connections 1024;
}

http {
    log_format  main  '$remote_addr - $remote_user [$time_local] "$request" '
                      '$status $body_bytes_sent "$http_referer" '
                      '"$http_user_agent" "$http_x_forwarded_for"';

    access_log  /var/log/nginx/access.log  main;

    sendfile            on;
    tcp_nopush          on;
    tcp_nodelay         on;
    keepalive_timeout   65;
    types_hash_max_size 4096;

    include             /etc/nginx/mime.types;
    default_type        application/octet-stream;

    # Load modular configuration files from the /etc/nginx/conf.d directory.
    # See http://nginx.org/en/docs/ngx_core_module.html#include
    # for more information.
    include /etc/nginx/conf.d/*.conf;

    #support cross domain access
    add_header Access-Control-Allow-Origin *;
    add_header Access-Control-Allow-Headers X-Requested-With;
    add_header Access-Control-Allow-Methods GET,POST,OPTIONS;


    server {
        listen       80;
        listen       [::]:80;
        server_name  _;
        root         /usr/share/nginx/html;

        # Load configuration files for the default server block.
        include /etc/nginx/default.d/*.conf;

        error_page 404 /404.html;
        location = /404.html {
        }

        error_page 500 502 503 504 /50x.html;
        location = /50x.html {
        }

        location /user {
            proxy_pass http://43.140.201.70:8080;
			
		#CORS 配置
        add_header 'Access-Control-Allow-Origin' '*';
	    add_header 'Access-Control-Allow-Methods' 'GET, POST, OPTIONS, PUT, DELETE';
	    #是否允许cookie传输
        add_header 'Access-Control-Allow-Credentials' 'true';
	    add_header 'Access-Control-Allow-Headers' 'Authorization,Content-Type,Accept,Origin,User-Agent,DNT,Cache-Control,X-Mx-ReqToken,X-Data-Type,X-Requested-With,X-Data-Type,X-Auth-Token';
            
            #针对浏览器的options预请求直接返回200，否则会被403 forbidden--invalie CORS request
            if ( $request_method = 'OPTIONS' ) { 
								return 200;
            } 
        }

        location /courseInfo {
            proxy_pass http://43.140.201.70:8080;
	}
        location /courseExam {
            proxy_pass http://43.140.201.70:8080;
	}
        location /courseExamPaper {
            proxy_pass http://43.140.201.70:8080;
	}
        location /student {
            proxy_pass http://43.140.201.70:8080;
	}
    }

# Settings for a TLS enabled server.
#
#    server {
#        listen       443 ssl http2;
#        listen       [::]:443 ssl http2;
#        server_name  _;
#        root         /usr/share/nginx/html;
#
#        ssl_certificate "/etc/pki/nginx/server.crt";
#        ssl_certificate_key "/etc/pki/nginx/private/server.key";
#        ssl_session_cache shared:SSL:1m;
#        ssl_session_timeout  10m;
#        ssl_ciphers HIGH:!aNULL:!MD5;
#        ssl_prefer_server_ciphers on;
#
#        # Load configuration files for the default server block.
#        include /etc/nginx/default.d/*.conf;
#
#        error_page 404 /404.html;
#            location = /40x.html {
#        }
#
#        error_page 500 502 503 504 /50x.html;
#            location = /50x.html {
#        }
#    }

}

```

## 七、Linux  ssh免密登录

```sh
# 生成密钥
ssh-keygen
```

将公钥上传置服务器更名为authorized_keys

```sh
scp id_rsa.pub root@192.168.0.0.1 
```

或者

```shell
ssh-copy-id root@192.168.1.106
```

## 八、Linux  NVM安装配置

```sh
# 配置镜像
export NVM_NODEJS_ORG_MIRROR=https://npm.taobao.org/mirrors/node/
export NVM_IOJS_ORG_MIRROR=http://npm.taobao.org/mirrors/iojs
```

## 九、Linux  字体目录

1. Linux 字体存在该目录中。如果需要新建字体应该在该目录中添加新目录`/newDir`

   ```sh
   /usr/share/fonts
   ```

2. 并且设置目录权限

   ```sh
   chmod 755 myfonts
   ```

3. 安装字体索引指令

   ```sh
   sudo yum install -y fontconfig mkfontscale
   ```

4. 建立字体索引信息更新字体缓存

   ```sh
   cd /usr/share/fonts/myfonts
   mkfontscale && mkfontdir && fc-cache -fv
   ```

5. 查看安装情况

   ```sh
   fc-list :lang=zh
   ```

## 十、Linux  设置开机自启

#### 一、在etc/rc.local中添加

1、先修改好脚本，使其所有模块都能在任意目录启动时正常执行;

2、再在/etc/rc.local的末尾添加一行以绝对路径启动脚本的行。

```sh
#!/bin/bash
# THIS FILE IS ADDED FOR COMPATIBILITY PURPOSES
#
# It is highly advisable to create own systemd services or udev rules
# to run scripts during boot instead of using this file.
#
# In contrast to previous versions due to parallel execution during boot
# this script will NOT be run after all other services.
#
# Please note that you must run 'chmod +x /etc/rc.d/rc.local' to ensure
# that this script will be executed during boot.

touch /var/lock/subsys/local
```

3、添加可执行权限：chmod +x /etc/rc.d/rc.local

4、保存并退出;再重启动测试下，则在其它的程序都启动完成后，将启动脚本。

#### 二、使用systemd服务

代的Linux发行版通常使用systemd来管理系统进程和服务。

你可以创建一个systemd服务来实现开机自启动。首先，创建一个以 `.service` 结尾的文件（例如 `myservice.service`）并将以下内容添加进去：

```sh
[Unit]
Description=My Service
After=network.target

[Service]
ExecStart=/path/to/your/command

[Install]
WantedBy=default.target
```

将 `/path/to/your/command` 替换为你想要自启的命令的完整路径。

将该 `.service` 文件复制到 `/etc/systemd/system/` 目录下，然后运行以下命令启用服务并启动：

```sh
sudo systemctl enable myservice.service
sudo systemctl start myservice.service
```

## 十一、Linux  FireWall

查看版本： 

```sh
firewall-cmd --version
```

查看帮助：

```sh
 firewall-cmd --help
```

显示状态： 

```sh
firewall-cmd --state
```

查看所有打开的端口：

```sh
 firewall-cmd --zone=public --list-ports
```

更新防火墙规则： 

```sh
firewall-cmd --reload
```

查看区域信息: 

```sh
firewall-cmd --get-active-zones
```

查看指定接口所属区域： 

```sh
firewall-cmd --get-zone-of-interface=eth0
```

拒绝所有包：

```sh
firewall-cmd --panic-on
```

取消拒绝状态： 

```sh
firewall-cmd --panic-off
```

查看是否拒绝： 

```sh
firewall-cmd --query-panic
```

**那怎么开启一个端口呢**

添加

```sh
firewall-cmd --zone=public --add-port=80/tcp --permanent 
（--permanent永久生效，没有此参数重启后失效）
```

重新载入

```sh
firewall-cmd --reload
```

查看

```sh
firewall-cmd --zone=public --query-port=80/tcp
```

删除

```sh
firewall-cmd --zone=public --remove-port=80/tcp --permanent
```

# Linux命令排雷

## 管道符 | 

![image-20231218103123341](https://github.com/Aerlany/Images-of-mine/raw/main/PicGo/image-20231218103123341.png)

Linux提供的管道符`|`将两条命令隔开，管道符左边命令的**输出**会作为管道符**输入**

##  重定向符号 

| 符号    | 解释           |
| ------- | -------------- |
| >       | 输出覆盖重定向 |
| >>      | 输出追加重定向 |
| < 或 << | 标准输入重定向 |

## cat

查看⽂件内容

```sh
cat text.txt
```

多个⽂件合并

```sh
cat file.txt file2.txt > file3.txt
```

⾮交互式编辑或追加内容

```sh
cat >> file.txt << EOF欢迎来到路⻜学城EOF
```

清空⽂件内容

```sh
cat /dev/null > file.txt【/dev/null是linux系统的⿊洞⽂件】
```

**参数：**

- ```sh
  ⽤法：
  cat [选项][⽂件]...
  将[⽂件]或标准输⼊组合输出到标准输出。
  
  -A, --show-all 			等价于-vET
  -b, --number-nonblank 	对⾮空输出⾏编号
  -e 						等价于-vE
  -E, --show-ends			在每⾏结束处显示$
  -n, --number			对输出的所有⾏编号
  -s, --squeeze-blank		不输出多⾏空⾏
  -t						与-vT等价
  -T, --show-tabs			将跳格字符显示为^I
  -v, --show-nonprinting	使⽤^和M-引⽤，除了LFD和TAB之外
  --help					显示此帮助信息并退出
  --version				输出版本信息并退出
  
  如果[⽂件]缺省，或者[⽂件]为-，则读取标准输⼊。
  ```

## tac

与cat命令作⽤相反，反向读取⽂件内容

```sh
➜  Temp cat text.txt 
我是0
我是1
➜  Temp tac text.txt 
我是1
我是0
➜  Temp 
```

## more & less

分屏查看大文本数据

```sh
more 操作： 
enter 下一行
空格 下一页
```

```sh
less 操作参照vim
```

## head & tail

head 用于查看文件开头的n行

```sh
head -5 查看文件开头的5行（默认为10行）

参数：
-c		查看字符数 
```

less 用于查看文件结尾的n行

```sh
tail -5 查看文件结尾的5行（默认为10行）

参数：
-f 		实时查看已有文件末尾信息
-F   	实时查看文件()可以未创建末尾信息  
```

## cut

cut命令在每个文件的各行中用于逐行文本分割，将分割片段作为标准输出

**参数**：

- ```sh
  -c			以字符为单位分割
  -b			以字节为单位分割
  -n			取消分割多字节字符，与-b一起使用
  -d			自定义分割符
  -f			与-d一起使用，指定到那个区域
  
  指定范围：
         N      第 N 个 字节, 字符 或 字段, 从 1 计数 起
         N-     从 第 N 个 字节, 字符 或 字段 直至 行尾
         N-M    从 第 N 到 第 M (并包括 第M) 个 字节, 字符 或 字段
         -M     从 第 1 到 第 M (并包括 第M) 个 字节, 字符 或 字段
  
  ```

**案例：**

```sh
# 截取指定字符范围的文本
cut -c 3- passwd

# 自定义分割符号进行截取，并限定范围
cut -d ":" -f1-10 passwd
```

## sort

sort命令将文件按照规则进行排序，将结果作为标准输出

```sh
sort [选项] [文件]
```

**参数**：

- ```sh
  -b     	忽略排序字段或关键字中开头的空格
  -c     	检查是否指定文件已经排序好了,不排序.
  -d     	在关键字中只考虑[a-zA-Z0-9]字符.
  -f     	将关键字中的小写字母折合成大写字母.
  -g     	按照通常的数字值顺序作比较,暗含-b
  -i     	在关键字中只考虑[\040-\0176]字符.
  -k POS1[,POS2]			指定排序范围
  
  -l     	按照当前环境排序.
  -u		排序结果去重
  -n		根据字符串数值比较
  -t		指定分割符号
  
  -m     合并已经排序好的文件,不排序.
  
  ```

**案例**：

```sh
# 指定分割符划分范围进行排序
sort -n -t':' -k 3 passwd
```

## uniq

uniq命令将文件逐行去重，将结果作为标准输出

```sh
uniq [选项] [文件]
```

**参数：**

- ```sh
  -c		显示每行出现的次数
  -d		只输出重复的行
  -u		只显示出现过一次的行
  ```

  





## xargs 

xargs（英文全拼： **eXtended ARGuments**）是给命令传递参数的一个过滤器，也是组合多个命令的一个工具。

xargs 可以将管道或标准输入（stdin）数据转换成命令行参数，也能够从文件的输出中读取数据。

xargs 也可以将单行或多行文本输入转换为其他格式，例如多行变单行，单行变多行。

xargs 默认的命令是 echo，这意味着通过管道传递给 xargs 的输入将会包含换行和空白，不过通过 xargs 的处理，换行和空白将被空格取代。

xargs 是一个强有力的命令，它能够捕获一个命令的输出，然后传递给另外一个命令。

之所以能用到这个命令，关键是由于很多命令不支持|管道来传递参数，而日常工作中有有这个必要，所以就有了 xargs 命令，例如：

```sh
somecommand |xargs -item  command
```

**参数：**

- ```sh
  -a file 从文件中读入作为 stdin
  -e flag ，注意有的时候可能会是-E，flag必须是一个以空格分隔的标志，当xargs分析到含有flag这个标志的时候就停止。
  -p 当每次执行一个argument的时候询问一次用户。
  -n num 后面加次数，表示命令在执行的时候一次用的argument的个数，默认是用所有的。
  -t 表示先打印命令，然后再执行。
  -i 或者是-I，这得看linux支持了，将xargs的每项名称，一般是一行一行赋值给 {}，可以用 {} 代替。
  -r no-run-if-empty 当xargs的输入为空的时候则停止xargs，不用再去执行了。
  -s num 命令行的最大字符数，指的是 xargs 后面那个命令的最大命令行字符数。
  -L num 从标准输入一次读取 num 行送给 command 命令。
  -l 同 -L。
  -d delim 分隔符，默认的xargs分隔符是回车，argument的分隔符是空格，这里修改的是xargs的分隔符。
  -x exit的意思，主要是配合-s使用。。
  -P 修改最大的进程数，默认是1，为0时候为as many as it can ，这个例子我没有想到，应该平时都用不到的吧。
  ```

  ### 实例

  xargs 用作替换工具，读取输入数据重新格式化后输出。

  定义一个测试文件，内有多行文本数据：

  ```sh
  # cat test.txt
  
  a b c d e f g
  h i j k l m n
  o p q
  r s t
  u v w x y z
  ```

  多行输入单行输出：

  ```sh
  # cat test.txt | xargs
  a b c d e f g h i j k l m n o p q r s t u v w x y z
  ```

  -n 选项多行输出：

  ```sh
  # cat test.txt | xargs -n3
  
  a b c
  d e f
  g h i
  j k l
  m n o
  p q r
  s t u
  v w x
  y z
  ```

  -d 选项可以自定义一个定界符：

  ```sh
  # echo "nameXnameXnameXname" | xargs -dX
  
  name name name name
  ```

  结合 -n 选项使用：

  ```sh
  # echo "nameXnameXnameXname" | xargs -dX -n2
  
  name name
  name name
  ```

  读取 stdin，将格式化后的参数传递给命令

  假设一个命令为 sk.sh 和一个保存参数的文件 arg.txt：

  ```sh
  #!/bin/bash
  #sk.sh命令内容，打印出所有参数。
  
  echo $*
  ```

  arg.txt文件内容：

  ```sh
  # cat arg.txt
  
  aaa
  bbb
  ccc
  ```

  xargs 的一个选项 -I，使用 -I 指定一个替换字符串 {}，这个字符串在 xargs 扩展时会被替换掉，当 -I 与 xargs 结合使用，每一个参数命令都会被执行一次：

  ```sh
  # cat arg.txt | xargs -I {} ./sk.sh -p {} -l
  
  -p aaa -l
  -p bbb -l
  -p ccc -l
  ```

  复制所有图片文件到 /data/images 目录下：

  ```sh
  ls *.jpg | xargs -n1 -I {} cp {} /data/images
  ```

  xargs 结合 find 使用

  用 rm 删除太多的文件时候，可能得到一个错误信息：**/bin/rm Argument list too long.** 用 xargs 去避免这个问题：

  ```sh
  find . -type f -name "*.log" -print0 | xargs -0 rm -f
  ```

  xargs -0 将 \0 作为定界符。

  统计一个源代码目录中所有 php 文件的行数：

  ```sh
  find . -type f -name "*.php" -print0 | xargs -0 wc -l
  ```

  查找所有的 jpg 文件，并且压缩它们：

  ```sh
  find . -type f -name "*.jpg" -print | xargs tar -czvf images.tar.gz
  ```

  xargs 其他应用

  假如你有一个文件包含了很多你希望下载的 URL，你能够使用 xargs下载所有链接：

  ```sh
  # cat url-list.txt | xargs wget -c
  ```
