#include<stdio.h>
int t;
char s[6][6];
int bit_cnt(int d){
	int cnt=0;
	for(;d;d>>=1)
		if(d&1) ++cnt;
	return cnt;
}
void flip(int x,int y){
	s[x][y]^=1;
	s[x+1][y]^=1;
	s[x-1][y]^=1;
	s[x][y+1]^=1;
	s[x][y-1]^=1;
}
void flip_all(int ST){
	int i;
	for(i=0;i<16;++i)
		if(ST&(1<<i)) flip(i/4+1,i%4+1);
}
int check(){
	int i,j,add=0;
	for(i=1;i<=4;++i)
		for(j=1;j<=4;++j)
			add+=s[i][j];
	return add==0||add==16;
}
void solve(){
    int ST, MIN=7122;
    for(ST=0;ST<(1<<16);++ST){//枚舉所有可能的ST
        flip_all(ST);
        int b_cnt = bit_cnt(ST);
        if(check()&&MIN>b_cnt) MIN=b_cnt;
        flip_all(ST); //記得要把它恢復成原來的樣子
    }
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

