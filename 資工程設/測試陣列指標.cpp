#include<stdlib.h>
#include<stdio.h>

int main(void)
{
    /*int (*ptr)[10];
    int a[10]={99,1,2,3,4,5,6,7,8,9};
    ptr=&a;
    printf("%d",(*ptr)[1]);*/ 
    
    int *ptr[10];
int a[10]={0,8,2,3,4,5,6,7,8,9};
ptr[0]=&a[0];
printf("%d%d",*ptr[0],*(ptr[0]+1));
}
