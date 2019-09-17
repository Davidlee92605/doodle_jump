#include<stdio.h>
#include<stdlib.h>
#define size 10
int solution[size],num[size];

void showresult(int n)
{
    int i;
	printf("(%d", solution[0]);
	for (i=1; i<n ;i++)printf(",%d", solution[i]);
	printf(")\n");
}
void change(int total ,int current ,int n)
{
    int i;
    if(current==n)
    {
        if(total==0){
            showresult(n);
        }
    }
    else
    {
        for(i=0;i<=total/num[current];i++)
        {
            solution[current]=i;
            change(total-i*num[current],current+1,n);
        }
    }
}
int main(void)
{
    int n,i=0,total;
    scanf("%d",&n);
    for(i=0;i<n;i++)
    {
        scanf("%d",&num[i]);
    }
    scanf("%d",&total);
    change(total,0,n);
}
