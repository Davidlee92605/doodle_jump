#include <stdio.h>

int main(void)
{
   unsigned long long x;
   int str[65];
   int i=0;
   char w[5]={'2','4','5'} ;
   /*scanf("%llu",&x);
    while(x!=1)
    {
    	str[i]=x%2;
    	x=x/2;
    	i++;
	}
	str[i]=x;
	while(i!=-1)
	{
		printf("%d",str[i]);
		i--;
	}
    printf("\n");*/
    w[3]=(w[0]-'0')+(w[1]-'0');
    w[3]=w[3]+'0';
    printf("%d",w[3]);
}



