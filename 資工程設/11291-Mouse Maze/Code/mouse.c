#include <stdio.h>
#include <stdlib.h>
#define SIZE 500

void visit(char(*maze)[SIZE], int, int, int, int, int);
int Result;

int main() {
    int R, C, i, j, N;
    char maze[SIZE][SIZE];
    int start_x, start_y;
    int temp = 0;

    scanf("%d", &N);

    while(--N>=0) {
        Result = 250000;

        scanf("%d %d", &R, &C);

        for(i=0; i<R; i++)
            for(j=0; j<C; j++) {
                scanf(" %c", &maze[i][j]);
                if(maze[i][j]=='S') {
                    start_x = i;
                    start_y = j;
                }
            }

        visit(maze, start_x, start_y, R, C, 0);

        if(Result!=250000)
            printf("%d\n", Result);
        else
            printf("-1\n");
    }

    return 0;
}

void visit(char(*maze)[SIZE], int x, int y, int R, int C, int step) {
    //if(maze[x][y]=='F'){
    //    if(step<Result)
    //        Result = step;
    //    return;
    //}
    if(step==Result) return;
    else if(maze[x][y]=='F'){
        Result = step; //found a shorter path
        return;
    }

    maze[x][y] = '#';
    if(x+1<R&&maze[x+1][y]!='#') {
        visit(maze, x+1, y, R, C, step+1);
    }
    if(y+1<C&&maze[x][y+1]!='#') {
        visit(maze, x, y+1, R, C, step+1);
    }
    if(x-1>=0&&maze[x-1][y]!='#') {
        visit(maze, x-1, y, R, C, step+1);
    }
    if(y-1>=0&&maze[x][y-1]!='#') {
        visit(maze, x, y-1, R, C, step+1);
    }
    maze[x][y] = '$';
    return ;
}
