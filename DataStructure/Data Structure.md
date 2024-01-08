# 查找方法

### 插值查找

![img](https://img-blog.csdnimg.cn/20200622212422237.PNG#pic_center)

```c
include<iostream>
using namespace std;

int Interpolation_search(int *a, int search_value, int low, int high)
{
	if (low > high)
		return -1;
	int lo = low, hi = high;
	int mid = lo + (hi - lo)*((search_value - a[lo]) / (a[hi] - a[lo]));
	
	if(mid>=10)
		reurn -1;
	
	if (a[mid] < search_value)
		return Interpolation_search(a, search_value, mid + 1, hi);
	else if (search_value < a[mid])
		return Interpolation_search(a, search_value, lo, mid - 1);
	else if (a[mid] == search_value)
		return mid + 1;

}

int InterpolationSearch(int *A, int e, int low, int high)
{
	while (low < high)
	{
		int mid = low + (high - low - 1)*(e - A[low]) / (A[high - 1] - A[low]);
		if (mid >= 10) //在这里防止死循环退出
			return -1;
		if (e < A[mid])
			high = mid;
		else if (e > A[mid])
			low = mid + 1;
		else
			return mid;
	}
	return -1;
}

int main()
{
	int a[19] = { 5,10,12,14,26,31,38,39,42,46,49,51,54,59,72,79,82,86,92 };
	//	cout<<Interpolation_search(a,50,0,18)<<endl;;
	cout << InterpolationSearch(a, 50, 0, 18);
	cout << endl;
	return 0;
}

```

### 分块查找

```
1.将查找表分成几块。块间有序,即第i+1块的所有记录关键字均大于(或小于)第i块记录关键字;块内无序。
2.在查找表的基础上附加一个索引表,索引表是按关键字有序的,索引表中记录的构成是:
最大关键字
起始指针2 
3.查找思想
先确定待查记录所在块,再在块内查找(顺序查找)。
```

```c
//分块查找
void Block_search(int Array[], int key, int len)
{
    clock_t start, finish;
    start = clock();

    //块数
    int size = len / 10;
    Index Array2[size];
    for (int i = 0; i < size; i++)
    {
        int a = (i + 1) * 10;
        Array2[i].maxkey = Array[a - 1];
        Array2[i].startpos = i * 10;
    }

    int i = 0, j, k;
    //确定key值所在块
    while ((i < size) && Array2[i].maxkey < key)
    {
        i++;
    }
    if (i > size)
    {
        printf("未找到！！\n");
    }

    j = Array2[i].startpos;
    // for (j; j < j + 9; j++)
    // {
    //     if (Array[j] == key && j < len)
    //     {
    //         finish = clock();
    //         printf("找到了在%d 处！本次查找一共耗时：%f秒\n\n", j ,(double)(finish - start) / CLOCKS_PER_SEC);
    //         break;
    //     }
    // }
    
    //块内查找
    while ((j < len) && Array[j] < Array2[i].maxkey)
    {
        if (Array[j] == key)
        {
            finish = clock();
            printf("找到了在%d 处！本次查找一共耗时：%f秒\n\n", j, (double)(finish - start) / CLOCKS_PER_SEC);
            break;
        }
        j++;
    }

    if (j > len || Array[j] != key)
    {
        finish = clock();
        printf("未找到！本次查找一共耗时：%f秒\n\n", (double)(finish - start) / CLOCKS_PER_SEC);
    }
}
```

### 斐波那契查找

```
Fibonacci查找方法是根据Fibonacci数列的特点对查找表进行分割。
Fibonacci数列的定义是:F(0)=0,F(1)=1,F(j)=F(j-1)+F(j-2。

查找思想
设查找表中的记录数比某个Fibonacci数小1,即设n=F(j)-1。用Low、High和Mid表示待查找区间的下界、上界和分割位置,初值为Low=1,High=n。
(1) 取分割位置Mid:Mid=F(j-1) ;
(2) 比较分割位置记录的关键字与给定的K值:
1 相等: 查找成功;
2 大于:待查记录在区间的前半段(区间长度为F(j-1)-1),修改上界指针: High=Mid-1,转(1) ;
3 小于:待查记录在区间的后半段(区间长度为F(j-2)-1),修改下界指针:Low=Mid+1,转(1) ;

直到越界(Low>High),查找失败。
```

```

```

### 二叉树查找

```
二叉排序树(Binary Sort Tree或Binary Search Tree)
的定义为:二叉排序树或者是空树,或者是满足下列性
质的二叉树。
(1) :若左子树不为空,则左子树上所有结点的值(关
键字)都小于根结点的值;
(2) :若右子树不为空,则右子树上所有结点的值(关
键字)都大于根结点的值;
(3) :左、右子树都分别是二叉排序树。
结论: 若按中序遍历一棵二叉排序树,所得到的
结点序列是一个递增序列。
```

# 排序

### 快速排序

```
原理分析(从小到大)：
1. 首先取出一个key，一般取第一个元素
2. 从后往前遍历，如果数组中的数据小于了key，那么就将从前往后未比较过的第一个位置即fisrt位置替换为该数据
3. 然后从前往后遍历，如果数组中的数据大于了key，那么就将从后往前的第一个比较过数据位置替换
4. 直到左右两边的位置重合，说明key就找到了正确的位置，每次循环就能找到一个数的正确位置
5. 然后将key左右两边的数据分为两组，递归调用自己。

```

