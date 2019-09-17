#include <stdio.h>
#define size 5


int cup[size];
int solution[size];

void showResult(int n) {
    int i;
	printf("(%d", solution[0]);
	for (i=1; i<n ;i++)printf(",%d", solution[i]);
	printf(")\n");
}

void filling(int space, int current, int n){
	/*if(current < n){
		if(space == 0)showResult(n);
		else if(space > 0){

			solution[current]++;
			filling(space-cup[current], current, n);
			solution[current]--;
			filling(space, current+1, n);

		}
	}*/
	int i;
	if(current==n)
	{
	 	if(space==0)
	 	{
	 		showResult(n);
		}
	}
	else
	{
		for( i=space/cup[current];i>=0;i--)
		{
			solution[current]=i;
			filling( space-i*cup[current], current+1, n);
		}
	}
}

int main(void) {
    int n, i, space;

    scanf("%d", &n);
	for (i=0; i<n ;i++)scanf("%d", &cup[i]);
	scanf("%d", &space);
	filling(space, 0, n);

    return 0;
}
