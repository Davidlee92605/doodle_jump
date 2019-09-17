#include<stdio.h>
#include<stdlib.h>
int board[16][16]={0};
int M,N,ans;

void place(int m,int n,int row)
{
    int col;
    if(m==M&&n==N&&row==(M+N))
    {
        ans++;
    }
    else if(m<=M&&n<=N&&row<(M+N))
    {
        for(col=0;col<(M+N);col++)
        {
            int status,ok;
            for(status=1;status<=2;status++)
            {
                if(status==1)
                {
                    ok=1;
                    board[row][col]=1;
                    int i;
                    for(i=0;i<row;i++)
                    {
                        if(board[i][col]!=0||board[i][col-row+i]!=0||board[i][col+row-i]!=0)
                        {
                            ok=0;
                            board[row][col]=0;
                            break;
                        }
                    }
                    if(ok==1)
                    {
                        place(m+1,n,row+1);
                        board[row][col]=0;
                    }
                }
                else if(status==2)
                {
                    ok=1;
                    board[row][col]=2;
                    int i;
                    for(i=0;i<row;i++)
                    {
                        if(board[i][col]!=0||board[i][col-row+i]==1||board[i][col+row-i]==1)
                        {
                            ok=0;
                            board[row][col]=0;
                            break;
                        }
                    }
                    if(ok==1)
                    {
                        place(m,n+1,row+1);
                        board[row][col]=0;
                    }
                }
            }
        }
    }
}

int main()
{
    scanf("%d%d",&M,&N);
    place(0,0,0);
    printf("%d\n",ans);
}
