# c语言数据结构之排序

## （1）冒泡查找

1、两两相邻的元素进行比较，如果前面元素大于后面元素就交换两个元素的位置，最终的结果是最大的一个元素移动到了最后的位置。 我们暂称这个过程为冒泡。

2、如果有n个元素那么【冒泡操作】重复n-1次即可排序完成。

```c
//冒泡排序
void Buble_sort(int arr[], int n)
{

    clock_t start, finish;
    start = clock();
    int i;    //比较的轮数
    int j;    //每轮比较的次数
    int temp; //交换数据时用于存放中间数据
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n - 1 - i; j++) //每轮比较n-1-i次,
        {
            if (arr[j] > arr[j + 1])
            {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
    finish = clock();
    printf("\n本次排序一共耗时：%f秒\n", (double)(finish - start) / CLOCKS_PER_SEC);
    printf("冒泡排序后:\n");
    for (i = 0; i < n; ++i)
    {
        printf("%5d", arr[i]);
    }
    printf("\n");
}
```

## （2）直接插入排序

1.每次将一个待排序的数据按照大小插入到前面已经排好序的适当位置，直到全部数据插入完成为止。
2.建立一个哨兵（即临时变量），把要插入的数据赋给它,插入数据从后面开始比较，如果大于前面的就记录下标，并将数据后移，直到插入数据碰到比它小的。将临时变量赋值给当前记录下标。for循环即完成全部数据插入。

```c
//直接插入排序
void Insert_sort(int arr[], int n)
{
    clock_t start, finish;
    start = clock();
    int i, j, temp;
    for (i = 1; i < n; i++)
    {
        if (arr[i] < arr[i - 1])
        {
            temp = arr[i];
            arr[i] = arr[i - 1];
            //数组中大于temp值的数后移
            for (j = i - 1; arr[j] > temp && j >= 0; j--)
            {
                arr[j + 1] = arr[j];
            }
            //找到数组中小于temp值的数赋值
            arr[j + 1] = temp;
        }
    }

    finish = clock();
    printf("\n本次排序一共耗时：%f秒\n", (double)(finish - start) / CLOCKS_PER_SEC);
    printf("直接插入排序后:\n");
    for (i = 0; i < n; ++i)
    {
        printf("%5d", arr[i]);
    }
    printf("\n");
}
```

## （3）简单选择排序

简单选择排序算法原理：每次从左至右扫描序列，记下最小值的位置。然后将最小值与当前位置的值交换

```c
//简单选择排序
void Select_sort(int a[], int n)
{
    clock_t start, finish;
    start = clock();
    int i, j;
    for (i = 0; i < n - 1; i++)
    {
        int min = i; // i表示当前最小元素应该在的位置，min记录最小元素的实际位置
        for (int j = i + 1; j < n; j++)
            if (a[j] < a[min])
                min = j;
        if (min != i)
        {
            int temp = a[min];
            a[min] = a[i];
            a[i] = temp;
        }
    }
    finish = clock();
    printf("\n本次排序一共耗时：%f秒\n", (double)(finish - start) / CLOCKS_PER_SEC);
    printf("选择插入排序后:\n");
    for (i = 0; i < n; ++i)
    {
        printf("%5d", a[i]);
    }
    printf("\n");
}

```

## （4）快速排序

原理分析(从小到大)：
1. 首先取出一个key，一般取第一个元素
2. 从后往前遍历，如果数组中的数据小于了key，那么就将从前往后未比较过的第一个位置即fisrt位置替换为该数据
3. 然后从前往后遍历，如果数组中的数据大于了key，那么就将从后往前的第一个比较过数据位置替换
4. 直到左右两边的位置重合，说明key就找到了正确的位置，每次循环就能找到一个数的正确位置
5. 然后将key左右两边的数据分为两组，递归调用自己。

```c
void quick_Sort(int arr[], int low, int high)
{
    if (low >= high)
        return;
    int first = low;
    int last = high;
    int key = arr[first];
    while (first < last)
    {
        while (first < last && arr[last] >= key)
        {
            last--;
        }
        arr[first] = arr[last];

        while (first < last && arr[first] < key)
        {
            first++;
        }
        arr[last] = arr[first];
    }
    arr[first] = key;

    quick_Sort(arr, low, first - 1);
    quick_Sort(arr, first + 1, high);
}
```

## （5）希尔排序

1.先选定一个小于N的整数gap作为第一增量，然后将所有距离为gap的元素分在同一组，并对每一组的元素进行直接插入排序。然后再取一个比第一增量小的整数作为第二增量，重复上述操作…
2.当增量的大小减到1时，就相当于整个序列被分到一组，进行一次直接插入排序，排序完成

```c
//希尔排序
void shellSort(int a[], int len)
{
    clock_t start, finish;
    start = clock();
    int i, j, k, tmp, gap;  // gap 为步长
    for (gap = len / 2; gap > 0; gap /= 2) {  // 步长初始化为数组长度的一半，每次遍历后步长减半,
    	for (i = 0; i < gap; ++i) { // 变量 i 为每次分组的第一个元素下标 
	        for (j = i + gap; j < len; j += gap) { //对步长为gap的元素进行直插排序，当gap为1时，就是直插排序
	            tmp = a[j];  // 备份a[j]的值
	            k = j - gap;  // j初始化为i的前一个元素（与i相差gap长度）
	            while (k >= 0 && a[k] > tmp) {
	                a[k + gap] = a[k]; // 将在a[i]前且比tmp的值大的元素向后移动一位
	                k -= gap;
	            }
	            a[k + gap] = tmp; 
	        }
	    }
    }
    finish = clock();
    printf("\n本次排序一共耗时：%f秒\n", (double)(finish - start) / CLOCKS_PER_SEC);
    printf("希尔排序后:\n");
    for (int i = 0; i < len; ++i)
    {
        printf("%5d", a[i]);
    }
    printf("\n");
}

```

## （6）堆排序

1、选出一个key，一般是最左边或是最右边的。
2、定义一个begin和一个end，begin从左向右走，end从右向左走。（需要注意的是：若选择最左边的数据作为key，则需要end先走；若选择最右边的数据作为key，则需要bengin先走）。
3、在走的过程中，若end遇到小于key的数，则停下，begin开始走，直到begin遇到一个大于key的数时，将begin和right的内容交换，end再次开始走，如此进行下去，直到begin和end最终相遇，此时将相遇点的内容与key交换即可。（选取最左边的值作为key）
4.此时key的左边都是小于key的数，key的右边都是大于key的数
5.将key的左序列和右序列再次进行这种单趟排序，如此反复操作下去，直到左右序列只有一个数据，或是左右序列不存在时，便停止操作，此时此部分已有序

```c
//堆排序
//交换结点
void swap(int num[],int i,int j)
{
	int temp;
	temp=num[i];
	num[i]=num[j];
	num[j]=temp;
}

//最大堆调整
void Heapify(int num[],int len,int k)
{
	if(k<len)
	{
		int max=k;//根结点
		int s1=2*k+1;//左子节点
		int s2=2*k+2;//右子结点
		//找出最大结点
		if(num[s1]>num[max]&&s1<len)
			max=s1;
		if(num[s2]>num[max]&&s2<len)
			max=s2;
		//交换最大子节点到根结点并做递归
		if(max!=k)
		{
			swap(num,max,k);
			Heapify(num,len,max);
		}
	}
}

//创建最大堆
void CreateHeap(int num[],int len)
{
	int last=len-1;				//最后一个子结点位置
	int parent=(last-1)/2;		//最后一个子结点的父结点
	for(int i=parent;i>=0;i--)	
	{
		Heapify(num,len,i);		//从最后一个父结点开始做最大堆调整
	}
}

//堆排序
void HeapSort(int num[],int len)
{

	CreateHeap(num,len);		//创建最大堆

	for(int i=len-1;i>=0;i--)	//依次将最大堆的根结点（最大值）取出
	{
		//将最大堆的根（最大值）换到最后
		swap(num,i,0);			
		//除去最大值,对交换后的二叉树做最大堆调整，使二叉树根结点始终为最大值	
		Heapify(num,i,0);		
	}
}
```

