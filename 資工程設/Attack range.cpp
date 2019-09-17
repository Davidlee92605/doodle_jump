#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(void)
{
	int n,ax0,ax1,ay0,ay1,bx0,bx1,by0,by1;
	scanf("%d",&n);
	for(int i=0;i<n;i++)
	{
		scanf("%d%d%d%d%d%d%d%d",&ax0, &ay0, &ax1, &ay1, &bx0, &by0, &bx1, &by1);
		if((ax0>=bx1)||(bx0>=ax1)||(ay0>=by1)||(by0>=ay1))
		{
			printf("Do you like WHAT YOU SEE,ASS WE CAN\n");
		}
		else
		{
			printf("BOY NEXT DOOR,DEEP DARK FANTASY\n");
		}
	}
	return 0;
}
