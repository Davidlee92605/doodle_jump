#include<stdio.h>
#include<stdlib.h>
#include<string.h> 
int main(void)
{
	char str[1000];
	int letters;
	
	scanf("%s",str);
	letters=strlen(str);
	
	for(int i=0;i<letters;i++)
	{
		char p;
		p=str[0];
		for(int j=0;j<(letters-1);j++)
		{
		   str[j]=str[j+1];
		}
		str[letters-1]=p;
        printf("%s\n",str);
	}
}
