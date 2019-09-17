#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(void)
{
	int n[200005]={0},m[100000]={0},nn,mm,e,tmp;
	scanf("%d%d",&nn,&mm);
	tmp=mm;
	while(tmp--)
	{
		scanf("%d",&e);
		m[tmp]=e;
		n[e]=1;
	}	
	for(int i=0;i<mm;i++)
	{
		if(n[m[i]]==1)
		{
			printf("%d\n",m[i]);
			n[m[i]]=-1;
		}
	}
	for(int i=1;i<=nn;i++)
	{
		if(n[i]==0)
		{
			printf("%d\n",i);
		}
	}
	return 0;
}
