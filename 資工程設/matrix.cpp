#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(void)
{
	int a[10000][10000],b[10000][10000],c[10000][10000]={0},n,m,p;
	
	for(int i=0;i<=50;i++)
	{
		scanf("%d%d%d",&n,&m,&p);
		for(int j=0;j<n;j++)
		{
			for(int k=0;k<m;k++)
			scanf("%d",&a[j][k]);
		}
		for(int j=0;j<n;j++)
		{
			for(int k=0;k<m;k++)
			scanf("%d",&b[j][k]);
		}
		for(int j=0;j<n;j++)
		{
			for(int k=0;k<p;k++)
			{
				for(int l=0;l<m;l++)
				{
					c[j][k]+=a[j][l]*b[l][j];
				}
			}
		}
		for(int j=0;j<n;j++)
		    for(int k=0;k<p;k++)
		    printf("%d ",c[j][k]);
		    printf("\n");
	}
	return 0; 
	
	
}
