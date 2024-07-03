#  Spring Security 

## 简介

Spring Security 是 Spring 家族中的一个安全管理框架。相比与另外一个安全框架Shiro，它提供了更丰富的功能，社区资源也比Shiro丰富。

 一般来说中大型的项目都是使用Spring Security 来做安全框架。小项目有Shiro的比较多，因为相比与Spring Security，Shiro的上手更加的简单。

 一般Web应用的需要进行认证和授权。

认证：验证当前访问系统的是不是本系统的用户，并且要确认具体是哪个用户

授权：经过认证后判断当前用户是否有权限进行某个操作

而认证和授权也是Spring Security作为安全框架的核心功能。

## 快速入门

在我们创建好一个 Spring Boot 项目后，在`pom.xml`文件中引入以下依赖

```xml
        <dependency>
            <groupId>org.springframework.boot</groupId>
            <artifactId>spring-boot-starter-security</artifactId>
        </dependency>
```

注意：引入依赖后我们在尝试去访问之前的接口就会自动跳转到一个SpringSecurity的默认登陆页面，默认用户名是user,密码会输出在控制台。 必须登陆之后才能对接口进行访问。



## 认证

### 登录校验流程

<img src="https://img-blog.csdnimg.cn/a7a8fdee84084b8dadc4ee29ae0b3257.png?x-oss-process=image/watermark,type_d3F5LXplbmhlaQ,shadow_50,text_Q1NETiBA5bCn5LiK5pyJ5Yac,size_20,color_FFFFFF,t_70,g_se,x_16" alt="在这里插入图片描述" style="zoom:80%;" />



### SpringSecurity完整流程

 Spring Security的原理其实就是一个过滤器链，内部包含了提供各种功能的过滤器。这里我们可以看看入门案例中的过滤器。

<img src="https://img-blog.csdnimg.cn/2b17809d92b54724a93c7cd8b5b36d29.png?x-oss-process=image/watermark,type_d3F5LXplbmhlaQ,shadow_50,text_Q1NETiBA5bCn5LiK5pyJ5Yac,size_20,color_FFFFFF,t_70,g_se,x_16" alt="img" style="zoom: 80%;" />

 图中只展示了核心过滤器，其它的非核心过滤器并没有在图中展示。

`UsernamePasswordAuthenticationFilter`:负责处理我们在登陆页面填写了用户名密码后的登陆请求。入门案例的认证工作主要有它负责。

`ExceptionTranslationFilter`： 处理过滤器链中抛出的任何`AccessDeniedException`和`AuthenticationException` 。

`FilterSecurityInterceptor`： 负责权限校验的过滤器。



### 认证流程详解

<img src="https://img-blog.csdnimg.cn/876cfee0be5f4869bac24e447db74cd8.png?x-oss-process=image/watermark,type_d3F5LXplbmhlaQ,shadow_50,text_Q1NETiBA5bCn5LiK5pyJ5Yac,size_20,color_FFFFFF,t_70,g_se,x_16" alt="在这里插入图片描述" style="zoom: 80%;" />

`Authentication`接口: 它的实现类，表示当前访问系统的用户，封装了用户相关信息。

`AuthenticationManager`接口：定义了认证`Authentication`的方法

`UserDetailsService`接口：加载用户特定数据的核心接口。里面定义了一个根据用户名查询用户信息的方法。

`UserDetails`接口：提供核心用户信息。通过`UserDetailsService`根据用户名获取处理的用户信息要封装成`UserDetails`对象返回。然后将这些信息封装到Authentication对象中。



### 思路分析

**登录：**

 ①自定义登录接口

 	调用`ProviderManager`的方法进行认证 如果认证通过生成jwt
 	
 	把用户信息存入`redis`中

 ②自定义`UserDetailsService`

 	在这个实现类中去查询数据库

**校验：**

 ①定义Jwt认证过滤器

 	获取token
 	
 	解析token获取其中的`userid`
 	
 	从`redis`中获取用户信息
 	
 	存入`SecurityContextHolder`

