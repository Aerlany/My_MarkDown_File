

## **MySQL** **常用命令**

### 1、创建数据库

```sql
create database 数据库名;
```

### 2、删除数据库

```sql
drop database 数据库名;
```

### 3、创建数据表

```sql
create table 表名(
	字段一	数据类型一  其它,
	字段二	数据类型二	其它,
......)
```

***其它可以设置为：***

***primary key（主键）***

***auto_increment（自增）***

***unique（不重复）***

***not null***



#### **数据类型**

| 类型         | 用途             |
| :----------- | :--------------- |
| TINYINT      | 小整数值         |
| SMALLINT     | 大整数值         |
| MEDIUMINT    | 大整数值         |
| INT或INTEGER | 大整数值         |
| BIGINT       | 极大整数值       |
| FLOAT        | 单精度  浮点数值 |
| DOUBLE       | 双精度  浮点数值 |

#### 日期和时间类型

| 类型      | 格式                        | 用途                     |
| --------- | :-------------------------- | ------------------------ |
| DATE      | YYYY-MM-DD                  | 日期值                   |
| TIME      | HH:MM:SS                    | 时间值或持续时间         |
| YEAR      | YYYY                        | 年份值                   |
| DATETIME  | YYYY-MM-DD 		HH:MM:SS | 混合日期和时间值         |
| TIMESTAMP | YYYYMMDD 		HHMMSS     | 混合日期和时间值，时间戳 |

#### 字符串类型

| 类型       | 用途                                    |
| ---------- | --------------------------------------- |
| CHAR       | 定长字符串                              |
| VARCHAR    | 变长字符串                              |
| TINYBLOB   | 不超过 255 		个字符的二进制字符串 |
| TINYTEXT   | 短文本字符串                            |
| BLOB       | 二进制形式的长文本数据                  |
| TEXT       | 长文本数据                              |
| MEDIUMBLOB | 二进制形式的中等长度文本数据            |
| MEDIUMTEXT | 中等长度文本数据                        |
| LONGBLOB   | 二进制形式的极大文本数据                |
| LONGTEXT   | 极大文本数据                            |

 

### 4、 删除数据表

```sql
drop table 表名;
```

### 5、变更数据表数据

#### **更新数据表数据**

```sql
update 表名 set 字段一 = 新值, 字段二 = 新值 where 字段名 = 想要修改的字段;
```



#### **删除数据表数据**

```sql
delete from 表名 where 字段名 = 想要的字段值;
```



#### **添加数据表数据**

```sql
insert into 表名(字段一, 字段二, 字段三, ......) values (值一, 值二, 值三,....);
```

**注意**： 

1.当字段名不限定时，添加值的数量和类型需要对应表的字段

2.值可以添加多条，之间使用, 隔开

 

### 6、修改数据表

#### 	（**修改数据表名称**）

```sql
alter table 表名 rename to 新表名;
```

​	

#### （**修改数据表的字符集**）

```sql
alter table 表名 character set 字符集名;
```

​	

#### （**数据表添加列**）	

```sql
alter table 表名 add 列名 数据类型 其它;
```

```sql
ALTER TABLE <表名> ADD <新字段名> <数据类型> [约束条件] [FIRST|AFTER 已存在的字段名]；
```

`FIRST` 为可选参数，其作用是将新添加的字段设置为表的第一个字段；`AFTER` 为可选参数，其作用是将新添加的字段添加到指定的`已存在的字段名`的后面。

#### （**修改数据表某一列的数据类型**）

```sql
alter table 表名 modify 列名 新数据类型;
```

​	

#### （**修改数据表某一列的所有信息**）

```sql
alter table 表名 change 列名 新列名 新数据类型 其它;
```

​	**注**：该方法不会保留老一列除了主键外的任何数据。

​	

#### （**删除一列**）

```sql
alter table 表名 drop 列名;
```

### 7、 查询数据表

#### **（查询所有）**

```sql
select * from 表名;
```

 

#### **（查询指定列）**

```sql
select 列名1, 列名2, 列名3 from 表名;
```

 

#### **（去重列查询）**

```sql
select distinct * from 表名;
```

 

#### **（起别名的查询）**

```sql
select 列名 as 指定名 from 表名;
```

 

#### **（聚合函数查询）**

```sql
select 聚合函数(列名) from 表名;
```

**注**：

*count()		统计数量，不统计NULL值*

*max()		最大值*

*min()		最小值*

*sum()		求和*

*avg()			求平均值*

 

#### **（条件查询）**

```sql
select * from 表名 where 查询条件;
```

| 操作符 | 描述                                                         | 实例                 |
| ------ | ------------------------------------------------------------ | -------------------- |
| =      | 等号，检测两个值是否相等，如果相等返回true                   | (A = B) 返回false。  |
| <>, != | 不等于，检测两个值是否相等，如果不相等返回true               | (A != B) 返回 true。 |
| >      | 大于号，检测左边的值是否大于右边的值, 如果左边的值大于右边的值返回true | (A > B) 返回false。  |
| <      | 小于号，检测左边的值是否小于右边的值, 如果左边的值小于右边的值返回true | (A < B) 返回 true。  |
| >=     | 大于等于号，检测左边的值是否大于或等于右边的值, 如果左边的值大于或等于右边的值返回true | (A >= B) 返回false。 |
| <=     | 小于等于号，检测左边的值是否小于或等于右边的值, 如果左边的值小于或等于右边的值返回true | (A <= B) 返回 true。 |



#### **（分组查询）**

```sql
select * from 表名 group by 字段1, 字段2;
```

*having：分组操作中的having子语句，是用于在分组后对数据进行过滤的，作用类似于where条件。*

```text
分组查询：

1.聚合函数一般情况下要和分组结合使用。

2.为了方便查看数据，一般作为分组的字段都要显示出来。

3.where用在分组前面。

4.having用在分组的后面.

5.where后面不能用聚合函数。

6.having后面可以使用聚合函数
```



#### **（排序查询）**

```sql
select 字段/列表1，字段/列表2... from 表名 where 条件 order by 排序的字段 ASC|DESC；
```

**注意**：

*order by 一般写在sql语句的最后。*

 *ASC：升序，默认。*

*DESC：降序。*



#### **（链接查询）**

`INNER JOIN` 关键字选择在两个表中具有匹配值的记录。

![MySQL INNER JOIN](https://www.w3schools.cn/mysql/img_innerjoin.gif)

```sql
SELECT column_name(s)
FROM table1
INNER JOIN table2
ON table1.column_name = table2.column_name;
```



`LEFT JOIN` 关键字返回左表（table1）中的所有记录，以及右表（table2）中的匹配记录（如果有）。

![MySQL LEFT JOIN](https://www.w3schools.cn/mysql/img_leftjoin.gif)

```sql
SELECT column_name(s)
FROM table1
LEFT JOIN table2
ON table1.column_name = table2.column_name;
```



`RIGHT JOIN` 关键字返回右表（table2）中的所有记录，以及左表（table1）中的匹配记录（如果有）。 p>

![MySQL RIGHT JOIN](https://www.w3schools.cn/mysql/img_rightjoin.gif)

```sql
SELECT column_name(s)
FROM table1
RIGHT JOIN table2
ON table1.column_name = table2.column_name;
```



### 8、数据库的导入和导出

- **导入**

  ```shell
  source 相对路径
  ```

- **导出**

  ```shell
  mysqldump -u 用户名 -p 数据库名 > 导出的文件名
  ```

  

### 9、约束关系

#### ( 外键约束 )

添加外键时，应该确保附表中的链接主键有唯一约束。

**添加外键**

```sql
ALTER TABLE <数据表名> ADD CONSTRAINT <外键名>
FOREIGN KEY(<列名>) REFERENCES <主表名> (<列名>);
```

**删除外键**

```sql
ALTER TABLE <表名> DROP FOREIGN KEY <外键约束名>;
```

**添加外键属性**

```sql
ON DELETE CASCADE ON UPDATE CASCADE
```



## Mysql拓展

### 一、跳过密码验证登录

在mysql配置文件`/etc/my.cnf`中加入

```sql
skip-grant-tables
```

### 二、mysql用户及用户权限管理

#### 1.添加用户

`host：指定该用户在哪个主机上可以登陆
如果是本地用户可用localhost;
如果想让该用户可以从任意远程主机登陆，可以使用通配符%;`

```sql
create user '用户名'@'%' identified by '密码';//所有主机可登录
create user '用户名'@'localhost' identified by '密码';//仅本地可登录
create user '用户名'@'192.168.3.%' identified by '密码';//指定哪些主机（以192.168.3为前缀）可以登录
```

#### 2. 查看用户信息

```powershell
select * from mysql.user;//查看所有用户所有信息
select user, host, authentication_string from mysql.user;//查看用户名、host、已加密密码以及
```

#### 3. 删除用户

```sql
drop user '用户名'@'host';
```

#### 4. 修改用户信息

```sql
alter user '用户名'@'host' identified by '密码';//修改密码
rename user '用户名'@'host' to '新用户名'@'新host';//修改用户名、host
```

#### 5. 查看用户权限

```sql
show grants;//查看当前用户权限
show grants for '用户名'@'host'//查看指定用户权限
```

#### 6. 用户授权

```sql
grant 权限 on 数据库名.表名 to '用户名'@'host';
grant 权限1,权限2... on 数据库名.表名 to '用户名'@'host';//可同时授予多个权限
```

#### 7. 插销用户权限

```sql
revoke 权限 on 数据库名.表名 from '用户名'@'host';
```



### 三、mysql误删MySQL的root用户解决方法

`进入mysql安全模式`

```sql
use mysql 
```

```sql
insert into user set user='root',ssl_cipher='',x509_issuer=''，x509_subject='';
```

```sql
 update user set Host='localhost',select_priv='y', insert_priv='y',update_priv='y',Alter_priv='y',delete_priv='y',create_priv='y',

drop_priv='y',reload_priv='y',shutdown_priv='y',Process_priv='y',file_priv='y',grant_priv='y',References_priv='y',index_priv='y',

create_user_priv='y',show_db_priv='y',super_priv='y',create_tmp_table_priv='y',Lock_tables_priv='y',execute_priv='y',

repl_slave_priv='y',repl_client_priv='y',create_view_priv='y',show_view_priv='y',create_routine_priv='y',alter_routine_priv='y',

create_user_priv='y' where user='root';
```

`关闭安全模式 重启服务 修改密码 刷新权限`

```sql

```

```sql
flush privileges; 
```



### 四、修改密码安全策略

##### 1. 查看当前密码安全策略

```sql
mysql> select @@validate_password_policy;
```

##### 2. 查看具体的设置项

```sql
mysql> SHOW VARIABLES LIKE 'validate_password%';  
```

##### 3. 修改validate_password_policy参数的值（等级为low）

```sql
mysql> set global validate_password_policy=0;
```

##### 4. 修改validate_password_length为6

```sql
mysql> set global validate_password_length=6;
```

##### 5.修改密码

```sql
mysql> alter user '用户名'@'host' identified by '密码';
```

##### 6.刷新权限

```sql
mysql> flush privileges; 
```



### 五、MySQL初始化

`初始化服务密码`

```sh
 mysqld --initialize --console
```

`使用初始化的密码进行登录`

```sh
mysql -uroot -p
```

