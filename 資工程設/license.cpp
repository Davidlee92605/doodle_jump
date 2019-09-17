#include <stdio.h>
#include <stdlib.h>
char str[5];
int hit[10000];

void sort(char str[])
{
	int i,j;
	char temp;
	for(i=0;i<3;i++)
	{
		for(j=0;j<3-i;j++)
		{
			if(str[j]>str[j+1])
			{
				temp=str[j];
				str[j]=str[j+1];
				str[j+1]=temp;
			}
		}
	}
	
}
int main(void)
{
	int n;
	scanf("%d",&n);
	for(int i=0;i<n;i++)
	{
		scanf("%s",str);
		sort(str);
		hit[atoi(str)]++;
	}
	for(int j=0;j<10000;j++)
	{
		if(hit[j]>1)
		{
			printf("%d\n",j);
		}
	}
	return 0;
}
