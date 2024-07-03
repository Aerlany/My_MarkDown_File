# Debian安装Java

Java是用于构建各种应用程序和系统的最流行的编程语言之一。Java可以在所有主流的操作系统和设备上运行。您可以在手机和游戏机上找到用Java开发的应用程序。

Java有多种不同的实现。Open JDK和Oracle Java是Java的两个主要实现，它们之间几乎没有区别，只是Oracle Java具有一些附加的商业功能。

Oracle Java[许可证](https://www.oracle.com/technetwork/java/javase/terms/license/javase-license.html)仅允许该软件的非商业使用，例如个人使用和开发使用。

默认的Debian 10软件源包含两个OpenJDK软件包：Java Runtime Environment JRE和Java Development Kit JDK。

JRE由Java虚拟机JVM，类和二进制文件组成，可让您运行Java程序。JDK包含构建Java应用程序所需的JRE以及开发/调试工具和库。

如果不确定要安装哪个Java软件包，通常建议安装OpenJDK版本11。一些基于Java的应用程序可能需要特定版本的Java，因此您应该查阅应用程序文档来确定使用的java版本。

## 安装 OpenJDK 11

在撰写本文时，Java 11是Java的最新长期支持版本LTS。它也是Debian 10中默认的Java开发和运行时。

以root或具有[sudo权限](https://www.myfreax.com/how-to-create-a-sudo-user-on-debian/)的用户运行以下命令，以更新软件包索引并安装Open JDK 11 JDK软件包。

如果仅需要JRE，则安装`openjdk-11-jre`。如果你为了使Java运行时占用空间最少，请安装`openjdk-11-jdk-headless`。

安装完成后，您可以运行命令`java -version`打印java版本号。至此，您已经在Debian 10安装Java 11。JRE包含在JDK软件包中。

```shell
sudo apt update
sudo apt install openjdk-11-jdk
java -version
```

## 安装 OpenJDK 8 （已经失效）

以前的Java LTS版本Java 8仍然被广泛使用。 如果您的应用程序仅在Java 8上运行，则可以运行命令`sudo apt install openjdk-8-jdk`进行安装。

如果仅需要JRE，则安装`openjdk-8-jre`。如果你为了使Java运行时占用空间最少，请安装`openjdk-8-jdk-headless`。

安装完成后，您可以运行命令`java -version`打印java版本号。至此，您已经在Debian 10安装Java 8。JRE包含在JDK软件包中。

```shell
sudo apt update
sudo apt install openjdk-8-jdk
java -version
```



## 设置Java 默认版本

如果您的Debian 10安装多个Java版本，则可以运行命令`sudo update-alternatives --config java`检查将哪个版本设置为默认版本。

```shell
sudo update-alternatives --config java
```

命令将会打印一个列表，其中`*`开头的行表示默认使用的Java版本。要查看当前的Java版本。你可以运行命令`java -version`检查当前使用的版本。

如果需要更改默认版本，请运行命令`sudo update-alternatives --config java`。

将为您提供所有已安装的Java版本的列表。 输入您要用作默认版本的数字，然后按`Enter`。

```shell
sudo update-alternatives --config java
There are 2 choices for the alternative java (providing /usr/bin/java).

  Selection    Path                                            Priority   Status
------------------------------------------------------------
* 0            /usr/lib/jvm/java-11-openjdk-amd64/bin/java      1111      auto mode
  1            /usr/lib/jvm/java-11-openjdk-amd64/bin/java      1111      manual mode
  2            /usr/lib/jvm/java-8-openjdk-amd64/jre/bin/java   1081      manual mode
Press <enter> to keep the current choice[*], or type selection number: 
```

除了更改默认的`java`的版本之外，你还需要更改`javac`的默认版本，也就是java编译器的版本。建议java和javac使用相同的版本号，避免因版本导致的问题。

修改`javac`默认版本与修改默认java版本类似。可以运行命令`sudo update-alternatives --config javac`更改`javac`的版本。

<iframe id="aswift_2" name="aswift_2" browsingtopics="true" sandbox="allow-forms allow-popups allow-popups-to-escape-sandbox allow-same-origin allow-scripts allow-top-navigation-by-user-activation" width="736" height="0" frameborder="0" marginwidth="0" marginheight="0" vspace="0" hspace="0" allowtransparency="true" scrolling="no" allow="attribution-reporting; run-ad-auction" src="https://googleads.g.doubleclick.net/pagead/ads?gdpr=0&amp;client=ca-pub-9716082213503633&amp;output=html&amp;h=280&amp;adk=2106567869&amp;adf=520100227&amp;pi=t.aa~a.1818994006~i.26~rp.4&amp;w=736&amp;fwrn=4&amp;fwrnh=100&amp;lmt=1710957767&amp;num_ads=1&amp;rafmt=1&amp;armr=3&amp;sem=mc&amp;pwprc=6096613189&amp;ad_type=text_image&amp;format=736x280&amp;url=https%3A%2F%2Fwww.myfreax.com%2Finstall-java-on-debian-10%2F&amp;fwr=0&amp;pra=3&amp;rh=184&amp;rw=736&amp;rpe=1&amp;resp_fmts=3&amp;wgl=1&amp;fa=27&amp;uach=WyJMaW51eCIsIjYuMS4wIiwieDg2IiwiIiwiMTIzLjAuNjMxMi41OCIsbnVsbCwwLG51bGwsIjY0IixbWyJHb29nbGUgQ2hyb21lIiwiMTIzLjAuNjMxMi41OCJdLFsiTm90OkEtQnJhbmQiLCI4LjAuMC4wIl0sWyJDaHJvbWl1bSIsIjEyMy4wLjYzMTIuNTgiXV0sMF0.&amp;dt=1710957767062&amp;bpp=2&amp;bdt=9794&amp;idt=-M&amp;shv=r20240314&amp;mjsv=m202403140101&amp;ptt=9&amp;saldr=aa&amp;abxe=1&amp;cookie=ID%3Ddcbff1148907be55%3AT%3D1710957766%3ART%3D1710957766%3AS%3DALNI_Maliww9JWXy3ZYcHO7JY-Hq82iJBw&amp;gpic=UID%3D00000d4c29563425%3AT%3D1710957766%3ART%3D1710957766%3AS%3DALNI_MaWOpgbg3TjP3BpfV0nRsOQXPOIBA&amp;eo_id_str=ID%3Db96a4a3fe1709d99%3AT%3D1710957766%3ART%3D1710957766%3AS%3DAA-AfjZBjOqdBTvTbkJDLAIWDibm&amp;prev_fmts=0x0%2C1200x280&amp;nras=2&amp;correlator=6156842851271&amp;frm=20&amp;pv=1&amp;ga_vid=1625806312.1710957759&amp;ga_sid=1710957763&amp;ga_hid=507066183&amp;ga_fc=1&amp;u_tz=480&amp;u_his=3&amp;u_h=1080&amp;u_w=1920&amp;u_ah=1080&amp;u_aw=1920&amp;u_cd=24&amp;u_sd=1&amp;dmc=8&amp;adx=433&amp;ady=3671&amp;biw=1905&amp;bih=959&amp;scr_x=0&amp;scr_y=2273&amp;eid=44759875%2C44759926%2C44759842%2C31081905%2C95320377%2C31081572%2C95322397%2C95326916%2C31078663%2C31078665%2C31078668%2C31078670&amp;oid=2&amp;pvsid=4168748717292438&amp;tmod=1975129363&amp;uas=0&amp;nvt=1&amp;ref=https%3A%2F%2Fwww.google.com%2F&amp;fc=1408&amp;brdim=0%2C0%2C0%2C0%2C1920%2C0%2C1920%2C1080%2C1920%2C959&amp;vis=1&amp;rsz=%7C%7Cs%7C&amp;abl=NS&amp;fu=128&amp;bc=31&amp;bz=1&amp;td=1&amp;psd=W251bGwsbnVsbCxudWxsLDNd&amp;nt=1&amp;ifi=3&amp;uci=a!3&amp;btvi=1&amp;fsb=1&amp;dtd=425" data-google-container-id="a!3" data-google-query-id="CIT72a-2g4UDFeSuSwUdKewBkA" data-load-complete="true" style="border: 0px; box-sizing: border-box; --tw-border-spacing-x: 0; --tw-border-spacing-y: 0; --tw-translate-x: 0; --tw-translate-y: 0; --tw-rotate: 0; --tw-skew-x: 0; --tw-skew-y: 0; --tw-scale-x: 1; --tw-scale-y: 1; --tw-pan-x: ; --tw-pan-y: ; --tw-pinch-zoom: ; --tw-scroll-snap-strictness: proximity; --tw-ordinal: ; --tw-slashed-zero: ; --tw-numeric-figure: ; --tw-numeric-spacing: ; --tw-numeric-fraction: ; --tw-ring-inset: ; --tw-ring-offset-width: 0px; --tw-ring-offset-color: #fff; --tw-ring-color: rgba(59,130,246,.5); --tw-ring-offset-shadow: 0 0 #0000; --tw-ring-shadow: 0 0 #0000; --tw-shadow: 0 0 #0000; --tw-shadow-colored: 0 0 #0000; --tw-blur: ; --tw-brightness: ; --tw-contrast: ; --tw-grayscale: ; --tw-hue-rotate: ; --tw-invert: ; --tw-saturate: ; --tw-sepia: ; --tw-drop-shadow: ; --tw-backdrop-blur: ; --tw-backdrop-brightness: ; --tw-backdrop-contrast: ; --tw-backdrop-grayscale: ; --tw-backdrop-hue-rotate: ; --tw-backdrop-invert: ; --tw-backdrop-opacity: ; --tw-backdrop-saturate: ; --tw-backdrop-sepia: ; display: block; vertical-align: middle; left: 0px; top: 0px; width: 736px; height: 0px;"></iframe>

同样，命令将为您提供所有已安装的`javac`版本的列表。 输入您要用作默认版本的版本号，然后按`Enter`。

```shell
sudo update-alternatives --config javac
```