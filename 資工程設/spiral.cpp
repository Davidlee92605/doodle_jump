#include<stdio.h>
#include<stdlib.h>
#include<string.h>
char map[5000][5000];
int main(void)
{

	int num;
	scanf("%d",&num);
	for(int i=0;i<num;i++)
	{
		int dir[4][2]={{0,1},{1,0},{0,-1},{-1,0}};
		int r=0;
		int c=-1;
		int index=0;
		int p,ne;
		int j=0;
		scanf("%d",&ne);	
		for(int i=0;i<ne;i++)
		{
			for(int w=0;w<ne;w++)
			map[i][w]=0;
		}
	
		p=ne;
		while(ne>0)
		{
			for(j=0;j<ne;j++)
			{
				r=r+dir[index][0];
				c=c+dir[index][1];
				map[r][c]='#';
			}
			index=(index+1)%4;
			ne--;
		}
		for(int k=0;k<p;k++)
		{
			for(int w=0;w<p;w++)
			{printf("%c",map[k][w]);
			}
			printf("\n");	
		}
	}
	return 0;
}
