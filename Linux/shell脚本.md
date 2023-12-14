# Shell脚本

### 一、执行sh脚本

**Linux 提供的 Shell 解析器有**

```sh
[user@localhost ~]$ cat /etc/shells
/bin/sh
/bin/bash
/usr/bin/sh
/usr/bin/bash
/bin/tcsh
/bin/csh
```

**bash 和 sh 的关系**

```
[user@localhost bin]$ ll | grep bash
-rwxr-xr-x. 1 root root 941880 5 月 11 2016 bash
lrwxrwxrwx. 1 root root	4 5 月 27 2017 sh -> bash
```

```
sh 或 bash命令：新创建一个bash子进程

. 或 ./ ：执行不产生子进程
```

**注**:
前两种方式都是在当前 shell 中打开一个子 shell 来执行脚本内容,当脚本内容结束,则
子 shell 关闭,回到父 shell 中。
第三种,也就是使用在脚本路径前加“.”或者 source 的方式,可以使脚本内容在当前
shell 里执行,而无需打开子 shell!这也是为什么我们每次要修改完/etc/profile 文件以后,需
要 source 一下的原因。
开子 shell 与不开子 shell 的区别就在于,环境变量的继承关系,如在子 shell 中设置的
当前变量,父 shell 是不可见的。

### 二、变量

#### **系统预定义变量**

**常用系统变量**

```
$HOME、$PWD、$SHELL、$USER 等
```

**查看系统变量的值**

```sh
[user@localhost shells]$ echo $HOME
/home/atguigu
```

**显示当前 Shell 中所有变量**:	set

```sh
[user@localhost shells]$ set
BASH=/bin/bash
BASH_ALIASES=()
BASH_ARGC=()
BASH_ARGV=()
```



#### **自定义变量**

**基本语法**

```
(1)定义变量:变量名=变量值,注意,=号前后不能有空格
(2)撤销变量:unset 变量名
(3)声明静态变量:readonly 变量,注意:不能 unset
```

**变量定义规则**

```
(1)变量名称可以由字母、数字和下划线组成,但是不能以数字开头,环境变量名建议大写。
(2)等号两侧不能有空格
(3)在 bash 中,变量默认类型都是字符串类型,无法直接进行数值运算。
(4)变量的值如果有空格,需要使用双引号或单引号括起来。
```

**注意**：

变量默认类型都是字符串类型,无法直接进行数值运算

普通变量使用 export 可以提升到全局变量

readonly 修饰的变量不可以被unset



#### **特殊变量**

1.**$n**
基本语法

```
$n
```

**功能描述**:

n 为数字,$0 代表该脚本名称,$1-$9 代表第一到第九个参数,十以上的参数,十以上的参数需要用大括号包含,如${10}

2.**$#**
基本语法

```
$#
```

**功能描述**:

获取所有输入参数个数,常用于循环,判断参数的个数是否正确以及加强脚本的健壮性。

3.**$*、$@**

$**(功能描述:这个变量代表命令行中所有的参数,$*把所有的参数看成一个整体)
$@ (功能描述:这个变量也代表命令行中所有的参数,不过$@把每个参数区分对待)

4.**$?**
基本语法

```
$? 
```

**功能描述**:

最后一次执行的命令的返回状态。如果这个变量的值为 0,证明上一
个命令正确执行;如果这个变量的值为非 0(具体是哪个数,由命令自己来决定),则证明
上一个命令执行不正确了。

**案例**

```sh
#!/bin/sh
echo '================$n=================='
echo 1st parameter: $1
echo 2nd parameter: $2
echo '================$#=================='
echo $#
echo '================$*=================='
echo $*
echo '================$@================='
echo $@
echo '================$?================='
echo $?

```

```sh
[user@localhost shell脚本]$ ./Parameter.sh ygw yy
================$n==================
1st parameter: ygw
2nd parameter: yy
================$#==================
2
================$*==================
ygw yy
================$@=================
ygw yy
================$?=================
0
```

### 三、运算符

#### 基本语法

```sh
#!/bin/sh
A=$((1+5))
B=$[7+1]
```

**案例**

```sh
[user@localhost shell脚本]$ S=$[(1+2)*3]
[user@localhost shell脚本]$ echo $S
```

### 四、条件判断

#### 1.基本语法

```sh
test condition
```

```sh
[ condition ]
#注意 condition 前后要有空格
```

**注意**:条件非空即为 true,[ ygw ]返回 true,[ ] 返回 false。

#### 2.常用判断条件

**(1)两个整数之间比较**

```
-eq 等于(equal) 
-ne 不等于(not equal)
-lt 小于(less than) 
-le 小于等于(less equal)
-gt 大于(greater than) 
-ge 大于等于(greater equal)
```

注:如果是字符串之间的比较 ,用等号“=”判断相等;用“!=”判断不等。

**(2)按照文件权限进行判断**

```
-r 有读的权限(read)
-w 有写的权限(write)
-x 有执行的权限(execute)
```

**(3)按照文件类型进行判断**

```
-e 文件存在(existence)
-f 文件存在并且是一个常规的文件(file)
-d 文件存在并且是一个目录(directory)
```

**案例**

1.23 是否等于23

```sh
[user@localhost shell脚本]$ [ 23 -eq 23 ]
[user@localhost shell脚本]$ echo $?
0
```

2.HelloWorld.sh 是否具有写权限

```sh
[user@localhost shell脚本]$ [ -w HelloWorld.sh ]
[user@localhost shell脚本]$ echo $?
0
```

3./home/user/text.c 是否存在

```sh
[user@localhost ~]$ [ -e /home/user/text.c ]
[user@localhost ~]$ echo $?
0
```

**注意：**

**多条件判断(&& 表示前一条命令执行成功时,才执行后一条命令,|| 表示上一条命令执行失败后,才执行下一条命令)**

```
[user@localhost ~]$ [ ygw ] && echo OK || echo notOK
OK

[user@localhost ~]$ [ ] && echo OK || echo notOK
notOK

```

### 五、流程控制(重点)

#### 1.if判断

**基本语法**

（1）单分支

```sh
if [condition];then
	语句
fi
```

```sh
if [condition]
then
	语句
fi
```

（2）多分支

```sh
if [condition];then
	语句
elif [condition];then
	语句
else
	语句
fi
```

**注意事项:**
**[ 条件判断式 ],中括号和条件判断式之间必须有空格**
**if 后要有空格**

**案例**

```sh
#!/bin/sh
if [ $# -eq 0 ];then
        echo '请输入参数！！！'
else
        if [ $1 -eq 1 ];then
                 echo '第一个输入的参数是 1'
        elif [ $1 -gt 1 ];then
                 echo '第一个输入的参数大于 1'
        elif [ $1 -lt 1 ];then
                 echo '第一个输入的参数小于 1'
        fi
fi
```

```sh
[user@localhost shell脚本]$ ./If.sh 3
第一个输入的参数大于 1
```

#### 2.case 语句

**基本语法**

```sh
case $变量名 in
"值 1")
如果变量的值等于值 1,则执行程序 1
;;
"值 2")
如果变量的值等于值 2,则执行程序 2
;;
...省略其他分支...
*)
如果变量的值都不是以上的值,则执行此程序
;;
esac
```

**注意事项:**
**(1)case 行尾必须为单词“in”,每一个模式匹配必须以右括号“)”结束。**
**(2)双分号“;;”表示命令序列结束,相当于 java 中的 break。**
**(3)最后的“*)”表示默认模式,相当于 java 中的 default。**

**案例**

```sh
#!/bin/sh
case $1 in
"1")
        echo "first"
;;
"2")
        echo "second"
;;
*)
        echo "NO Parameter"
;;
esac
```



#### 3.for 循环

**基本语法** 1

```sh
for (( 初始值;循环控制条件;变量变化 ))
do
	程序
done
```

**案例**

（从1加到100）

```sh
#!/bin/sh
sum=0
for((i=0;i<=100;i++))
do
        sum=$[$sum+$i]
done
echo $sum
```



**基本语法** 2

```sh
for 变量 in 值 1 值 2 值 3...
do
	程序
done
```

**案例**

（打印所有参数）

```sh
m=1
for j in $@
do
        echo "第$m个参数为$j"
        m=$[$m+1]
done
```

**比较$*和$@区别**

$*和$@都表示传递给函数或脚本的所有参数,不被双引号“”包含时,都以$1 $2 ...$n的形式输出所有参数。

```sh
echo "=========$@=========="
m=1
for j in $@
do
        echo "第$m个参数为$j"
        m=$[$m+1]
done

echo "=========$*=========="
l=1
for k in $*
do
        echo "第$l个参数为$k"
        l=$[$l+1]
done
```

```sh
=========1 2 3 45==========
第1个参数为1
第2个参数为2
第3个参数为3
第4个参数为45
=========1 2 3 45==========
第1个参数为1
第2个参数为2
第3个参数为3
第4个参数为45

```

当它们被双引号“”包含时,$*会将所有的参数作为一个整体,以“$1 $2 ...$n”的形式输出所有参数;$@会将各个参数分开,以“$1” “$2”...“$n”的形式输出所有参数。

```sh
echo "=========$@=========="
m=1
for j in "$@"
do
        echo "第$m个参数为$j"
        m=$[$m+1]
done

echo "=========$*=========="
l=1
for k in "$*"
do
        echo "第$l个参数为$k"
        l=$[$l+1]
done
```

```sh
=========1 2 3 45==========
第1个参数为1
第2个参数为2
第3个参数为3
第4个参数为45
=========1 2 3 45==========
第1个参数为1 2 3 45
```

#### 4.while 循环

**基本语法**

```sh
while [ 条件判断式 ]
do
	程序
done
```

**案例**

（1加到100）

```sh
#!/bin/sh
i=0
sum=0
while [ $i -le 100 ]
do
        sum=$[$sum+$i]
        i=$[$i+1]
done
echo $sum
```

### 六.read 读取控制台输入

**基本语法**

```
read (选项) (参数)
```

**选项**:

```
-p:指定读取值时的提示符;
-t:指定读取值时等待的时间(秒)如果-t 不加表示一直等待
```

**参数**

```
变量:指定读取值的变量名
```

**案例**

提示 7 秒内,读取控制台输入的名称

```sh
#!/bin/sh
read -t 4 -p "Enter your name in 4 seconds:" username
echo $username
```



### 七.函数

#### 系统函数

#### 1.basename

```sh
basename [string / pathname] [suffix]
```

**功能描述:	basename 命令会删掉所有的前缀包括最后一个(‘/’)字符,然后将字符串显示出来。**

**basename 可以理解为取路径里的文件名称**

**选项**:
suffix 为后缀,如果 suffix 被指定了, basename 会将 pathname 或 string 中的 suffix 去掉。



**案例**

```sh
[user@localhost shell脚本]$ basename /home/user/Documents/shell脚本/08_read.sh 
08_read.sh
```

```sh
[user@localhost shell脚本]$ basename /home/user/Documents/shell脚本/08_read.sh .sh
08_read
```

#### 2.dirname

```
dirname 文件绝对路径
```

**功能描述:从给定的包含绝对路径的文件名中去除文件名(非目录的部分),然后返回剩下的路径(目录的部分))**

**dirname 可以理解为取文件路径的绝对路径名称**



**案例**

```sh
[user@localhost shell脚本]$ dirname /home/user/Documents/shell脚本/08_read.sh
/home/user/Documents/shell脚本
```

#### 自定义函数

```sh
function funname()
{
	Action;
	return int;
}
```

**注意：**

(1)必须在调用函数地方之前,先声明函数,shell 脚本是逐行运行。不会像其它语言一样先编译。
(2)函数返回值,只能通过$?系统变量获得,可以显示加:return 返回,如果不加,将以最后一条命令运行结果,作为返回值。return 后跟数值 n(0-255)7

**案例**

两数之和

```sh
#!/bin/sh
function sum()
{
        s=0
        s=$[$1+$2]
        echo "$1 + $2 = $s"
}

read -p "please input a number:" n1
read -p "please input a number:" n2

sum $n1 $n2;
```



### 八.正则表达式

#### **常用特殊字符**

1.**特殊字符:	^**
**^ 匹配一行的开头**

```sh
[user@localhost shell脚本]$ ll | grep ^-rwx
-rwxr--r--. 1 user root      41 Sep 29 21:39 01_HelloWorld.sh
-rwxr--r--. 1 user root     306 Sep 30 09:58 01_Parameter.sh
-rwxr--r--. 1 user root      41 Sep 30 10:04 02_Calculate.sh
-rwxr--r--. 1 user root      31 Sep 30 10:19 03_Compare.sh
-rwxr--r--. 1 user root     350 Sep 30 10:43 04_If.sh
-rwxr--r--. 1 user root     119 Sep 30 10:57 05_Case.sh
-rwxr--r--. 1 user root     297 Sep 30 11:19 06_for.sh
-rwxr--r--. 1 user root     100 Sep 30 11:24 07_while.sh
-rwxr--r--. 1 user root      79 Sep 30 14:07 08_read.sh
-rwxr--r--. 1 user root     177 Sep 30 14:27 09_function.sh
-rw-r--r--. 1 user root   10965 Sep 30 14:32 shell脚本.md
-rw-r--r--. 1 user root 7491598 Sep 29 21:50 笔记.zip
```



2.**特殊字符:	$**
**$ 匹配一行的结束**

```sh
[user@localhost shell脚本]$ ll | grep .sh$
-rwxr--r--. 1 user root      41 Sep 29 21:39 01_HelloWorld.sh
-rwxr--r--. 1 user root     306 Sep 30 09:58 01_Parameter.sh
-rwxr--r--. 1 user root      41 Sep 30 10:04 02_Calculate.sh
-rwxr--r--. 1 user root      31 Sep 30 10:19 03_Compare.sh
-rwxr--r--. 1 user root     350 Sep 30 10:43 04_If.sh
-rwxr--r--. 1 user root     119 Sep 30 10:57 05_Case.sh
-rwxr--r--. 1 user root     297 Sep 30 11:19 06_for.sh
-rwxr--r--. 1 user root     100 Sep 30 11:24 07_while.sh
-rwxr--r--. 1 user root      79 Sep 30 14:07 08_read.sh
-rwxr--r--. 1 user root     177 Sep 30 14:27 09_function.sh
```



3.**特殊字符:	.**
**. 	匹配一个任意的字符**

```sh
[user@localhost shell脚本]$ cat /etc/passwd | grep r..t
```



4.**特殊字符:	***

***不单独使用,他和上一个字符连用,表示匹配上一个字符 0 次或多次**

```
[user@localhost shell脚本]$ cat /etc/passwd | grep r.*t
```

会匹配 rt, rot, root, rooot, roooot 等所有行



5.**字符区间(中括号): [ ]**

[ ] 表示匹配某个范围内的一个字符,例如

```
[6,8]		匹配 6 或者 8
[0-9]		匹配一个 0-9 的数字
[0-9]*		匹配任意长度的数字字符串
[a-z]		匹配一个 a-z 之间的字符
[a-z]*		匹配任意长度的字母字符串
[a-c, e-f]	匹配 a-c 或者 e-f 之间的任意字符
```

```
[user@localhost shell脚本]$ cat /etc/passwd | grep r[a,b,c]*t
```

会匹配 rt,rat, rbt, rabt, rbact,rabccbaaacbt 等等所有行



6.**特殊字符: \\**
**\ 表示转义,并不会单独使用**。由于所有特殊字符都有其特定匹配模式,当我们想匹配某一特殊字符本身时(例如,我想找出所有包含 '$' 的行),就会碰到困难。此时我们就要将转义字符和特殊字符连用,来表示特殊字符本身

```
[user@localhost shell脚本]$ cat /etc/passwd | grep 'a\$b'
```

### 九.补充

生成随机数

$RANDOM

指定范围(生成[1,999]随机数)

$((RANDOM % 1000))

```c
#!/bin/sh
#判断输入参数是否为一个
if [ $# -ne 1 ];then
        echo "携带参数错误！！"
        exit
fi

#从参数中获取目录名
if [ -d $1 ];then
        echo
else
        echo
        echo "目录不存在！！"
        exit
fi
#截取文件夹名`
DIR_NAME=$(basename $1)
DIR_PATH=$(cd $(dirname $1);pwd)

#获取当前时间
DATE=$(date +%Y-%m-%d)

#定义生成的归档文件名称
FILE=archive_${DIR_NAME}_$DATE.tar.gz
DEST=/home/user/Temp/$FILE

#开始
echo "开始归档"
echo

tar -czf $DEST $DIR_PATH/$DIR_NAME

if [ $? -eq 0 ];then
        echo
        echo "归档成功！！"
else
        echo "归档出现问题！！！"
fi

exit
```

