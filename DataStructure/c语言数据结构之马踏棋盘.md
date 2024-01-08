# c语言数据结构之马踏棋盘

马踏棋盘游戏
（一）思路：
马随机放在国际象棋的 8×8 棋盘 Board[0~7][0~7]的某个方格中,马按走棋规则进行移动。要求每个方格只进入一次,走遍棋盘上全部 64 个方格。,求出马的行走路线,并按求出的行走路线,将数字 1,2,...,64 依次填入一个 8×8 的方阵,输出之。

（二）步骤分析
1、马踏棋盘问题(骑士周游问题)实际上是图的深度优先搜索(DFS)的应用。
2、解决步骤与思路：
（1）创建棋盘（chessBoard），是一个二维数组，创建栈用于存储访问顺序和用于回朔；
（2）将当前位置设置为已经访问，然后根据当前位置，计算马能走哪些位置，并放入到一个,最多有8个位置，每走一步，就使用top+1；
（3）通过贪心算法进行优化：根据当前这一步的所有的下一步的选择位置，进行非递减排序（例如：1，2，2，2，3，3，4就属于非递减排序）；
（4）遍历栈中存放的所有位置，看看哪个可以走通，如果走通，就继续，走不通，就回溯；
（5）判断马是否完成了任务，使用top和应该走的步数比较，如果没有达到数量，则表示没有完成任务，将整个棋盘置为0。

```c
/**
 * @file 马踏棋盘.c
 * @author IT小阳
 * @brief 
 * @version 0.1
 * @date 2022-06-27
 * 
 * @copyright Copyright (c) 2022
 * 
 * 每次选择位置都是最优解
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define Row 8
#define Col 8
#define maxStep 64

typedef struct
{
    int abscissa;  //横坐标
    int ordinate;  //纵坐标
    int direction; //方向
} SqStack;

//储存路径(并置零)
int ChessBoard[Row + 1][Col + 1] = {}; 

//分别有（1 ~ 8）个方向
int HTry1[8] = {1, -1, -2, 2, 2, 1, -1, -2};
int HTry2[8] = {2, -2, 1, 1, -1, -2, 2, -1};

SqStack PointStack[maxStep];
int top = -1; //栈顶

int num = 0;         //记录结果数

//棋盘打印方法
void printChessBoard()
{
    printf("棋盘路径是:\n");
    for (int i = 1; i <= Row; i++)
    {
        for (int j = 1; j <= Col; j++)
        {
            printf("%5d ", ChessBoard[i][j]);
        }
        printf("\n");
    }
    printf("\n\n");
}

//入栈
void push(int abscissa, int ordinate)
{
    ++top;
    PointStack[top].abscissa = abscissa;
    PointStack[top].ordinate = ordinate;
    PointStack[top].direction = -1; //初始化方向
}

//出栈
void pop()
{
    PointStack[top].abscissa = 0;
    PointStack[top].ordinate = 0;
    PointStack[top].direction = -1; //初始化方向
    --top;
}

//标记棋盘
//棋子的行走路径
void markChessBoard(int abscissa, int ordinate)
{
    ChessBoard[ordinate][abscissa] = top + 1;
}

//初始化
//起点坐标
void InitStartPoint()
{
    int x, y;

    //输入起始坐标点
    printf("请输入起始点（x,y）:");
    scanf("%d,%d", &x, &y);
    while (((x > Col || x <= 0) || (y > Row || y <= 0)))
    {
        if ((x > Col || x <= 0) || (y > Row || y <= 0))
        {
            printf("输入的坐标超出范围，请重新输入（0~8）：");
            scanf("%d,%d", &x, &y);
        }
    }
    //入首栈
    push(x, y);
    //标记路径
    markChessBoard(x, y);
}

//主逻辑
void run()
{
    int xNow, yNow;//记录当前棋子位置

    
    while(1)
    {
        //栈满
        if (top == maxStep - 1)
        {
           break;
        }

        xNow = PointStack[top].abscissa;
        yNow = PointStack[top].ordinate;

        //检查该点可以走的所有节点得出最优解（少的先走）
        int count[8] = {};

        for (int i = 0; i < Row; i++)
        {
            int xNext = xNow, yNext = yNow;
            xNext += HTry1[i];
            yNext += HTry2[i];
            if (xNext > 0 && xNext < Row && yNext > 0 && yNext < Col && ChessBoard[xNext][yNext] == 0)
            {
                for (int j = 0; j < Col; j++)
                {
                    int xNext_Next = xNext, yNext_Next = yNext;
                    xNext_Next += HTry1[j];
                    yNext_Next += HTry2[j];
                    if (xNext_Next > 0 && xNext_Next < Row && yNext_Next > 0 && yNext_Next < Col && ChessBoard[xNext_Next][yNext_Next] == 0)
                    {
                        count[i]++;
                    }                   
                }   
            }         
        }

        //对方向进行排序，实际要走的方向记录在directionNext中
        int directionNext[8] = {};
        int temp = 9;
        int k = 0;
        for (int i = 0; i < 8; i++)
        {
            temp = 9;
            for (int j = 0; j < 8; j++)
            {
                if (count[j] < temp)
                {
                    directionNext[i] = j;
                    temp = count[j];
                    k = j;
                }
            }
            count[k] = 9;
        }

        //走下一步
        int direnow = 0;
        for (direnow = PointStack[top].direction + 1; direnow < 8; direnow++)
        {
            int xRealNext = xNow, yRealNext = yNow;
            xRealNext += HTry1[directionNext[direnow]];
            yRealNext += HTry2[directionNext[direnow]];
            PointStack[top].direction += 1;
            if (xRealNext <= Col && xRealNext > 0 && yRealNext <= Row && yRealNext > 0 && ChessBoard[yRealNext][xRealNext] == 0)
            {
                push(xRealNext, yRealNext);
                markChessBoard(xRealNext, yRealNext);
                break;
            }
        }

        //判断无路可走出栈
        if (PointStack[top].direction >= 7)
        {
            int x, y;
            x = PointStack[top].abscissa;
            y = PointStack[top].ordinate;
            ChessBoard[y][x] = 0; //棋盘标记取消
            pop();
        }
    }
}

int main()
{
    InitStartPoint();
    clock_t start, finish;
    start = clock();
    
    //主逻辑
    run();

    finish = clock();
    printChessBoard();
    printf("运行用时：%f 秒！\n", (double)(finish - start) / CLOCKS_PER_SEC);
}
```

