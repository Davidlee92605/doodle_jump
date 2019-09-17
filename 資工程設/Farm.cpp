#include<stdio.h>
#include<stdlib.h>

int space[1001][1001];
int main(void)
{
	int dir[4][2]={{-1,0},{1,0},{0,-1},{0,1}},n,m,time,r=0,c=0,move;
	scanf("%d%d",&n,&m);
	scanf("%d",&time);
	space[0][0]=1;
	int wrong=0;
	for(int i=0;i<time;i++)
	{
		
		scanf("%d",&move);
		if(move==1)
		{
			r=r+dir[0][0];
			if(r>=0)
			{
			    c=c+dir[0][1];
			    space[r][c]++;
			}
			if(r<0)
			{
				r=r-dir[0][0];
				wrong++;
			}

		}
		if(move==2)
		{
			r=r+dir[1][0];
			if(r<n)
			{
				c=c+dir[1][1];
				space[r][c]++;
			}
			if(r>=n)
			{
				r=r-dir[1][0];
				wrong++;
			}
			
		}
		if(move==3)
		{
			c=c+dir[2][1];
			if(c>=0)
			{
				r=r+dir[2][0];
				space[r][c]++;
			}
			if(c<0)
			{
				c=c-dir[2][1];
				wrong++;
			}
			
		}
		if(move==4)
		{
			c=c+dir[3][1];
			if(c<m)
			{
				r=r+dir[3][0];
				space[r][c]++;
			}
			if(c>=m)
			{
				c=c-dir[3][1];
				wrong++;
			}
	
		}
	}
	printf("%d\n",wrong);
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<m;j++)
		{
			printf("%d ",space[i][j]);
		}
		printf("\n");
	}
	return 0;
}
