#include <stdio.h>
typedef struct list
{
    int data;
    struct list *next;
} LIST;
void main()
{
    int num = 1;
    int *p = &num;
    printf("%p", p);
    *(++p) = 9;
    printf("\n");
    // printf("asfgh");
    printf("%p", p);
}