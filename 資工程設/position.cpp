#include<stdio.h>
#include<stdlib.h>
#include<string.h>
char str[1000001];
int main(void)
{
	char ch='A';
	int letter;
	scanf("%s",str);
	letter=strlen(str);
	while(ch<='z')
	{
		int found=0;
		for(int i=0;i<letter;i++)
		{
			if(str[i]==ch)
			{
				if(!found)
				{
					printf("%c: %d",ch,i);
					found=1;
				}
				else
				{
					printf(",%d",i);
				}
			}
		
		}
		if(found)
		{
			printf("\n");
		}
		if(ch=='Z')
		{
			ch='a';
		}
		else{
			ch++;
		}
	}
	return 0;
}
