#include<stdio.h>
#include<stdlib.h>
int map[30][30]={0};

int main()
{
    int l,i,j=1,m,n,p,total,index=0,row=0,col=-1,np,mp;
    int dir[4][2]={{0,1},{1,0},{0,-1},{-1,0}},num=0;
    scanf("%d%d%d",&m,&n,&p);
    total=m*n;
    np=n;
    mp=m;
    while(total>0)
    {
        if(num==0)
        {
            for(i=0;i<n;i++)
            {
                row=row+dir[index][0];
                col=col+dir[index][1];
                map[row][col]=j;
                j++;
            }
            if(index==0)
            {
                index=1;
            }
            else if(index==2)
            {
                index=3;
            }
            total=total-n;
            //printf("%d\n",total);            n--;
            num=1;
        }
        else if(num==1)
        {
            for(i=1;i<m;i++)
            {
                row=row+dir[index][0];
                col=col+dir[index][1];
                map[row][col]=j;
                j++;
            }
            if(index==1)
            {
                index=2;
            }
            else if(index==3)
            {
                index=0;
            }
            total=total-m+1;
            //printf("%d\n",total);
            m--;
            num=0;
        }
    }
    //printf("%d\n",j);
    for(i=0;i<mp;i++)
    {
        for(l=0;l<np;l++)
        {
            if(map[i][l]==p)
                printf("%d %d\n",i+1,l+1);
        }
    }
}
