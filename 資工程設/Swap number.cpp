#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
int main(void)
{
     int b[200],a[5]={0,1,2,3,4},k;
     
     scanf("%d",&k);
     for(int i=0;i<k;i++)
     {
     	scanf("%d%d",&b[2*i],&b[2*i+1]);
	 }
	 
	 for(int i=0;i<k;i++)
	 {
	 	int p;
	 	p=a[b[2*i]];
	 	a[b[2*i]]=a[b[2*i+1]];
	 	a[b[2*i+1]]=p;
	 }
	 printf("%d %d %d %d %d",a[0],a[1],a[2],a[3],a[4]);
     return 0;
}
