#include<stdio.h>
#include<stdlib.h>

int count(int x)
{
	int num;
	if(x==1)
	{
		num=1;
	}
	else if(x==2)
	{
		num=2;
	}
	else
	{
		num=count(x-1)+count(x-2);
	}
	return num;
}
int main(void)
{
	int n;
	scanf("%d",&n);
	for(int i=0;i<n;i++)
	{
		int x,m;
		scanf("%d",&x);
		m=count(x);
		printf("%d\n",m);	
	}	
	return 0;
} 

