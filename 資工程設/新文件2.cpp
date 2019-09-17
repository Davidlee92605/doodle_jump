#include<stdio.h>
#include<string.h>
#include<stdlib.h>
char str[1000],out[1000]; 

int main(void)
{
	int n;
	scanf("%d",&n);
	for(int i=0;i<n;i++)
	{
		int length,a,b,max=0;
		scanf("%s",&str[1000]);
		length=strlen(str);
		for(int j=0;j<length;j++)
		{
			for(int k=j+1;k<length;k++)
			{
				if(str[j]==str[k])
				{
					int t=0;
					a=j;
					b=k;
					for(int w=0;w<=((b-a)/2);w++)
					{
						if(str[a+w]==str[b-w])
						{
							t++;
						}
					}
					if(t==((b-a)/2+1)&&t>max)
					{
						max=t;
						for(int p=0;p<b-a+1;p++)
						{
							out[p]=str[a+p];
						}
					}
					
				}
			}
		}
		for(int e=0;e<=(max-1)*2;e++)
		{
			printf("%s",out[e]);
		}
	}
}
