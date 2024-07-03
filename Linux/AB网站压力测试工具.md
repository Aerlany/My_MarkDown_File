# **AB测试报告分析**



```bash
ab -n 100 -c 10 https://www.baidu.com/index.html
```

```bash
This is ApacheBench, Version 2.3 <$Revision: 1706008 $>
Copyright 1996 Adam Twiss, Zeus Technology Ltd, http://www.zeustech.net/
Licensed to The Apache Software Foundation, http://www.apache.org/
//以上为apache的版本信息，与本次测试无关
```

```bash
Benchmarking www.baidu.com (be patient).....done

//以上内容显示测试完成度，本次测试发起请求数量较少，完成较快，无中间过程显示。在请求数量很多时会分行显示当前完成数量。
```

```
Server Software:    bfe/1.0.8.14  
//被测试的服务器所用的软件信息，这里使用的是百度自己开发的反向代理Baidu Front End,类似nginx。
```

```bash
Server Hostname:    www.baidu.com 
//被测主机名
```

```
Server Port:      443 
//被测主机的服务端口号，一般http请求的默认端口号是80，https默认使用443端口
```

```
SSL/TLS Protocol:    TLSv1.2,ECDHE-RSA-AES128-GCM-SHA256,2048,128 
//加密协议
```

```
Document Path:     /index.html  
//请求的具体文件
```

```
Document Length:    227 bytes  
//请求的文件index.html大小
```

```
Concurrency Level:   10 
//并发级别，也就是并发数，请求中－c参数指定的数量
```

```
Time taken for tests:  1.093 seconds 
//本次测试总共花费的时间
```

```
Complete requests:   100 
//本次测试总共发起的请求数量
```

```
Failed requests:    0 
//失败的请求数量。因网络原因或服务器性能原因，发起的请求并不一定全部成功，通过该数值和Complete requests相除可以计算请求的失败率，作为测试结果的重要参考。
```

```
Total transferred:   103314 bytes  
//总共传输的数据量，指的是ab从被测服务器接收到的总数据量，包括index.html的文本内容和请求头信息。
```

```
HTML transferred:    22700 bytes 
//从服务器接收到的index.html文件的总大小，等于Document Length＊Complete requests＝227 bytes＊100＝22700 bytes
```

```
Requests per second:  91.50 [#/sec] (mean) 
//平均(mean)每秒完成的请求数：QPS，这是一个平均值，等于Complete requests/Time taken for tests=100/1.093=91.50
```

```
Time per request:    109.287 [ms] (mean) 
//从用户角度看，完成一个请求所需要的时间（因用户数量不止一个，服务器完成10个请求，平均每个用户才接收到一个完整的返回，所以该值是下一项数值的10倍。）
```

```
Time per request:    10.929 [ms] (mean, across all concurrent requests)
// 服务器完成一个请求的时间。
```

```
Transfer rate:     92.32 [Kbytes/sec] received 
//网络传输速度。对于大文件的请求测试，这个值很容易成为系统瓶颈所在。要确定该值是不是瓶颈，需要了解客户端和被测服务器之间的网络情况，包括网络带宽和网卡速度等信息。
```

 

```
Connection Times (ms)

​       	min 	mean	[+/-sd] 	median  	max

Connect:    47  	74 		12.9   		74   		106

Processing: 9  		32 		20.2   		32   		106

Waiting:    9  		29 		19.1   		27   		98

Total:     	66 		106 	20.8  		106   		195

//这几行组成的表格主要是针对响应时间也就是第一个Time per request进行细分和统计。一个请求的响应时间可以分成网络链接（Connect），系统处理（Processing）和等待（Waiting）三个部分。表中min表示最小值； mean表示平均值；[+/-sd]表示标准差（Standard Deviation） ，也称均方差（mean square error），这个概念在中学的数学课上学过，表示数据的离散程度，数值越大表示数据越分散，系统响应时间越不稳定。 median表示中位数； max当然就是表示最大值了。
//需要注意的是表中的Total并不等于前三行数据相加，因为前三行的数据并不是在同一个请求中采集到的，可能某个请求的网络延迟最短，但是系统处理时间又是最长的呢。所以Total是从整个请求所需要的时间的角度来统计的。这里可以看到最慢的一个请求花费了195ms，这个数据可以在下面的表中得到验证。
```

```
Percentage of the requests served within a certain time (ms)
 50%  106
 66%  109
 75%  111
 80%  114
 90%  118
 95%  154
 98%  176
 99%  195
 100%  195 (longest request)
 //这个表第一行表示有50%的请求都是在106ms内完成的，可以看到这个值是比较接近平均系统响应时间（第一个Time per request:    109.287 [ms] (mean) ）以此类推，90%的请求是小于等于118ms的。刚才我们看到响应时间最长的那个请求是195ms，那么显然所有请求（100%）的时间都是小于等于195毫秒的，也就是表中最后一行的数据肯定是时间最长的那个请求（longest request）。
```



