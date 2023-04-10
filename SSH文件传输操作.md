## 在linux下一般用scp这个命令来通过ssh传输文件

## 1、从服务器上下载文件

```
scp username@servername:/path/filename /var/www/local_dir（本地目录）
```

 例如：把192.168.0.101上的/var/www/test.txt 的文件下载到/var/www/local_dir（本地目录）

```
scp root@192.168.0.101:/var/www/test.txt /var/www/local_dir
```



## 2、上传本地文件到服务器

```
scp /path/filename username@servername:/path
```

例如：把本机/var/www/目录下的test.php文件上传到192.168.0.101这台服务器上的/var/www/目录中

```
scp /var/www/test.php root@192.168.0.101:/var/www/
```



## 3、从服务器下载整个目录

```
scp -r username@servername:/var/www/remote_dir/（远程目录） /var/www/local_dir (本地目录)
```

例如：从服务器root@192.168.0.101:/var/www/test下载整个目录到/var/www/

```
scp -r root@192.168.0.101:/var/www/test /var/www/
```

 


## 4、上传目录到服务器

```
scp -r local_dir username@servername:remote_dir
```

例如：把当前目录下的test目录上传到服务器的/var/www/ 目录

```
scp -r test root@192.168.0.101:/var/www/
```

# 二、使用ssh工具对远端服务器进行快捷链接

**生成ssh密钥对**

```sh
 ssh-keygen 
```

**设置远端密钥对**

```sh
ssh-copy-id 用户@127.0.0.1
```

