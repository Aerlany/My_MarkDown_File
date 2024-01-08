# c语言数据结构之查找

## （1）顺序查找

顺序查找（Sequential Search）的查找过程为：从表的一端开始，依次将表中的关键字和给定	的值进行比较，若表中的关键字和给定的值相等，则查找成功，反之查找失败。

```c
//顺序查找
void Search_Seq01(int Array[], int key, int len)
{
    clock_t start, finish;
    start = clock();
    for (int i = 1; i < len; i++)
    {
        if (Array[i] == key)
        {
            finish = clock();
            printf("找到了在%d 处！本次查找一共耗时：%f秒\n\n", i, (double)(finish - start) / CLOCKS_PER_SEC);
            break;
        }
        else if (i == len - 1)
        {
            finish = clock();
            printf("未找到！本次查找一共耗时：%f秒\n\n", (double)(finish - start) / CLOCKS_PER_SEC);
        }
    }
}
```

## （2）折半查找

先找到那个有序序列的中间元素mid，然后拿它和要找的元素K进行比较，就可以初步判断K所在范围，既然查找范围已确定，自然该范围之外的元素就可以不用再查找了。接下来按照上面的步骤反复查找下去。

```c
//二分查找
void Bin_Search(int Array[], int key, int a)
{
    clock_t start, finish;
    start = clock();
    int low = 1;
    int higth = a;
    int mid;
    while (low < higth)
    {
        mid = (low + higth) / 2;
        if (Array[mid] == key)
        {
            finish = clock();
            printf("找到了在%d 处！本次查找一共耗时：%f秒\n\n", mid, (double)(finish - start) / CLOCKS_PER_SEC);
            break;
        }
        else if (Array[mid] < key)
        {
            low = mid + 1;
        }
        else
        {
            higth = mid - 1;
        }
    }
}
```

## （3）分块查找

先确定待查记录所在的子块，然后在块中顺序查找。由于由索引项组成的索引表按关键字有序，则确定块的查找可以用顺序查找，亦可用折半查找。而块中记录是任意排序的，则在块中只能是顺序查找。（块间有序，块内可以无序）。

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

## （4）插值查找

插值查找的方法与折半查找的思路基本一致，但是其Mid采用该的方法确定
mid = first+(target-num[first])*(last-first)/(num[last]-num[first]);

```c
//插值查找
void Insert_Search(int Array[], int key, int len)
{
    clock_t start, finish;
    start = clock();
    int low = 0, mid;
    int higth = len - 1;
    // int higth = len;

    while (low <= higth)
    {

        mid = low + (key - Array[low]) * (higth - low) / (Array[higth] + Array[low]);
        // mid = low + ((key - Array[low]) / (Array[higth] - Array[low])) * (higth - low - 1);
        if (Array[mid] > key)
        {
            higth = mid - 1;
        }
        else if (Array[mid] < key)
        {
            low = mid + 1;
        }
        else
        {
            finish = clock();
            printf("找到了在%d 处！本次查找一共耗时：%f秒\n\n", mid, (double)(finish - start) / CLOCKS_PER_SEC);
            break;
        }
    }
}
```

## （5）斐波那契查找

斐波那契查找原理与前两种相似，仅仅改变了中间结点（mid）的位置，mid不再是中间或插值得到，而是位于黄金分割点附近。
斐波那契数列 F(k)={1，1，2，3，5，8，13，21…}，(从第三个数开始，后边每一个数都是前两个数的和)。
F[k] = F[k-1] + F[k-2]
斐波那契数列前一项/后一项的值越来越接近黄金比例，即0.618。
斐波那契查找关键就在要找到mid的位置。
在n=F(k)-1情况下，mid = low + F[k-1] - 1，我们就得到了mid的位置
但顺序表长度n不一定刚好等于F[k]-1，所以需要将原来的顺序表长度n增加至F[k]-1。
k值只要能使得F[k]-1恰好大于或等于n即可

```c
//生成Fibonacci数列
void Fibonacci(int f[],int n)
{
    int i;
    f[0] = 1;
    f[1] = 1;
    for (i = 2; i < n; ++i)
    {
        f[i] = f[i - 2] + f[i - 1];
    }
}
//斐波那契查找
void Fibonacci_Search(int a[], int key, int n)
{
    clock_t start, finish;
    start = clock();
    int i, low = 0, high = n - 1;
    int mid = 0;
    int k = 0;
    int f[n];

    Fibonacci(f,n);
    while (n > f[k] - 1)
        ++k;
    for (i = n; i < f[k] - 1; ++i) //把数组补全
        a[i] = a[high];
    while (low <= high)
    {

        mid = low + f[k - 1] - 1; //根据斐波那契数列进行黄金分割

        if (a[mid] > key)
        {
            high = mid - 1;
            k = k - 1;
        }
        else if (a[mid] < key)
        {
            low = mid + 1;
            k = k - 2;
        }
        else
        {
            if (mid <= high)
            { //如果为真则找到相应的位置
                finish = clock();
                printf("找到了在%d 处！本次查找一共耗时：%f秒\n\n", mid, (double)(finish - start) / CLOCKS_PER_SEC);
                return;
                break;
            }
            else
            {
                mid = -1;
                break;
            }
        }
    }
}

```

## 源码附上

```c
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

//定义索引表（分块查找）
typedef struct IndexType
{
    int maxkey;   /* 块中最大的关键字 */
    int startpos; /* 块的起始位置指针 */
} Index;

//顺序查找
void Search_Seq01(int Array[], int key, int len)
{
    clock_t start, finish;
    start = clock();
    for (int i = 1; i < len; i++)
    {
        if (Array[i] == key)
        {
            finish = clock();
            printf("找到了在%d 处！本次查找一共耗时：%f秒\n\n", i, (double)(finish - start) / CLOCKS_PER_SEC);
            break;
        }
        else if (i == len - 1)
        {
            finish = clock();
            printf("未找到！本次查找一共耗时：%f秒\n\n", (double)(finish - start) / CLOCKS_PER_SEC);
        }
    }
}

//二分查找
void Bin_Search(int Array[], int key, int a)
{
    clock_t start, finish;
    start = clock();
    int low = 1;
    int higth = a;
    int mid;
    while (low < higth)
    {
        mid = (low + higth) / 2;
        if (Array[mid] == key)
        {
            finish = clock();
            printf("找到了在%d 处！本次查找一共耗时：%f秒\n\n", mid, (double)(finish - start) / CLOCKS_PER_SEC);
            break;
        }
        else if (Array[mid] < key)
        {
            low = mid + 1;
        }
        else
        {
            higth = mid - 1;
        }
    }
}

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

//插值查找
void Insert_Search(int Array[], int key, int len)
{
    clock_t start, finish;
    start = clock();
    int low = 0, mid;
    int higth = len - 1;
    // int higth = len;

    while (low <= higth)
    {

        mid = low + (key - Array[low]) * (higth - low) / (Array[higth] + Array[low]);
        // mid = low + ((key - Array[low]) / (Array[higth] - Array[low])) * (higth - low - 1);
        if (Array[mid] > key)
        {
            higth = mid - 1;
        }
        else if (Array[mid] < key)
        {
            low = mid + 1;
        }
        else
        {
            finish = clock();
            printf("找到了在%d 处！本次查找一共耗时：%f秒\n\n", mid, (double)(finish - start) / CLOCKS_PER_SEC);
            break;
        }
    }
}

//斐波那契查找
void Fibonacci(int f[],int n)
{
    int i;
    f[0] = 1;
    f[1] = 1;
    for (i = 2; i < n; ++i)
    {
        f[i] = f[i - 2] + f[i - 1];
    }
}

void Fibonacci_Search(int a[], int key, int n)
{
    clock_t start, finish;
    start = clock();
    int i, low = 0, high = n - 1;
    int mid = 0;
    int k = 0;
    int f[n];

    Fibonacci(f,n);
    while (n > f[k] - 1)
        ++k;
    for (i = n; i < f[k] - 1; ++i) //把数组补全
        a[i] = a[high];
    while (low <= high)
    {

        mid = low + f[k - 1] - 1; //根据斐波那契数列进行黄金分割

        if (a[mid] > key)
        {
            high = mid - 1;
            k = k - 1;
        }
        else if (a[mid] < key)
        {
            low = mid + 1;
            k = k - 2;
        }
        else
        {
            if (mid <= high)
            { //如果为真则找到相应的位置
                finish = clock();
                printf("找到了在%d 处！本次查找一共耗时：%f秒\n\n", mid, (double)(finish - start) / CLOCKS_PER_SEC);
                return;
                break;
            }
            else
            {
                mid = -1;
                break;
            }
        }
    }
}

int main()
{
    int a = 0;
    printf("你想查找几个数:");
    scanf("%d", &a);
    srand((int)time(NULL));
    int Array[a];
    for (int i = 0; i < a; i++)
    {
        Array[i] = rand() % 1000;
    }

    int i;    //比较的轮数
    int j;    //每轮比较的次数
    int temp; //交换数据时用于存放中间数据
    for (i = 0; i < a; i++)
    {
        for (j = 0; j < a - 1 - i; j++) //每轮比较n-1-i次,
        {
            if (Array[j] > Array[j + 1])
            {
                temp = Array[j];
                Array[j] = Array[j + 1];
                Array[j + 1] = temp;
            }
        }
    }
    printf("排序后:\n");
    for (i = 0; i < a; ++i)
    {
        printf("%5d", Array[i]);
    }
    printf("\n");

    int v;
    printf("请输入查找数:");
    scanf("%d", &v);

    printf("顺序查找\n");
    Search_Seq01(Array, v, a);
    printf("二分查找\n");
    Bin_Search(Array, v, a);
    printf("分块查找\n");
    Block_search(Array, v, a);
    printf("插值查找\n");
    Insert_Search(Array, v, a);
    printf("Fibonacci查找\n ");
    Fibonacci_Search(Array, v, a);
    
}

```

