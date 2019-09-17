#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

int main(void)
{
	unsigned long long x;
	char str[65];
	int i=0;
	
	scanf("%llu",&x);
	//printf("%c",x);
	while(x!=1)
	{
		str[i]=x%2+'0';
		x=x/2;
		//printf("%c",str[i]);
		i++;
	
	}
	
	str[i]='1';
	for(int k=0;k<(i+1)/2;k++)
	{
		char p;
		p=str[k];
		str[k]=str[i-k];
		str[i-k]=p;
	}
	for(int k=0;k<=i;k++)
	    printf("%c",str[k]);
	printf("\n");
	    return 0;
}
