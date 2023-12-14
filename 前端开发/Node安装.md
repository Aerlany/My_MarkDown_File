1.安装

### **首先安装必要的环境**

```sh
yum install gcc gcc-c++
```

### **一、直接安装**

```sh
wget https://npm.taobao.org/mirrors/node/v10.14.1/node-v10.14.1-linux-x64.tar.gz
```

然后执行下面命令

```sh
tar -xvf  node-v8.0.0-linux-x64.tar.xz
mv node-v8.1.4-linux-x64 node
```

配置环境变量

```sh
vim /etc/profile
```

在文件中添加，目录写自己的实际目录

```sh
#set for nodejs  
export NODE_HOME=/usr/local/node  
export PATH=$NODE_HOME/bin:$PATH
```

​		生效配置文件

```sh
source /etc/profile
node -v
npm -v
```

### 二、源码编译

```sh
wget https://npm.taobao.org/mirrors/node/v10.13.0/node-v10.13.0.tar.gz
```

解压安装

```sh
tar xvf node-v10.13.0.tar.gz
cd node-v10.13.0/
./configure
make   #这个操作可能会很久
make install
```

### 三、NVM （Node版本管理器）

**1.获取 install.sh**

```sh
//curl
curl -o- https://raw.githubusercontent.com/nvm-sh/nvm/v0.39.1/install.sh | bash
```

```sh
//wget
wget -qO- https://raw.githubusercontent.com/nvm-sh/nvm/v0.39.1/install.sh | bash
```

**2.安装完成提示用户设置环境变量的时候**，修改` (~/.bash_profile, ~/.zshrc, ~/.profile, ~/.bashrc)`其中任意一个

```sh
cd ~
vim .bashrc
```

在末尾加入：

```shell
export NVM_DIR="$HOME/.nvm"
[ -s "$NVM_DIR/nvm.sh" ] && \. "$NVM_DIR/nvm.sh"  # This loads nvm
[ -s "$NVM_DIR/bash_completion" ] && \. "$NVM_DIR/bash_completion"  # This loads nvm bash_completion
```

使配置生效：

```sh
source .bashrc
```

把 nvm 的镜像改成国内的镜像

```sh
export NVM_NODEJS_ORG_MIRROR=https://npm.taobao.org/mirrors/node/
```

```sh
export NVM_IOJS_ORG_MIRROR=http://npm.taobao.org/mirrors/iojs
```

在安装完npm后配置国内的镜像

```sh
npm config set registry=https://registry.npm.taobao.org
```

```sh
//查看是否配置成功
npm config ls
```

**3.使用**

To look over the installed Node vesion:

```
nvm list
```

To download, compile, and install the latest release of node, do this:

```
nvm install node # "node" is an alias for the latest version
```

To install a specific version of node:

```
nvm install 14.7.0 # or 16.3.0, 12.22.1, etc
```

The first version installed becomes the default. New shells will start with the default version of node (e.g., `nvm alias default`).

You can list available versions using `ls-remote`:

```
nvm ls-remote
```

And then in any new shell just use the installed version:

```
nvm use node
```

Or you can just run it:

```
nvm run node --version
```

Or, you can run any arbitrary command in a subshell with the desired version of node:

```
nvm exec 4.2 node --version
```

You can also get the path to the executable to where it was installed:

```
nvm which 12.22
```



### 更换淘宝镜像

**1.使用cnpm**

```shell
npm install -g cnpm --registry=https://registry.npm.taobao.org

cnpm -v
```

不想用cnpm操作，那就直接换npm源

**2.换npm源**

- 单次使用

```sh
npm install --registry=https://registry.npm.taobao.org
```

- 永久使用

```sh
npm config set registry https://registry.npm.taobao.org
```

- 检测是否成功

```sh
#配置后可通过下面方式来验证是否成功
npm config get registry
#或
npm info express
```

​	
 	