# Docker

## Docker概述

Docker 是一个开源的应用容器引擎，基于 [Go 语言](https://www.runoob.com/go/go-tutorial.html) 并遵从 Apache2.0 协议开源。

Docker 可以让开发者打包他们的应用以及依赖包到一个轻量级、可移植的容器中，然后发布到任何流行的 Linux 机器上，也可以实现虚拟化。



------

**Docker的应用场景**

- Web 应用的自动化打包和发布。

- 自动化测试和持续集成、发布。

- 在服务型环境中部署和调整数据库或其他的后台应用。

- 从头编译或者扩展现有的 OpenShift 或 Cloud Foundry 平台来搭建自己的 PaaS 环境。

  

------

**Docker 架构**

Docker 包括三个基本概念:

- **镜像（Image）**：	Docker 镜像（Image），就相当于是一个 root 文件系统。比如官方镜像 ubuntu:16.04 就包含了完整的一套 Ubuntu16.04 最小系统的 root 文件系统。
- **容器（Container）**：镜像（Image）和容器（Container）的关系，就像是面向对象程序设计中的类和实例一样，镜像是静态的定义，容器是镜像运行时的实体。容器可以被创建、启动、停止、删除、暂停等。
- **仓库（Repository）**：仓库可看成一个代码控制中心，用来保存镜像。

Docker 使用客户端-服务器 (C/S) 架构模式，使用远程API来管理和创建Docker容器。

Docker 容器通过 Docker 镜像来创建。



------

| Docker | 面向对象 |
| :----- | :------- |
| 容器   | 对象     |
| 镜像   | 类       |

![img](https://www.runoob.com/wp-content/uploads/2016/04/576507-docker1.png)

| 概念                   | 说明                                                         |
| :--------------------- | :----------------------------------------------------------- |
| Docker 镜像(Images)    | Docker 镜像是用于创建 Docker 容器的模板，比如创建一个 Ubuntu 系统。 |
| Docker 容器(Container) | 容器是独立运行的一个或一组应用，是镜像运行时的实体。         |
| Docker 客户端(Client)  | Docker 客户端通过命令行或者其他工具使用 Docker SDK (https://docs.docker.com/develop/sdk/) 与 Docker 的守护进程通信。 |
| Docker 主机(Host)      | 一个物理或者虚拟的机器用于执行 Docker 守护进程和容器。       |
| Docker Registry        | Docker 仓库用来保存镜像，可以理解为代码控制中的代码仓库。Docker Hub([https://hub.docker.com](https://hub.docker.com/)) 提供了庞大的镜像集合供使用。一个 Docker Registry 中可以包含多个仓库（Repository）；每个仓库可以包含多个标签（Tag）；每个标签对应一个镜像。通常，一个仓库会包含同一个软件不同版本的镜像，而标签就常用于对应该软件的各个版本。我们可以通过 **<仓库名>:<标签>** 的格式来指定具体是这个软件哪个版本的镜像。如果不给出标签，将以 **latest** 作为默认标签。 |
| Docker Machine         | Docker Machine是一个简化Docker安装的命令行工具，通过一个简单的命令行即可在相应的平台上安装Docker，比如VirtualBox、 Digital Ocean、Microsoft Azure。 |




------

## Docker安装（CentOS 7）

官方文档：https://docs.docker.com/engine/install/centos/

##### **Uninstall old versions**

```sh
 sudo yum remove docker \
                  docker-client \
                  docker-client-latest \
                  docker-common \
                  docker-latest \
                  docker-latest-logrotate \
                  docker-logrotate \
                  docker-engine
```

##### **Install using the repository**

`配置镜像地址`

```sh
sudo yum-config-manager  --add-repo  \
http://mirrors.aliyun.com/docker-ce/linux/centos/docker-ce.repo
```

##### **Install Docker Engine**

```sh
sudo yum install docker-ce docker-ce-cli containerd.io docker-buildx-plugin docker-compose-plugin
```

`如果存在依赖不存在，可以到官方文档查找下载具体依赖`

##### **Run server**

```sh
sudo systemctl start docker.server
```

##### **Test**

```sh
sudo docker version
```

```sh
//第一次运行hello-word注意！！！！！

[user@localhost yum.repos.d]$ sudo docker run hello-world
Unable to find image 'hello-world:latest' locally
latest: Pulling from library/hello-world
2db29710123e: Pull complete 
Digest: sha256:4e83453afed1b4fa1a3500525091dbfca6ce1e66903fd4c01ff015dbcb1ba33e
Status: Downloaded newer image for hello-world:latest

Hello from Docker!
This message shows that your installation appears to be working correctly.

To generate this message, Docker took the following steps:
 1. The Docker client contacted the Docker daemon.
 2. The Docker daemon pulled the "hello-world" image from the Docker Hub.
    (amd64)
 3. The Docker daemon created a new container from that image which runs the
    executable that produces the output you are currently reading.
 4. The Docker daemon streamed that output to the Docker client, which sent it
    to your terminal.

To try something more ambitious, you can run an Ubuntu container with:
 $ docker run -it ubuntu bash

Share images, automate workflows, and more with a free Docker ID:
 https://hub.docker.com/

For more examples and ideas, visit:
 https://docs.docker.com/get-started/

```

##### Show images

```sh
[user@localhost yum.repos.d]$ sudo docker images 
REPOSITORY    TAG       IMAGE ID       CREATED         SIZE
hello-world   latest    feb5d9fea6a5   19 months ago   13.3kB
```

##### Uninstall docker

```sh
//删除依赖
sudo yum remove docker-ce docker-ce-cli containerd.io docker-buildx-plugin docker-compose-plugin

//删除文件夹
sudo rm -rf /var/lib/docker
```



## Docker 底层原理

### Docker 运行流程

```sh

[user@localhost yum.repos.d]$ sudo docker run hello-world

//1）在本机寻找镜像
Unable to find image 'hello-world:latest' locally

//2）找不到就去DockerHub上找
latest: Pulling from library/hello-world

//3）找不到返回Error 找到就下载到本地
2db29710123e: Pull complete 
Digest: sha256:4e83453afed1b4fa1a3500525091dbfca6ce1e66903fd4c01ff015dbcb1ba33e
Status: Downloaded newer image for hello-world:latest

//4）在本地读取镜像并运行
Hello from Docker!
This message shows that your installation appears to be working correctly.

To generate this message, Docker took the following steps:
 1. The Docker client contacted the Docker daemon.
 2. The Docker daemon pulled the "hello-world" image from the Docker Hub.
    (amd64)
 3. The Docker daemon created a new container from that image which runs the
    executable that produces the output you are currently reading.
 4. The Docker daemon streamed that output to the Docker client, which sent it
    to your terminal.

To try something more ambitious, you can run an Ubuntu container with:
 $ docker run -it ubuntu bash

Share images, automate workflows, and more with a free Docker ID:
 https://hub.docker.com/

For more examples and ideas, visit:
 https://docs.docker.com/get-started/

```

### Docker 底层原理

Docker 使用`C-S`模型( client-serve ), Docker的守护进程运行在主机上，使用Socket与客户端建立链接！

DockerServer 接收到 DockerClient 命令才会执行。

1、Docker有着比虚拟机更少的抽象层。
2、docker利用的是宿主机的内核，vm需要是Guest Os。

![](https://img-blog.csdnimg.cn/20210418145958802.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl81MjUxNDU2Nw==,size_16,color_FFFFFF,t_70)

所以说，新建一个容器的时候，docker不需要想虚拟机一样重新加载一个操作系统内核，避免引导。虚拟机是加载Guest OS，分钟级别的，而docker是利用宿主机的操作系统吗，省略了这个复杂的过程，秒级!

![](https://img-blog.csdnimg.cn/20210418150047448.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl81MjUxNDU2Nw==,size_16,color_FFFFFF,t_70)



## Docker 命令

```sh
docker version #查看docker版本信息
docker info    #查看docker系统信息，包括镜像信息等
docker 命令 --help #帮助命令
```

`帮助文档`https://docs.docker.com/engine/reference/commandline/cli/

### 镜像命令

##### docker images

```sh
docker images #查看docker全部镜像

[user@localhost ~]$ sudo docker images
REPOSITORY    TAG       IMAGE ID       CREATED         SIZE
hello-world   latest    feb5d9fea6a5   19 months ago   13.3kB

#解释
REPOSITORY #镜像仓库
TAG        #镜像标签
IMAGE ID   #镜像ID
CREATED	   #创建时间
SIZE       #大小
```

##### docker search

```sh
docker search -- #搜索镜像


#手册
Usage:  docker search [OPTIONS] TERM
Search Docker Hub for images
Options:
  -f, --filter filter   Filter output based on conditions provided
      --format string   Pretty-print search using a Go template
      --limit int       Max number of search results
      --no-trunc        Don't truncate output

example:
[user@localhost ~]$ sudo docker search --filter=stars=3000 mysql 
```

##### docker pull

```sh
docker pull -- #下载指定镜像

#手册
Usage:  docker pull [OPTIONS] NAME[:TAG|@DIGEST]
Download an image from a registry
Aliases:
  docker image pull, docker pull
Options:
  -a, --all-tags                Download all tagged images in the repository
      --disable-content-trust   Skip image verification (default true)
      --platform string         Set platform if server is multi-platform capable
  -q, --quiet                   Suppress verbose output


example: 
[user@localhost bin]$ sudo docker pull mysql
Using default tag: latest #tag 默认是latest
latest: Pulling from library/mysql
72a69066d2fe: Pull complete 
93619dbc5b36: Pull complete 
99da31dd6142: Pull complete 
626033c43d70: Pull complete 
37d5d7efb64e: Pull complete 
ac563158d721: Pull complete 
d2ba16033dad: Pull complete 
688ba7d5c01a: Pull complete 
00e060b6d11d: Pull complete 
1c04857f594f: Pull complete 
4d7cfa90e6ea: Pull complete 
e0431212d27d: Pull complete 
Digest: sha256:e9027fe4d91c0153429607251656806cc784e914937271037f7738bd5b8e7709
Status: Downloaded newer image for mysql:latest
docker.io/library/mysql:latest #镜像真实地址

[user@localhost bin]$ sudo docker pull mysql:5.7
5.7: Pulling from library/mysql
72a69066d2fe: Already exists #联合文件系统（在同一个文件系统下的镜像不需要全部下载）
93619dbc5b36: Already exists 
99da31dd6142: Already exists 
626033c43d70: Already exists 
37d5d7efb64e: Already exists 
ac563158d721: Already exists 
d2ba16033dad: Already exists 
0ceb82207cd7: Pull complete 
37f2405cae96: Pull complete 
e2482e017e53: Pull complete 
70deed891d42: Pull complete 
Digest: sha256:f2ad209efe9c67104167fc609cca6973c8422939491c9345270175a300419f94
Status: Downloaded newer image for mysql:5.7
docker.io/library/mysql:5.7

```

##### docker rmi

```sh
docker rmi -- #删除镜像（一般通过镜像id）

#手册
Usage:  docker rmi [OPTIONS] IMAGE [IMAGE...]
Remove one or more images
Aliases:
  docker image rm, docker image remove, docker rmi

Options:
  -f, --force      Force removal of the image
      --no-prune   Do not delete untagged parents

[user@localhost bin]$ sudo docker rmi 3218b38490ce #删除一个
[user@localhost bin]$ sudo docker rmi -f id1 id2 id3 #删除多个
[user@localhost bin]$ sudo docker rmi -f $(sudo docker images -aq)#删除一个
Untagged: mysql:latest
Untagged: mysql@sha256:e9027fe4d91c0153429607251656806cc784e914937271037f7738bd5b8e7709
Deleted: sha256:3218b38490cec8d31976a40b92e09d61377359eab878db49f025e5d464367f3b
Deleted: sha256:aa81ca46575069829fe1b3c654d9e8feb43b4373932159fe2cad1ac13524a2f5
Deleted: sha256:0558823b9fbe967ea6d7174999be3cc9250b3423036370dc1a6888168cbd224d
Deleted: sha256:a46013db1d31231a0e1bac7eeda5ad4786dea0b1773927b45f92ea352a6d7ff9
Deleted: sha256:af161a47bb22852e9e3caf39f1dcd590b64bb8fae54315f9c2e7dc35b025e4e3
Deleted: sha256:feff1495e6982a7e91edc59b96ea74fd80e03674d92c7ec8a502b417268822ff
# 不会删除整个文件系统（联合文件系统思想）
```

##### 镜像加速

`对于使用 systemd 的系统，请在 /etc/docker/daemon.json 中写入如下内容`

```json
{"registry-mirrors":["https://reg-mirror.qiniu.com/"]}
```

`重启服务`

```sh
sudo systemctl daemon-reload
sudo systemctl restart docker
```

##### 更新镜像

`更新镜像之前，我们需要使用镜像来创建一个容器`

```

```





### 容器命令

```sh
# 下载一个centos进行测试
[user@localhost ~]$ sudo docker pull centos
Using default tag: latest
latest: Pulling from library/centos
a1d0c7532777: Pull complete 
Digest: sha256:a27fd8080b517143cbbbab9dfb7c8571c40d67d534bbdee55bd6c473f432b177
Status: Downloaded newer image for centos:latest
docker.io/library/centos:latest
```

##### 运行镜像

```sh
docker run [参数] image

#manual
--name="name"	容器名（区分不同容器）
-d				后台方式运行
-it 			使用交互式运行，进入容器查看内容
-p				指定端口
	-p ip:主机端口
	-p 主机端口：容器端口
	-p 容器端口

-P				随机指定端口

example:
[user@localhost ~]$ sudo docker run -it centos /bin/bash
[root@2973a990302c /]# exit

```

##### 查看已创建的容器

```shell
docker ps [参数]

-a		#列出当前运行的容器 + 历史运行过的容器
-n=?	#列出最近创建的容器
-q		#只显示编号
```



##### 启动已停止运行的容器

```sh
# 先查看之前创建的容器
docker ps -a

[root@localhost etc]# docker ps -a
CONTAINER ID   IMAGE    COMMAND  CREATED       STATUS             		NAMES
7764bd4275d6   ubuntu   "bash"   5 days ago    Exited (0) 5 days ago    ubuntuUser
```

使用 `docker start` 启动一个已停止的容器：

```sh
docker start 7764bd4275d6
```



##### 停止容器

```sh
docker stop <容器id>
```



##### 重启容器

```sh
docker restart <container_id>
```



##### 进入容器

当使用 `-d`参数时，启动的容器会进入后台。若想要进入容器：

- ```bash
  docker attach <container_id>
  ```

- ```sh
  docker exec -it <container_id> /bin/bash
  ```

  `区别 ：attach 进入到容器，当退出时容器会停止; 而 exec 进入则不会`

##### 导出容器

```sh
docker export <container_id> > TestName.tar
```

##### **导入容器快照**

使用 `docker import` 导入镜像

```sh
cat docker/ubuntu.tar | docker import - test/ubuntu:v1
```

```bash
[root@localhost ~]# cat TestName.tar | docker import - test/ubantu:version1.0
sha256:dd4d4aab8854eb93d10d5fcd50bbaddcf1b7014a1435c7293e578b7d673dfebe
[root@localhost ~]# docker images 
REPOSITORY    TAG          IMAGE ID       CREATED          SIZE
test/ubantu   version1.0   dd4d4aab8854   16 seconds ago   1.07GB

```

当然 也可以通过指定 `URL` 进行导入

```bash
docker import http://example.com/exampleimage.tgz example/imagerepo
```

##### 删除容器

删除容器使用 `docker rm` 命令：

```
$ docker rm -f 1e560fca3906
```

##### 端口映射

接下来让我们尝试使用 docker 构建一个 web 应用程序。

我们将在docker容器中运行一个 `Python Flask` 应用来运行一个web应用。

```sh
docker pull training/webapp
docker run -d -P training/webapp python app.py
```

```sh
[root@localhost ~]# docker ps 
CONTAINER ID   IMAGE             COMMAND           CREATED         STATUS         PORTS   
ca447d073d31   training/webapp   "python app.py"   6 seconds ago   Up 6 seconds   0.0.0.0:32768->5000/tcp, :::32768->5000/tcp  
```

可以看到容器信息新增`PORTS`列 `0.0.0.0:32768->5000/tc`代表容器的`5000`端口映射到本机`32768`端口

当然我们也可以手动指定端口`docker run -d -p 5000:5000 training/webapp python app.py`

当我们使用`docker run `时可以指定容器端口

```sh
-p	   指定端口
	-p ip:主机端口
	-p 主机端口：容器端口
	-p 容器端口

-P	   随机指定端口
```

**网络端口的快捷方式**

通过 **docker ps** 命令可以查看到容器的端口映射，**docker** 还提供了另一个快捷方式 **docker port**，使用 **docker port** 可以查看指定 （ID 或者名字）容器的某个确定端口映射到宿主机的端口号。

```sh
docker port <container_name>
```

```bash
docker port <container_id>
```

##### 查看容器日志

```bash
docker logs <container_name/container_id>

# Options
-f --follow 实时输出
-t --timestamps 显示时间戳

```

```sh
      --details        Show extra details provided to logs
  -f, --follow         Follow log output
      --since string   Show logs since timestamp (e.g. "2013-01-02T13:23:37Z") or relative (e.g. "42m" for 42 minutes)
  -n, --tail string    Number of lines to show from the end of the logs (default "all")
  -t, --timestamps     Show timestamps
      --until string   Show logs before a timestamp (e.g. "2013-01-02T13:23:37Z") or relative (e.g. "42m" for 42 minutes)

```

##### 查看容器内进程

```bash
docker top <container_name/container_id>
```

##### 查看容器详细信息

输出结构为一个`JSON`包含该容器详细信息

```bash
docker inspect <container_name/container_id>
```

