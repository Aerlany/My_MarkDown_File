# c语言数据结构之迷宫问题

## 代码100%可以远行！！

迷宫问题求解
（一）思路：
首先实现一个以链表作存储结构的栈类型,然后编写一个求解迷宫的非递归程序。求得的通路以三元组(i,j,d)的形式输出,其中:(i,j)指示迷宫中的一个坐标,d 表示走到下一坐标的方向。

```c
typedef struct Data
{
int abscissa; // x
int ordinate; // y
int direction;
} Data;
```

计算机解迷宫通常用的是“穷举求解”方法,即从入口出发,顺着某一个方向进行探索,若能走通,则继续前进;否则沿着原路退回,换一个方向继续探索,直至出口位置,求得一条通路。假如所有可能的通路都探索到而未能到达出口,则所设定的迷宫没有通路。可以二维数组存储迷宫数据,通常设定入口的下标为(1,1),出口点的下标为(n,n)。为处理方便起见,可在迷宫的四周加一圈障碍。对于迷宫中任一位置,均可约定有东、南、西、北四个方向可通。

（二）步骤分析
1、用二维数组存放0,1来分别表示迷宫中可走方块以及不可走方块。
2、从入口处开始，顺时针方向去试探当前方块的四个方位（上，左，下，右）。
3、在当前位置寻找四个方位中的可走方块。若当前试探方位可走。则将该试探方位的方块入栈，	并将此时走过的方块置为不可走（这里将值置为-1），以防止两个方块来回进入死循环，此时试	探方位的方块在栈的顶部，再用栈顶方块继续对四个方位进行试探。若当前方块的四个试探方	位都无法前进。则将当前方块退栈，并将退栈方块的值恢复为0，然后找此时栈顶方块的其他	可能的相邻方块。

```c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define Row 8
#define Col 9
// typedef int ElemenType;

typedef struct Data
{
    int abscissa; // x
    int ordinate; // y
    int direction;
} Data;

typedef struct StackNode
{
    Data data;
    struct StackNode *next;
} StackNode;

int directions[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

int maze[Col + 2][Row + 2] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 1, 0, 0, 0, 1, 0, 1},
    {1, 0, 0, 1, 0, 0, 0, 1, 0, 1},
    {1, 0, 0, 0, 0, 1, 1, 0, 1, 1},
    {1, 0, 1, 1, 1, 0, 0, 1, 0, 1},
    {1, 0, 0, 0, 1, 0, 0, 0, 0, 1},
    {1, 0, 1, 0, 0, 0, 1, 0, 1, 1},
    {1, 0, 1, 1, 1, 1, 0, 0, 1, 1},
    {1, 1, 1, 0, 0, 0, 1, 0, 1, 1},
    {1, 1, 1, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};

//初始化
StackNode *Init(void)
{
    StackNode *top;
    top = (StackNode *)malloc(sizeof(StackNode));
    top->next = NULL;

    return top;
}

//进栈
void Push(StackNode *top, Data data)
{
    StackNode *p;
    p = (StackNode *)malloc(sizeof(StackNode));
    if (!p)
    {
        printf("申请新结点失败!!\n");
    }
    else
    {
        //前插入法
        p->data = data;
        p->next = top->next;
        top->next = p;
    }
    printf("%d,%d 进栈\n", data.ordinate, data.abscissa);
}

//出栈
void Pop(StackNode *top)
{
    StackNode *p;
    Data data;
    if (p->next == NULL)
    {
        printf("栈空！！\n");
    }
    else
    {
        p = top->next;
        data = p->data;      /* 取栈顶元素 */
        top->next = p->next; /*修改栈顶指针*/
        free(p);
        printf("%d,%d出栈!!\n", data.ordinate, data.abscissa);
    }
}

void Run()
{
    StackNode *top = Init();
    Data data;
    int x1, y1, d1, find;

    data.abscissa = 1;
    data.ordinate = 1;
    data.direction = -1;
    Push(top, data);

    while (top->next != NULL)
    {
        x1 = top->next->data.abscissa;
        y1 = top->next->data.ordinate;
        d1 = top->next->data.direction;

        //输出路径逻辑
        if (x1 == Col && y1 == Row)
        {
            printf("找到路径:");
            StackNode *p;
            p = top->next;
            while (p != NULL)
            {
                printf("(%d,%d)", p->data.ordinate, p->data.abscissa);
                p = p->next;
            }
            printf("\n");
            break;
        }

        //查找下一个节点
        find = 0;
        while (find == 0 && d1 < 4)
        {
            d1++;
            switch (d1)
            {
            //向上
            case 0:
                x1 = top->next->data.abscissa;
                y1 = top->next->data.ordinate - 1;
                break;

            //右
            case 1:
                x1 = top->next->data.abscissa + 1;
                y1 = top->next->data.ordinate;
                break;

            //向下
            case 2:
                x1 = top->next->data.abscissa;
                y1 = top->next->data.ordinate + 1;
                break;

            //向左
            case 3:
                x1 = top->next->data.abscissa - 1;
                y1 = top->next->data.ordinate;
                break;
            default:
                break;
            }

            if (maze[x1][y1] == 0)
            {
                find = 1;
            }
        }

        //找到下一个节点
        if (find == 1)
        {
            top->next->data.direction = d1;
            data.abscissa = x1;
            data.ordinate = y1;
            data.direction = -1;

            //走过的节点置1不可通行
            Push(top, data);
            maze[x1][y1] = 1;
        }
        else
        {
            //该节点可通行
            maze[top->next->data.abscissa][top->next->data.ordinate] = 0;
            Pop(top);
        }
    }
}

int main()
{
    clock_t start, finish;
    start = clock();
    Run();
    finish = clock();
    printf("运行用时：%f 秒！\n", (double)(finish - start) / CLOCKS_PER_SEC);
}
```

