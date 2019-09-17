#include<stdio.h>
#include<stdlib.h>

int ans, n, q[11];

void queen(int row){
	
	int i;
	if(row == n)ans++;
	else if(row < n){
		for( i = 0; i < n; i++){
			
			if(valid(row, i)){
				q[row] = i;
				queen(row+1);	
			}
			
		}
	}
	
}

int valid(int row, int col){	
    int i;
	for ( i=0; i < row; i++){
        if (q[i] == col || q[i] == col-row+i || q[i] == col+row-i)
            return 0;
    }
    return 1;
    
}

int main(void){
	
	scanf("%d", &n);
	queen(0);
	printf("%d", ans);
	return 0;
	
} 
