#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(void)
{
	char a[5],b[10],num[3];
	int n,lettera,nmax=0;
	
	scanf("%s",a);
	scanf("%d",&n);
	
	lettera=strlen(a);
	for(int i=0;i<n;i++)
	{
		int letterb,nc=0,j;
		
		scanf("%s",b);
		letterb=strlen(b);
		for(int m=0;m<(letterb-lettera+1);m++)
		{
			for( j=0;j<lettera;j++)
			{
				if(b[m+j]!=a[j])
				break;
			}
			if(j==lettera)
			{
				nc++;
			}
		}
		if(nc>nmax)
		nmax=nc;
	}
	printf("%d",nmax);
	return 0;
	
}
