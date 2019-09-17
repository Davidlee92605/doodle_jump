#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(void)
{
	long long int a[200][200],b[200][200],c[200][200]={0},n,m,p;
	
	for(int i=0;i<=50;i++)
	{
		for(int j=0;j<200;j++)
		{
			for(int k=0;k<200;k++)
			{
				c[j][k]=0;
			}
		}
		if(scanf("%lld%lld%lld",&n,&m,&p)!=EOF)
		{
			for(int j=0;j<n;j++)
		{
			for(int k=0;k<m;k++)
			scanf("%lld",&a[j][k]);
		}
		for(int j=0;j<m;j++)
		{
			for(int k=0;k<p;k++)
			scanf("%lld",&b[j][k]);
		}
		for(int j=0;j<n;j++)
		{
			for(int k=0;k<p;k++)
			{
				for(int l=0;l<m;l++)
				{
					c[j][k]+=a[j][l]*b[l][k];
				}
			}
		}
		for(int j=0;j<n;j++)
		{
			for(int k=0;k<p-1;k++){
			printf("%lld ",c[j][k]);
			}
		    printf("%lld",c[j][p-1]);
		    printf("\n");
		}
		printf("\n");
		}
		else{
			break;
		}


	}
	return 0; 
	
	
}
