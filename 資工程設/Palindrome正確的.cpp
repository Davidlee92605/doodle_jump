#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(void)
{
	char input[100001];
	
	for(int i=0;i<1000;i++)
	{
		int letter,p=0;
		scanf("%s",input);
		letter=strlen(input);
		for(int m=0;m<(letter/2);m++)
		{
			if(input[m]!=input[letter-1-m])
			{
				printf("No\n");
				p++;
				break;
			}
			
		}
		if(p==0)
		{
			printf("Yes\n");
		}
		else{printf("No\n");
		}
	}
} 
