#include<stdio.h>
int t;
char s[6][6];
void flip(int x,int y){
	s[x][y]^=1;
	s[x+1][y]^=1;
	s[x-1][y]^=1;
	s[x][y+1]^=1;
	s[x][y-1]^=1;
}
int check(){
	int i,j,add=0;
	for(i=1;i<=4;++i)
		for(j=1;j<=4;++j)
			add+=s[i][j];
	return add==0||add==16;
}
int MIN, cnt; //cnt: # of flips
void dfs(int id){
    if(cnt>=MIN) return;
    else
    {
        if(check())
        {
            MIN = cnt;
            return;
        }
        if(id==16) return;
    }

    //第id個格子=0
    dfs(id+1);
    //第id個格子=1
    flip(id/4+1, id%4+1);
    ++cnt, dfs(id+1), --cnt;
    flip(id/4+1, id%4+1); //記得要把它恢復成原來的樣子
}
void solve(){
    MIN=7122, cnt=0;
    dfs(0);
    if(MIN==7122) puts("Impossible");
    else printf("%d\n",MIN);
}
int main(){
	char _t[10];
	scanf("%s",_t);
	sscanf(_t,"%d",&t);
	while(t--){
		int i,j;
		for(i=1;i<=4;++i){
			scanf("%s",&s[i][1]);
			for(j=1;j<=4;++j) s[i][j]= s[i][j]=='w';
		}
		solve();
	}
	return 0;
}

