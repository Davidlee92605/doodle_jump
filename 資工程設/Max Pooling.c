#include<stdio.h>
#include<stdlib.h>
int arr[10][10],out[10][10],n;
int main(void)
{
    int i,j;
    scanf("%d",&n);
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            scanf("%d",&arr[i][j]);
        }
    }
    int a,k,l;
    a=n-3+1;
    for(i=0;i<a;i++)
    {
        for(j=0;j<a;j++)
        {
            int temp;
            temp=arr[i][j];
            for(k=0;k<3;k++)
            {
                for(l=0;l<3;l++)
                {
                    if(temp<arr[i+k][j+l])
                    {
                        temp=arr[i+k][j+l];
                    }
                }
            }
            out[i][j]=temp;
        }
    }
    for(i=0;i<a;i++)
    {
        for(j=0;j<a-1;j++)
        {
            printf("%d ",out[i][j]);
        }
        printf("%d\n",out[i][j]);
    }
}
