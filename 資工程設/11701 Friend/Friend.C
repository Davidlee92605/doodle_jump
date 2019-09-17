#include <stdio.h>
#include <stdbool.h>
#define MAXN 2005

bool f[MAXN][MAXN];
int n;
void init(){
	int i=0,j;
	for(;i<n;++i){
		for(j=0;j<n;++j){
			f[i][j]=false;
		}
		f[i][i]=true;
	}
}
bool is_friend(int a,int b){
	//如果f[a][b]=true，就表示他們是朋友
	//你的作業就是要好好維護f陣列
	return f[a][b];
}
int ga[MAXN],gb[MAXN];
int len_ga,len_gb;
void get_ga(int a){
	//ga陣列存是a的所有朋友
	//例如a的朋友有： 1, 4, 5, 10
	//那ga[]={1,4,5,10}, len_ga=4
	//請思考要怎麼從f陣列得到ga
	int idx=0;
	for(int i=0;i<MAXN;i++){
		if(f[a][i]==true){
			ga[idx]=i;
			idx++;
		}
	}
	len_ga=idx;
}
void get_gb(int b){
	//gb陣列存是b的所有朋友
	//和ga類似
	int idx=0;
	for(int i=0;i<MAXN;i++){
		if(f[b][i]==true){
			gb[idx]=i;
			idx++;
		}
	}
	len_gb=idx;
}
void set_friend_ab(){
	//現在ga、gb你都有了
	//因為a和b會成為朋友，你要怎麼利用ga,gb來維護新的f陣列呢？

	for(int i=0;i<len_ga;i++){
		for(int j=0;j<len_gb;j++){
			if(f[ga[i]][gb[j]]==false)
				f[ga[i]][gb[j]]=true;
			if(f[gb[j]][ga[i]]==false)
				f[gb[j]][ga[i]]=true;
		}
	}

}
void merge_friend(int a,int b){
	if(is_friend(a,b)) return;
	get_ga(a);
	get_gb(b);
	set_friend_ab();
}
int main(){
	int t,q;
	scanf("%d",&t);
	while(t--){
		scanf("%d%d",&n,&q);
		init();
		while(q--){
			int op,a,b;
			scanf("%d%d%d",&op,&a,&b);
			if(op==1) puts(is_friend(a,b) ? "they are friends!" : "they are not friends!");
			else merge_friend(a,b);
		}
	}
	return 0;
}
