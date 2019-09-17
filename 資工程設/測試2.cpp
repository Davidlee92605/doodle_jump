#include<stdio.h>
#include<stdlib.h>
int main(void)
{
	int k,ball[5]={0,1,2,3,4},a[50];
	
	scanf("%d",&k);
	for(int i=0;i<k;i++)
	scanf("%d%d",&a[2*i],&a[2*i+1]);
	
	for(int j=0;j<k;j++)
	{
		int p;
		p=ball[a[2*j]];
		ball[a[2*j]]=ball[a[2*j+1]];
		ball[a[2*j+1]]=p;
	}
	printf("%d %d %d %d %d",ball[0],ball[1],ball[2],ball[3],ball[4]);
}
