#include<stdio.h>
#include<stdlib.h>
#define size 510
int result;


void visit(char mou[][size],int x,int y,int r,int c,int step)
{
    if(step==result) return;
    if(mou[x][y]=='F')
    {
        if(step<result)
            result=step;
        return;
    }
    mou[x][y]='#';
    if(x+1<r&&mou[x+1][y]!='#') visit(mou,x+1,y,r,c,step+1);
    if(y+1<c&&mou[x][y+1]!='#') visit(mou,x,y+1,r,c,step+1);
    if(x-1>=0&&mou[x-1][y]!='#') visit(mou,x-1,y,r,c,step+1);
    if(y-1>=0&&mou[x][y-1]!='#') visit(mou,x,y-1,r,c,step+1);
    mou[x][y]='$';
    return;
}
int main(void)
{
    int i,j,n,r,c,x,y;
    char mou[size][size];
    scanf("%d",&n);
    while(n--)
    {
        result=250000;
        scanf("%d%d",&r,&c);
        for(i=0;i<r;i++)
        {
            for(j=0;j<c;j++)
            {
                scanf(" %c",&mou[i][j]);
                if(mou[i][j]=='S')
                {
                    x=i;
                    y=j;
                }
            }
        }
        /*for(i=0; i<r; i++)
            for(j=0; j<c; j++) {
                scanf(" %c", &mou[i][j]);
                if(mou[i][j]=='S') {
                    x = i;
                    y = j; } }*/

        visit(mou,x,y,r,c,0);
        if(result!=250000)
        {
            printf("%d\n",result);
        }
        else
        {
            printf("-1\n");
        }
        result=250000;
    }
    return 0;
}
