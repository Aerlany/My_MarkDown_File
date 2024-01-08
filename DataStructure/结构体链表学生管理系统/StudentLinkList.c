#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct student
{
    char number[10];
    char name[20];
    int score;
    struct student *next;
    // int length;
    // struct student *end;
} STU;
STU *createHead()
{
    STU *head = (STU *)malloc(sizeof(STU));
    head->next = NULL;
    return head;
}
STU *createStudent()
{
    char number[10];
    char name[20];
    int score;
    printf("请输入学号：");
    scanf("%s", &number);
    printf("请输入姓名：");
    scanf("%s", &name);
    printf("请输入分数：");
    scanf("%d", &score);
    STU *student = (STU *)malloc(sizeof(STU));
    strcpy(student->number, number);
    strcpy(student->name, name);
    student->score = score;
    student->next = NULL;
    return student;
}
void showStudents(STU *head)
{
    STU *student = head->next;
    if (student == NULL)
    {
        printf("\n当前学生列表为空\n");
    }
    else
    {
        while (1)
        {
            printf("学号：%s\t姓名：%s\t成绩:%d\n", student->number, student->name, student->score);
            if (student->next == NULL)
            {
                break;
            }
            student = student->next;
        }
    }
}
void addStudentAfterHead(STU *head)
{
    STU *student = createStudent();
    student->next = head->next;
    head->next = student;
    // head->length++;
}
void addStudentInTheEnd(STU *head)
{
    STU *p = head;
    STU *student = createStudent();
    while (p->next != NULL)
    {
        p = p->next;
    }
    p->next = student;
    // head->length++;
}

int getLength(STU *head)
{
    STU *p = head;
    int count = 0;
    while (p->next != NULL)
    {
        count++;
        p = p->next;
    }
    return count;
}

void insertStudentAtPosition(STU *head)
{
    int position;
    printf("\n请输入插入位置:");
    scanf("%d", &position);
    int length = getLength(head);
    if (position > length)
    {
        printf("\n请输入0~%d之间的位置", length);
    }
    else
    {
        STU *p = head;
        int count = 0;
        while (count < position)
        {
            p = p->next;
            count++;
        }
        STU *student = createStudent();
        student->next = p->next;
        p->next = student;
    }
}
void findStudentByNumber(STU *head)
{
    char number[10];
    printf("\n请输入要查找学生的学号:");
    scanf("%s", &number);
    STU *student = head->next;
    while (student)
    {
        if (strcmp(student->number, number) == 0)
        {
            printf("\n找到学生信息如下：\n");
            printf("学号：%s\t姓名：%s\t成绩:%d\n", student->number, student->name, student->score);
            return;
        }
        student = student->next;
    }
    printf("未找到该学生！");
}
void deleteStudent(STU *head)
{
    STU *student = head->next;
    STU *p = head;
    char number[10];
    printf("请输入要删除的学生的学号:");
    scanf("%s", number);
    while (student)
    {
        if (strcmp(student->number, number) == 0)
        {
            p->next = student->next;
            free(student);
            return;
        }
        p = student;
        student = student->next;
    }
    printf("\n已删除!");
}
void freeAll(STU *head)
{

    STU *student = head->next;
    while (head->next != NULL)
    {
        // p=student->next;
        head = student->next;
        free(student);
    }
    free(head);
}
void menu(STU *head)
{
    printf("\n===================================================\n");
    printf("欢迎来到学生管理系统！\n");
    printf("输入对应数字回车后选择相应的功能！\n");
    printf("1=>显示所有学生信息\t\t2=>查找学生信息\n");
    printf("3=>在表头插入一个学生\t\t4=>在表尾插入一个学生\n");
    printf("5=>选择位置插入学生\t\t6=>统计学生人数\n");
    printf("7=>删除一个学生\t\t\t8=>退出");
    printf("\n===================================================\n");
    printf("情输入要进行的操作的数字编号:");
    int option;
    scanf("%d", &option);
    if (option > 8 || option < 1)
    {
        printf("\n++================++\n||输入有误,请重试！||\n++================++\n");
    }
    else if (option == 1)
    {
        showStudents(head);
    }
    else if (option == 2)
    {
        findStudentByNumber(head);
    }
    else if (option == 3)
    {
        addStudentAfterHead(head);
    }
    else if (option == 4)
    {
        addStudentInTheEnd(head);
    }
    else if (option == 5)
    {
        insertStudentAtPosition(head);
    }
    else if (option == 6)
    {
        printf("当前学生总数为%d", getLength(head));
    }
    else if (option == 7)
    {
        deleteStudent(head);
    }
    else if (option == 8)
    {
        freeAll(head);
        printf("\n你已退出学生管理系统！\n");
        exit(1);
    }
}

int main(int argc, char **argv)
{
    STU *head = createHead();
    while (1)
    {
        menu(head);
    }
    // freeAll(head);
    return 0;
}