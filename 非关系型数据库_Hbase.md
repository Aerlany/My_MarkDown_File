### 一、HBase介绍

```
HBase是一个分布式的、面向列的开源数据库,源于Google的一篇论文《BigTable：一个结构化数据的分布式存储系统》。HBase以表的形式存储数据，表有行和列组成，列划分为若干个列族/列簇(column family)。欲了解HBase的官方资讯，请访问[HBase官方网站](http://hbase.apache.org/)。
HBase的运行有三种模式：单机模式、伪分布式模式、分布式模式。
单机模式：在一台计算机上安装和使用HBase，不涉及数据的分布式存储；伪分布式模式：在一台计算机上模拟一个小的集群；分布式模式：使用多台计算机实现物理意义上的分布式存储。这里出于学习目的，我们只重点讨论单机模式和伪分布式模式。
```

本教程运行环境是在Ubuntu-64位系统下（比如Ubuntu18.04，Ubuntu16.04或Ubuntu14.04），HBase版本为hbase-2.2.2，这是目前已经发行的已经编译好的稳定的版本，带有src的文件是未编译的版本，这里我们只要下载bin版本hbase-2.2.2-bin.tar.gz就好了。

1. 如果读者是使用虚拟机方式安装Ubuntu系统的用户，请用虚拟机中的Ubuntu自带firefox浏览器访问本指南，再点击下面的地址，才能把HBase文件下载虚拟机Ubuntu中。请不要使用Windows系统下的浏览器下载，文件会被下载到Windows系统中，虚拟机中的Ubuntu无法访问外部Windows系统的文件，造成不必要的麻烦。
2. 如果读者是使用双系统方式安装Ubuntu系统的用户，请运行Ubuntu系统，在Ubuntu系统打开firefox浏览器访问本指南，再点击下面的地址下载[HBase下载地址](http://archive.apache.org/dist/hbase/)

## 二、安装并配置HBase2.2.2

在安装HBase之前，请确保你的电脑已经安装了Hadoop3.1.3，由于HBase对Hadoop具有版本依赖性，所以，在安装HBase2.2.2时，一定要首先安装Hadoop3.1.3（[查看安装方法](https://dblab.xmu.edu.cn/blog/2441-2/)）。

### 1. HBase2.2.2安装

点击下面的地址下载HBase2.2.2安装文件[HBase官网下载地址](http://archive.apache.org/dist/hbase/)
也可以直接[点击这里从百度云盘下载软件](https://pan.baidu.com/s/1lLjW9cmS1tkBHkrqtpkjWw)（提取码：ziyu）。进入百度网盘后，进入“软件”目录，找到hbase-2.2.2-bin.tar.gz文件，下载到本地。

1.1 解压安装包hbase-2.2.2-bin.tar.gz至路径 /usr/local，命令如下：

```bash
cd ~sudo tar -zxf ~/下载/hbase-2.2.2-bin.tar.gz -C /usr/local
```

Shell 命令

1.2 将解压的文件名hbase-2.2.2改为hbase，以方便使用，命令如下：

```bash
cd /usr/localsudo mv ./hbase-2.2.2 ./hbase
```

Shell 命令

下面把hbase目录权限赋予给hadoop用户：

```bash
cd /usr/localsudo chown -R hadoop ./hbase
```

Shell 命令

1.3 配置环境变量
将hbase下的bin目录添加到path中，这样，启动hbase就无需到/usr/local/hbase目录下，大大的方便了hbase的使用。教程下面的部分还是切换到了/usr/local/hbase目录操作，有助于初学者理解运行过程，熟练之后可以不必切换。
编辑~/.bashrc文件

```bash
vim ~/.bashrc
```

Shell 命令

如果没有引入过PATH请在~/.bashrc文件尾行添加如下内容：

```shell
export PATH=$PATH:/usr/local/hbase/bin
```

Shell

如果已经引入过PATH请在export PATH这行追加/usr/local/hbase/bin，这里的“：”是分隔符。如下图：
![配置环境变量](https://dblab.xmu.edu.cn/blog/wp-content/uploads/2016/01/%E5%BC%95%E5%85%A5%E7%8E%AF%E5%A2%83%E5%8F%98%E9%87%8F.png)
编辑完成后，再执行source命令使上述配置在当前终端立即生效，命令如下：

```bash
source ~/.bashrc
```

Shell 命令

扩展阅读: [设置Linux环境变量的方法和区别](https://dblab.xmu.edu.cn/blog/linux-environment-variable/)
1.4 添加HBase权限

```bash
cd /usr/localsudo chown -R hadoop ./hbase       #将hbase下的所有文件的所有者改为hadoop，hadoop是当前用户的用户名。
```

Shell 命令

1.5 查看HBase版本，确定hbase安装成功,命令如下：

```bash
/usr/local/hbase/bin/hbase version
```

Shell 命令

看到输出版本消息表示HBase已经安装成功，接下来将分别进行HBase单机模式和伪分布式模式的配置。

### 2. HBase配置

HBase有三种运行模式，单机模式、伪分布式模式、分布式模式。作为学习，我们重点讨论单机模式和伪分布式模式。
以下先决条件很重要，比如没有配置JAVA_HOME环境变量，就会报错。
\- jdk
\- Hadoop( 单机模式不需要，伪分布式模式和分布式模式需要)
\- SSH

以上三者如果没有安装，请回到[Hadoop3.1.3的安装](https://dblab.xmu.edu.cn/blog/2441-2/)参考如何安装。

#### 2.1单机模式配置

\1. 配置/usr/local/hbase/conf/hbase-env.sh 。配置JAVA环境变量，并添加配置HBASE_MANAGES_ZK为true，用vi命令打开并编辑hbase-env.sh，命令如下：

```bash
vim /usr/local/hbase/conf/hbase-env.sh
```

Shell 命令

配置JAVA环境变量。如果你之前已经按照本网站[Hadoop安装教程](https://dblab.xmu.edu.cn/blog/2441-2/)安装Hadoop3.1.3，则已经安装了JDK1.8。JDK的安装目录是/usr/lib/jvm/jdk1.8.0_162， 则JAVA _HOME =/usr/lib/jvm/jdk1.8.0_162；配置HBASE_MANAGES_ZK为true，表示由hbase自己管理zookeeper，不需要单独的zookeeper。hbase-env.sh中本来就存在这些变量的配置，大家只需要删除前面的#并修改配置内容即可(#代表注释)：

```shell
export JAVA_HOME=/usr/lib/jvm/jdk1.8.0_162export HBASE_MANAGES_ZK=true 
```

Shell

添加完成后保存退出即可。

\2. 配置/usr/local/hbase/conf/hbase-site.xml
打开并编辑hbase-site.xml，命令如下：

```bash
vim /usr/local/hbase/conf/hbase-site.xml
```

Shell 命令

在启动HBase前需要设置属性hbase.rootdir，用于指定HBase数据的存储位置，因为如果不设置的话，hbase.rootdir默认为/tmp/hbase-${user.name},这意味着每次重启系统都会丢失数据。此处设置为HBase安装目录下的hbase-tmp文件夹即（/usr/local/hbase/hbase-tmp）,添加配置如下：

```xml
<configuration>        <property>                <name>hbase.rootdir</name>                <value>file:///usr/local/hbase/hbase-tmp</value>        </property></configuration>
```

XML

\3. 接下来测试运行。首先切换目录至HBase安装目录/usr/local/hbase；再启动HBase。命令如下：

```bash
cd /usr/local/hbasebin/start-hbase.shbin/hbase shell
```

Shell 命令

上述三条命令中，sudo bin/start-hbase.sh用于启动HBase，bin/hbase shell用于打开shell命令行模式，用户可以通过输入shell命令操作HBase数据库。
成功启动HBase，截图如下：

![img](https://dblab.xmu.edu.cn/blog/wp-content/uploads/2020/01/HBASE-SHELL-2-2-2.jpg)

停止HBase运行,命令如下：

```bash
bin/stop-hbase.sh
```

Shell 命令

注意：如果在操作HBase的过程中发生错误，可以通过{HBASE_HOME}目录（/usr/local/hbase）下的logs子目录中的日志文件查看错误原因。

#### 2.2 伪分布式模式配置

1.配置/usr/local/hbase/conf/hbase-env.sh。命令如下：

```bash
vim /usr/local/hbase/conf/hbase-env.sh
```

Shell 命令

配置JAVA_HOME，HBASE_CLASSPATH，HBASE_MANAGES_ZK.
HBASE_CLASSPATH设置为本机HBase安装目录下的conf目录（即/usr/local/hbase/conf）

```shell
export JAVA_HOME=/usr/lib/jvm/jdk1.8.0_162export HBASE_CLASSPATH=/usr/local/hbase/conf export HBASE_MANAGES_ZK=true
```

Shell

2.配置/usr/local/hbase/conf/hbase-site.xml
用命令vi打开并编辑hbase-site.xml，命令如下：

```bash
vim /usr/local/hbase/conf/hbase-site.xml
```

Shell 命令

修改hbase.rootdir，指定HBase数据在HDFS上的存储路径；将属性hbase.cluter.distributed设置为true。假设当前Hadoop集群运行在伪分布式模式下，在本机上运行，且NameNode运行在9000端口。

```xml
<configuration>        
    <property>               
        <name>hbase.rootdir</name> 
        <value>hdfs://localhost:9000/hbase</value>        
    </property>        
    <property>                
        <name>hbase.cluster.distributed</name>    
        <value>true</value>     
    </property>      
    <property>      
        <name>hbase.unsafe.stream.capability.enforce</name>  
        <value>false</value>  
    </property>
</configuration>
```

XML

hbase.rootdir指定HBase的存储目录；hbase.cluster.distributed设置集群处于分布式模式.
另外，上面配置文件中，hbase.unsafe.stream.capability.enforce这个属性的设置，是为了避免出现启动错误。也就是说，如果没有设置hbase.unsafe.stream.capability.enforce为false，那么，在启动HBase以后，会出现无法找到HMaster进程的错误，启动后查看系统启动日志（/usr/local/hbase/logs/hbase-hadoop-master-ubuntu.log），会发现如下错误：

```
2020-01-25 15:04:56,916 ERROR [master/localhost:16000:becomeActiveMaster] master.HMaster: Failed to become active master
java.lang.IllegalStateException: The procedure WAL relies on the ability to hsync for proper operation during component failures, but the underlying filesystem does not support doing so. Please check the config value of 'hbase.procedure.store.wal.use.hsync' to set the desired level of robustness and ensure the config value of 'hbase.wal.dir' points to a FileSystem mount that can provide it.
```

\3. 接下来测试运行HBase。
第一步：首先登陆ssh，之前设置了无密码登陆，因此这里不需要密码；再切换目录至/usr/local/hadoop ；再启动hadoop，如果已经启动hadoop请跳过此步骤。命令如下：

```bash
ssh localhostcd /usr/local/hadoop./sbin/start-dfs.sh
```

Shell 命令

输入命令jps，能看到NameNode,DataNode和SecondaryNameNode都已经成功启动，表示hadoop启动成功，截图如下：
![hadoop jps](https://dblab.xmu.edu.cn/blog/wp-content/uploads/2016/01/hadoop-jps.png)

第二步：切换目录至/usr/local/hbase;再启动HBase.命令如下：

```bash
cd /usr/local/hbasebin/start-hbase.sh
```

Shell 命令

启动成功，输入命令jps，看到以下界面说明hbase启动成功
![hbase jps](https://dblab.xmu.edu.cn/blog/wp-content/uploads/2016/01/hbase-jps.png)
进入shell界面：

```bash
bin/hbase shell
```

Shell 命令

截图如下：
![hbase shell](https://dblab.xmu.edu.cn/blog/wp-content/uploads/2016/01/hbase-shell.png)

4.停止HBase运行,命令如下：

```bash
bin/stop-hbase.sh
```

Shell 命令

注意：如果在操作HBase的过程中发生错误，可以通过{HBASE_HOME}目录（/usr/local/hbase）下的logs子目录中的日志文件查看错误原因。
这里启动关闭Hadoop和HBase的顺序一定是：
启动Hadoop—>启动HBase—>关闭HBase—>关闭Hadoop

## 三、 编程实践

### 1. 利用Shell命令

#### 1.1 HBase中创建表

HBase中用create命令创建表，具体如下：

```bash
  create 'student','Sname','Ssex','Sage','Sdept','course'
```

Shell 命令

命令执行截图如下：
![img](https://dblab.xmu.edu.cn/blog/wp-content/uploads/2015/09/%E9%80%89%E5%8C%BA_007.png)

此时，即创建了一个“student”表，属性有：Sname,Ssex,Sage,Sdept,course。因为HBase的表中会有一个系统默认的属性作为行键，无需自行创建，默认为put命令操作中表名后第一个数据。创建完“student”表后，可通过describe命令查看“student”表的基本信息。命令执行截图如下：
![img](https://dblab.xmu.edu.cn/blog/wp-content/uploads/2015/09/%E9%80%89%E5%8C%BA_008.png)

#### 1.2 HBase数据库基本操作

本小节主要介绍HBase的增、删、改、查操作。在添加数据时，HBase会自动为添加的数据添加一个时间戳，故在需要修改数据时，只需直接添加数据，HBase即会生成一个新的版本，从而完成“改”操作，旧的版本依旧保留，系统会定时回收垃圾数据，只留下最新的几个版本，保存的版本数可以在创建表的时候指定。

- 添加数据
  HBase中用put命令添加数据，注意：一次只能为一个表的一行数据的一个列，也就是一个单元格添加一个数据，所以直接用shell命令插入数据效率很低，在实际应用中，一般都是利用编程操作数据。
  当运行命令：put ‘student’,’95001’,’Sname’,’LiYing’时，即为student表添加了学号为95001，名字为LiYing的一行数据，其行键为95001。

```bash
put 'student','95001','Sname','LiYing'
```

Shell 命令

命令执行截图如下，即为student表添加了学号为95001，名字为LiYing的一行数据，其行键为95001。
![插入数据](https://dblab.xmu.edu.cn/blog/wp-content/uploads/2016/01/%E6%8F%92%E5%85%A5%E6%95%B0%E6%8D%AE.png)

```bash
  put 'student','95001','course:math','80'
```

Shell 命令

命令执行截图如下，即为95001行下的course列族的math列添加了一个数据。
![img](https://dblab.xmu.edu.cn/blog/wp-content/uploads/2015/09/%E9%80%89%E5%8C%BA_011.png)

- 删除数据

在HBase中用delete以及deleteall命令进行删除数据操作，它们的区别是：1. delete用于删除一个数据，是put的反向操作；2. deleteall操作用于删除一行数据。

\1. delete命令

```bash
  delete 'student','95001','Ssex'
```

Shell 命令

命令执行截图如下， 即删除了student表中95001行下的Ssex列的所有数据。
![img](https://dblab.xmu.edu.cn/blog/wp-content/uploads/2015/09/%E9%80%89%E5%8C%BA_014.png)

\2. deleteall命令

```bash
  deleteall 'student','95001'
```

Shell 命令

命令执行截图如下，即删除了student表中的95001行的全部数据。
![img](https://dblab.xmu.edu.cn/blog/wp-content/uploads/2015/09/%E9%80%89%E5%8C%BA_015.png)

- 查看数据
  HBase中有两个用于查看数据的命令：1. get命令，用于查看表的某一行数据；2. scan命令用于查看某个表的全部数据

\1. get命令

```bash
  get 'student','95001'
```

Shell 命令

命令执行截图如下， 返回的是‘student’表‘95001’行的数据。
![img](https://dblab.xmu.edu.cn/blog/wp-content/uploads/2015/09/%E9%80%89%E5%8C%BA_012.png)

\2. scan命令

```bash
  scan 'student'
```

Shell 命令

命令执行截图如下， 返回的是‘student’表的全部数据。
![img](https://dblab.xmu.edu.cn/blog/wp-content/uploads/2015/09/%E9%80%89%E5%8C%BA_013.png)

- 删除表
  删除表有两步，第一步先让该表不可用，第二步删除表。

```bash
disable 'student'  drop 'student'
```

Shell 命令

命令执行截图如下：
![删除表](https://dblab.xmu.edu.cn/blog/wp-content/uploads/2016/01/%E5%88%A0%E9%99%A4%E8%A1%A8.png)

#### 1.3 查询表历史数据

查询表的历史版本，需要两步。
1、在创建表的时候，指定保存的版本数（假设指定为5）

```bash
  create 'teacher',{NAME=>'username',VERSIONS=>5}
```

Shell 命令

2、插入数据然后更新数据，使其产生历史版本数据，注意：这里插入数据和更新数据都是用put命令

```bash
put 'teacher','91001','username','Mary'put 'teacher','91001','username','Mary1'put 'teacher','91001','username','Mary2'put 'teacher','91001','username','Mary3'put 'teacher','91001','username','Mary4'  put 'teacher','91001','username','Mary5'
```

Shell 命令

3、查询时，指定查询的历史版本数。默认会查询出最新的数据。（有效取值为1到5）

```bash
  get 'teacher','91001',{COLUMN=>'username',VERSIONS=>5}
```

Shell 命令

查询结果截图如下：
![查看历史数据](https://dblab.xmu.edu.cn/blog/wp-content/uploads/2016/01/%E6%9F%A5%E7%9C%8B%E5%8E%86%E5%8F%B2%E6%95%B0%E6%8D%AE.png)

#### 1.4 退出HBase数据库表操作

最后退出数据库操作，输入exit命令即可退出，注意：这里退出HBase数据库是退出对数据库表的操作，而不是停止启动HBase数据库后台运行。

### 2. 表操作

#### 2.1创建表

命令格式1：create ‘表名’,‘列簇名1’,‘列簇名2’…
命名格式2：create ‘表名’,{NAME=>‘列簇名1’},{NAME=>‘列簇名2’}…

```sql
#创建一张名为Student的表，包含基本信息（baseinfo）、学校信息（schoolinfo）两个列簇
create 'student','haseinfo','schoolinfo'
```

#### 2.2 删除表

```sql
#删除表前需要先禁用表
disable 'student'
#删除表
drop 'student'
```

#### 2.3 修改表

```sql
snapshot 'student','temp'
clone_snapshot 'temp','stu'
delect_snapshot 'temp'
```

#### 2.4 查看所有表

```sql
list
```

#### 2.5 查看表的基本信息

```sql
desc 'Student'
```

#### 2.6 检查表是否存在

```sql
exists 'student'
```

#### 2.7 表的启用或禁用

```sql
#禁用表
disable 'student'
#检查表是否被禁用
is_disabled 'student'
#启用表
enable 'student'
#检查表是否被启用
is_enabled 'student'
```

### 3. 增删改

#### 3.1 添加列簇

命令格式：alter ‘表名’,‘列簇名’

```sql
alter 'student','teacherinfo'
```

#### 3.2 删除列簇

命令格式：alter ‘表名’,{NAME=>‘列簇名’,METHOD=‘delete’}

```sql
alter 'student', {NAME => 'teacherinfo', METHOD => 'delete'}
```

#### 3.3 更改列簇存储版本限制

默认情况下列族只存储一个版本的数据，如果需要存储多个版本的数据，则需要修改列族的属性。修改后可通过 desc 命令查看。

```sql
alter 'student',{NAME=>'baseinfo',VERSIONS=>3}
```

#### 3.4 插入数据

命令格式：put ‘表名’,‘行键’,‘列簇名:列名’,‘值’[,时间戳]

```sql
put 'student', '1','baseinfo:name','tom'
put 'student', '1','baseinfo:birthday','1990-01-09'
put 'student', '1','baseinfo:age','29'
put 'student', '1','schoolinfo:name','Havard'
put 'student', '1','schoolinfo:localtion','Boston'

put 'student', '2','baseinfo:name','jack'
put 'student', '2','baseinfo:birthday','1998-08-22'
put 'student', '2','baseinfo:age','21'
put 'student', '2','schoolinfo:name','yale
```

#### 3.5获取指定行、指定行中的列族、列的信息

###### 3.5.1 get

```sql
# 获取指定行中所有列的数据信息
get 'student','3'
# 获取指定行中指定列族下所有列的数据信息
get 'student','3','baseInfo'
# 获取指定行中指定列的数据信息
get 'student','3','baseinfo:name'
```

###### 3.5.2 scan

```sql
#查询整表数据
scan 'student'
#查询指定列簇的数据
scan 'student', {COLUMN=>'baseinfo'}
# 查询指定列的数据
scan 'student', {COLUMNS=> 'baseinfo:birthday'}
# 查看指定列两个版本的数据(3.3中我们设置了3个版本)
scan 'student', {COLUMNS=> 'baseinfo:birthday',VERSIONS=>2}
# 查看前3条数据
scan 'student',{LIMIT=>3}
```

#### 3.6 删除指定行、指定行中的列

```sql
# 删除指定行
delete 'student','3'
# 删除指定行中指定列的数据
delete 'student','3','baseinfo:name'
```

