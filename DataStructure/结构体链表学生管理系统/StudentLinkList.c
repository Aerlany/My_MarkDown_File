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
    printf("������ѧ�ţ�");
    scanf("%s", &number);
    printf("������������");
    scanf("%s", &name);
    printf("�����������");
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
        printf("\n��ǰѧ���б�Ϊ��\n");
    }
    else
    {
        while (1)
        {
            printf("ѧ�ţ�%s\t������%s\t�ɼ�:%d\n", student->number, student->name, student->score);
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
    printf("\n���������λ��:");
    scanf("%d", &position);
    int length = getLength(head);
    if (position > length)
    {
        printf("\n������0~%d֮���λ��", length);
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
    printf("\n������Ҫ����ѧ����ѧ��:");
    scanf("%s", &number);
    STU *student = head->next;
    while (student)
    {
        if (strcmp(student->number, number) == 0)
        {
            printf("\n�ҵ�ѧ����Ϣ���£�\n");
            printf("ѧ�ţ�%s\t������%s\t�ɼ�:%d\n", student->number, student->name, student->score);
            return;
        }
        student = student->next;
    }
    printf("δ�ҵ���ѧ����");
}
void deleteStudent(STU *head)
{
    STU *student = head->next;
    STU *p = head;
    char number[10];
    printf("������Ҫɾ����ѧ����ѧ��:");
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
    printf("\n��ɾ��!");
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
    printf("��ӭ����ѧ������ϵͳ��\n");
    printf("�����Ӧ���ֻس���ѡ����Ӧ�Ĺ��ܣ�\n");
    printf("1=>��ʾ����ѧ����Ϣ\t\t2=>����ѧ����Ϣ\n");
    printf("3=>�ڱ�ͷ����һ��ѧ��\t\t4=>�ڱ�β����һ��ѧ��\n");
    printf("5=>ѡ��λ�ò���ѧ��\t\t6=>ͳ��ѧ������\n");
    printf("7=>ɾ��һ��ѧ��\t\t\t8=>�˳�");
    printf("\n===================================================\n");
    printf("������Ҫ���еĲ��������ֱ��:");
    int option;
    scanf("%d", &option);
    if (option > 8 || option < 1)
    {
        printf("\n++================++\n||��������,�����ԣ�||\n++================++\n");
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
        printf("��ǰѧ������Ϊ%d", getLength(head));
    }
    else if (option == 7)
    {
        deleteStudent(head);
    }
    else if (option == 8)
    {
        freeAll(head);
        printf("\n�����˳�ѧ������ϵͳ��\n");
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