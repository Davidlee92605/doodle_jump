#include<stdio.h>
#include<stdlib.h>
void malloc_array(int **array,int num)
{
    *array=(int *)malloc(sizeof(int)*num);
    return;
}
int** malloc_ptr(int num)
{
    int **ptr;
    ptr=(int **)malloc(sizeof(int *)*num);
    return ptr;
}
void point_to(int **ptr,int *array,int num)
{
    int i;
    for(i=0;i<num;i++)
    {
        *(ptr+i)=&array[i*(i+1)/2];
    }
    return;
}
int main(void)
{
    int *array, **ptr,n,offset,i,j;
    scanf("%d %d",&n,&offset);
    malloc_array(&array,n*(n+1)/2);
    ptr=malloc_ptr(n);
    for( i=0;i<n*(n+1)/2;i++)
    {
        array[i]=i;
    }
    point_to(ptr,array,n);
    for(i=0;i<n;i++)
    {
        printf("%d",*(ptr[i]+offset));
    }
    return 0;
}
