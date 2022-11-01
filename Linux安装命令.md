**Linux软件安装方式：**

1.apt，rpm，yum

2.源代码安装

3.二进制安装

## 一、apt，rpm，yum软件安装方式

***\*apt(Advancd Packaging Tool)\****高级包装工具，软件包管理器

例，apt-get isntall w3m

当你在执行安装操作时，首先apt-get 工具会在本地的一个数据库中搜索关于 w3m 软件的相关信息，并根据这些信息在相关的服务器上下载软件安装，这里大家可能会一个疑问：既然是在线安装软件，为啥会在本地的数据库中搜索？要解释这个问题就得提到几个名词了：

① 软件源镜像服务器

② 软件源

我们需要定期从服务器上下载一个软件包列表，使用 sudo apt-get update 命令来保持本地的软件包列表是最新的（有时你也需要手动执行这个操作，比如更换了软件源），而这个表里会有软件依赖信息的记录，对于软件依赖，我举个例子：我们安装 w3m 软件的时候，而这个软件需要 libgc1c2 这个软件包才能正常工作，这个时候 apt-get 在安装软件的时候会一并替我们安装了，以保证 w3m 能正常的工作。

### ***\*1、APT方式（apt是Ubuntu的软件包管理工具）\****

（1）普通安装：apt-get install softname1 softname2 …;

（2）修复安装：apt-get -f install softname1 softname2... ;(-f 是用来修复损坏的依赖关系)

（3）重新安装：apt-get --reinstall install softname1 softname2...;

***\*Ubuntu中软件包的卸载方法\****

APT方式

（1）移除式卸载：apt-get remove softname1 softname2 …;（移除软件包，当包尾部有+时，意为安装）

（2）清除式卸载 ：apt-get --purge remove softname1 softname2...;(同时清除配置)

（3） 清除式卸载：apt-get purge sofname1 softname2...;(同上，也清除配置文件)

**常用参数：**

-y 自动回应是否安装软件包，在一些自动化脚本中经常用到

-s 模拟安装

-q 静默安装

-f 修复损坏的依赖关系

-- reinstall 重新安装已经安装但可能存在问题的软件包

-- install-suggests 同时安装APT给出的建议安装的软件包

apt-get包含的常用工具：

update  从软件源镜像服务器上下载/更新用于更新本地软件源的软件包

upgrade  升级本地可更新的全部软件包，但存在依赖问题时将不会升级，通常会在更新之前执行一次update

purge  与remove相同，但会完全移除软件包，包含其配置文件

autoremove  移除之前被其他软件包依赖，但现在不再被使用的软件包

### ***\*常用的APT命令:\****

***\*apt-cache search package 搜索包\****

apt-cache show package 获取包的相关信息，如说明、大小、版本等

apt-cache depends package 了解使用依赖

apt-cache rdepends package 查看该包被哪些包依赖

sudo apt-get install package 安装包，apt会自动下载安装，若有依赖性软件包，apt也会自动下载安装

***\*sudo apt-get install package --reinstall 重新安装包\****

sudo apt-get -f install 修复安装"-f = --fix-missing"

***\*sudo apt-get remove package 删除包，如有依赖的软件包，则会一并移除\****

***\*sudo apt-get remove package --purge 删除包，包括删除配置文件等\****

***\*sudo apt-get update 更新源\****（该指令是用来取得记录在 /etc/apt/sources.list 内的远端服务器的软件包清单，在使用apt-get dist-upgrade指令升级软件前，一定要记得先用此指令将软件包清单更新）

sudo apt-get upgrade 更新已安装的软件包

sudo apt-get dist-upgrade 升级系统

sudo apt-get dselect-upgrade 使用 dselect 升级

sudo apt-get build-dep package 安装相关的编译环境

apt-get source package 下载该包的源代码

sudo apt-get clean && sudo apt-get autoclean 清理无用的包（当使用 apt-get install 指令安装后，下载的软件包会放置在 /var/cache/apt/archives，使用apt-get clean指令可将其删除）

sudo apt-get check 检查是否有损坏的依赖

### ***\*2、rpm（Red Hat Linux软件包管理工具）\****

rpm原本是Red Hat Linux发行版专门用来管理Linux各项套件的程序

语法：

```
rpm [选项] [软件包]

常用选项：

-a：查询所有套件； 

-b<完成阶段><套件档>+或-t <完成阶段><套件档>+：设置包装套件的完成阶段，并指定套件档的文件名称； 

-c：只列出组态配置文件，本参数需配合"-l"参数使用； 

-d：只列出文本文件，本参数需配合"-l"参数使用； 

-e<套件档>或--erase<套件档>：删除指定的套件； 

-f<文件>+：查询拥有指定文件的套件； 

-h或--hash：套件安装时列出标记； -i：显示套件的相关信息； 

-i<套件档>或--install<套件档>：安装指定的套件档； 

-l：显示套件的文件列表； 

-p<套件档>+：查询指定的RPM套件档； 

-q：使用询问模式，当遇到任何问题时，rpm指令会先询问用户； 

-R：显示套件的关联性信息； 

-s：显示文件状态，本参数需配合"-l"参数使用； 

-U<套件档>或--upgrade<套件档>：升级指定的套件档； 

-v：显示指令执行过程； 

-vv：详细显示指令执行过程，便于排错。
```

------

**1.安装**

rpm -ivh example.rpm 	安装 example.rpm 包并在安装过程中显示正在安装的文件信息及安装进度；

------

**2.查询**

RPM 查询操作

命令：

rpm -q …

附加查询命令：

a 查询所有已经安装的包以下两个附加命令用于查询安装包的信息；

i 显示安装包的信息；

l 显示安装包中的所有文件被安装到哪些目录下；

s 显示安装版中的所有文件状态及被安装到哪些目录下；以下两个附加命令用于指定需要查询的是安装包还是已安装后的文件；

p 查询的是安装包的信息；

f 查询的是已安装的某文件信息；

例，rpm -qa | grep tomcat4 查看 tomcat4 是否被安装；

------

**3.RPM 卸载操作**

命令：

rpm -e 需要卸载的安装包

在卸载之前，通常需要使用rpm -q …命令查出需要卸载的安装包名称。

举例如下：

rpm -e tomcat4 卸载 tomcat4 软件包；

------

**4.RPM 升级操作**

命令：

rpm -U 需要升级的包

举例如下：

rpm -Uvh example.rpm 升级 example.rpm 软件包；

 

***\*注意：\****但是rpm软件包之间的依赖性问题往往会很繁琐,尤其是软件由多个rpm包组成时。所以很多情况下我们出于方便，选择使用yum包管理器来进行安装。Yum（全称为 Yellow dog Updater, Modified）是一个在Fedora和RedHat以及SUSE中的Shell前端软件包管理器。基于RPM包管理，能够从指定的服务器（例如淘宝镜像、腾讯云、网易镜像等，可自己配置）自动下载RPM包并且安装，可以自动处理软件包的依赖关系，一次安装所有依赖的软体包，无须繁琐地一次次下载、安装。



### ***\*3、yum(Yellow dog Updater, Modified）：\****

yum命令是在Fedora和RedHat以及SUSE中基于rpm的软件包管理器，它可以使系统管理人员交互和自动化地更细与管理RPM软件包，能够从指定的服务器自动下载RPM包并且安装，可以自动处理依赖性关系，并且一次安装所有依赖的软体包，无须繁琐地一次次下载、安装。

***\*yum和rpm的区别：\****

```
①   rpm软件包形式的管理虽然方便，但是需要手工解决软件包的依赖关系。很多时候安装一个软件安装一个软件需要安装1个或者多个其他软件，手动解决时，很复杂，yum解决这些问题。Yum是rpm的前端程序，主要目的是设计用来自动解决rpm的依赖关系，其特点：

1） 自动解决依赖关系；2）可以对rpm进行分组，基于组进行安装操作；3）引入仓库概念，支持多个仓库；4）配置简单

②   yum仓库用来存放所有的现有的.rpm包，当使用yum安装一个rpm包时，需要依赖关系，会自动在仓库中查找依赖软件并安装。仓库可以是本地的，也可以是HTTP、FTP、nfs形式使用的集中地、统一的网络仓库。

③   仓库的配置文件/etc/yum.repos.d目录下
```

------

**1.安装：**

yum install package1 #安装指定的安装包package1

------

**2.更新和升级：**

yum update #全部更新 

yum update package1 #更新指定程序包package1 

yum check-update #检查可更新的程序 

yum upgrade package1 #升级指定程序包package1 

yum groupupdate group1 #升级程序组group1

**3.卸载：**

------

yum remove package1

**4.清除缓存:**

yum clean packages #清除缓存目录下的软件包 

yum clean headers #清除缓存目录下的 headers 

yum clean oldheaders #清除缓存目录下旧的 headers

------

**5.查找和显示:**

yum info package1 #显示安装包信息package1 

yum list #显示所有已经安装和可以安装的程序包 

yum list package1 #显示指定程序包安装情况package1 

yum groupinfo group1 #显示程序组group1信息yum search string 根据关键字string查找安装包

## 二、源代码安装方式：

源码安装（.tar、tar.gz、tar.bz2、tar.Z）

首先解压缩源码压缩包然后通过tar命令来完成

```
解xx.tar.gz：
tar zxf xx.tar.gz 

解xx.tar.Z：
tar zxf xx.tar.Z 

解xx.tgz：
tar zxf xx.tgz 

解xx.bz2：
bunzip2 xx.bz2 

解xx.tar：
tar xf xx.tar
```

然后进入到解压出的目录中，建议先读一下README之类的说明文件，因为此时不同源代码包或者预编译包可能存在差异，然后建议使用ls -F --color或者ls -F命令（实际上我的只需要 l 命令即可）查看一下可执行文件，可执行文件会以*号的尾部标志。

一般依次执行：

```
./configure （检查编译环境）

make （对源代码进行编译）

sudo make install （将生成的可执行文件安装到当前计算机中）

make clean (选择执行，主要是用来清除一些临时文件)

即可完成安装。
```

***\*解释：\****

1、configure，这一步一般用来生成 Makefile，为下一步的编译做准备，你可以通过在 configure 后加上参数来对安装进行控制，比如代码:./configure –prefix=/usr 意思是将该软件安装在 /usr 下面，执行文件就会安装在 /usr/bin （而不是默认的 /usr/local/bin),资源文件就会安装在 /usr/share（而不是默认的/usr/local/share）。同时一些软件的配置文件你可以通过指定 –sys-config= 参数进行设定。有一些软件还可以加上 –with、–enable、–without、–disable 等等参数对编译加以控制，你可以通过允许 ./configure –help 察看详细的说明帮助。

2、make，这一步就是编译，大多数的源代码包都经过这一步进行编译（当然有些perl或python编写的软件需要调用perl或python来进行编译）。如果 在 make 过程中出现 error ，你就要记下错误代码（注意不仅仅是最后一行），然后你可以向开发者提交 bugreport（一般在 INSTALL 里有提交地址），或者你的系统少了一些依赖库等，这些需要自己仔细研究错误代码。

3、make insatll，这条命令来进行安装（当然有些软件需要先运行 make check 或 make test 来进行一些测试），这一步一般需要你有 root 权限（因为要向系统写入文件）。

## 三、二进制安装：

二进制包的安装比较简单，我们需要做的只是将从网络上下载的二进制包解压后放到合适的目录，然后将包含可执行的主程序文件的目录添加进PATH环境变量即可，如果你不知道该放到什么位置，请重新复习关于 Linux 目录结构的内容。

 

 