#include<stdio.h>
#include<stdlib.h>
int time=0;
void hanoi(char a ,char b ,char c,int n)
{
	if(n==1)
	{
		printf("%d: %d from %c to %c\n",++time,n,a,c);
	}
	else
	{
		hanoi(a,c,b,n-1);
		printf("%d: %d from %c to %c\n",++time,n,a,c);
		hanoi(b,a,c,n-1);
	}

}

int main(void)
{
	int n;
	scanf("%d",&n);
	hanoi('a','b','c',n);
	printf("%d",time);
	return 0;
}
