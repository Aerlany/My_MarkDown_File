# Spark

## spark基础概念

### RDD

RDD的全称是 `Resilient Distributed Datasets`，这是Spark的一种数据抽象集合，它可以被执行在分布式的集群上进行各种操作，而且有较强的容错机制。RDD可以被分为若干个分区，每一个分区就是一个数据集片段，从而可以支持分布式计算。

**相关名词**

简单来说可以有 Client、Job、Master、Worker、Driver、Stage、Task以及Executor，这几个东西在调优的时候也会经常遇到的。

> **Client**：指的是客户端进程，主要负责提交job到Master；
>
> **Job**：Job来自于我们编写的程序，Application包含一个或者多个job，job包含各种RDD操作；
>
> **Master**：指的是Standalone模式中的主控节点，负责接收来自Client的job，并管理着worker，可以给worker分配任务和资源（主要是driver和executor资源）；
>
> **Worker**：指的是Standalone模式中的slave节点，负责管理本节点的资源，同时受Master管理，需要定期给Master回报heartbeat（心跳），启动Driver和Executor；
>
> **Driver**：指的是 job（作业）的主进程，一般每个Spark作业都会有一个Driver进程，负责整个作业的运行，包括了job的解析、Stage的生成、调度Task到Executor上去执行；
>
> **Stage**：中文名 阶段，是job的基本调度单位，因为每个job会分成若干组Task，每组任务就被称为 Stage；
>
> **Task**：任务，指的是直接运行在executor上的东西，是executor上的一个线程；
>
> **Executor**：指的是 执行器，顾名思义就是真正执行任务的地方了，一个集群可以被配置若干个Executor，每个Executor接收来自Driver的Task，并执行它（可同时执行多个Task）。

### DAG

全称是 Directed Acyclic Graph，中文名是有向无环图。Spark就是借用了DAG对RDD之间的关系进行了建模，用来描述RDD之间的因果依赖关系。因为在一个Spark作业调度中，多个作业任务之间也是相互依赖的，有些任务需要在一些任务执行完成了才可以执行的。在Spark调度中就是有DAGscheduler，它负责将job分成若干组Task组成的Stage。

![img](https://pic3.zhimg.com/v2-956b4732acca4b3dd34354399373004e_r.jpg)

###  **Spark的部署模式有哪些**

主要有`local`模式、`Standalone`模式、`Mesos`模式、`YARN`模式。

### **Shuffle**

Shuffle指的是数据从Map端到Reduce端的数据传输过程，Shuffle性能的高低直接会影响程序的性能。因为Reduce task需要跨节点去拉在分布在不同节点上的Map task计算结果，这一个过程是需要有磁盘IO消耗以及数据网络传输的消耗的，所以需要根据实际数据情况进行适当调整。另外，Shuffle可以分为两部分，分别是Map阶段的数据准备与Reduce阶段的数据拷贝处理，在Map端我们叫Shuffle Write，在Reduce端我们叫Shuffle Read。