#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>

int grammer[100][100],grammer_size[100];
int sentence[100];
int pos,N,M,length;

bool solve(int rightbound)
{
    int i,j;
    int s_pos;
    s_pos = pos;
    for(i=0;i<N;i++){
        pos = s_pos;
        for(j=0;pos<=rightbound&&grammer[i][j]!=-1;j++){
            if(grammer[i][j]==0){
                if(!solve(rightbound-(grammer_size[i]-(j+1)))){
                    break;
                }
            }
            else if(sentence[pos]!=grammer[i][j]){
                break;
            }
            else{
                pos++;
            }
        }
        if(grammer[i][j]==-1&&pos==rightbound+1){
            return true;
        }
    }
    return false;
}

int main(void)
{
    int i;
    scanf("%d%d",&N,&M);

    for(i=0;i<N;i++){
        int x=0 , temp;
        while(scanf("%d",&temp)&&temp!=-1){
            grammer[i][x++]=temp;
        }
        if(grammer[i][0]==0&&x==1){
            N--;
            i--;
            continue;
        }
        grammer[i][x] = -1;
        grammer_size[i] = x;
    }
    for(i=0;i<M;i++){
        int x=0 , temp;
        while(scanf("%d",&temp)&&temp!=-1){
            sentence[x++] = temp;
        }
        sentence[x] = -1;
        length = x;
        pos = 0;
        if(solve(length-1)){
            printf("True\n");
        }
        else{
            printf("False\n");
        }
    }
    return 0;
}
