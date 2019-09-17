#include<stdio.h>
#include<ctype.h>

double prefix(void){
	char c;
	double op1, op2;
	double ans;
	while(isspace( c = getchar() )) continue;
	
	if(c=='+'){
		printf("( ");
		op1=prefix();
		printf(" + ");
		op2=prefix();
		printf(" )");
		ans=op1+op2;
	}
	
	if(c=='-'){
		printf("( ");
		op1=prefix();
		printf(" - ");
		op2=prefix();
		printf(" )");
		ans=op1-op2;
	}
	
	if(c=='*'){
		printf("( ");
		op1=prefix();
		printf(" * ");
		op2=prefix();
		printf(" )");
		ans=op1*op2;
	}
	
	if(c=='/'){
		printf("( ");
		op1=prefix();
		printf(" / ");
		op2=prefix();
		printf(" )");
		ans=op1/op2;
	}
	
	else if(isdigit(c)){
		ungetc(c, stdin);
		scanf("%lf", &ans);
		printf("%.0f", ans);
	}
	
	return ans;
} 

int main(void){
	int n, ans1;
	double ans2;
	scanf("%d", &n);
	while(n--){
		ans2=prefix();
		ans1=ans2;
		if(ans2>ans1){
			printf(" = %.1f", ans2);
		}
		else if(ans2==ans1){
			printf(" = %.0f", ans2);
		}
		
	}
	return 0;
}
