#include<stdio.h>

void in(int);

void out(int n){
	if(n<1) return;
	out(n-2);
	printf("Move ring %d out\n",n );
	in(n-2);
	out(n-1);
    // take off the first n rings

}

void in(int n){
	if(n<1) return;
	in(n-1);
	out(n-2);
	printf("Move ring %d in\n",n);
	in(n-2);
    //put on the first n rings

}

int n;

int main(){

    scanf("%d",&n);

    out(n);

    return 0;

}
