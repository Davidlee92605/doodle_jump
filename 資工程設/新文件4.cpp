#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
char a[2001],b[2001],c[4002];
int main(void)
{
	int k;
	scanf("%d",&k);
	for(int i=0;i<k;i++)
	{
		
		int sizea,sizeb;
		scanf("%s%s",a,b);
		sizea=strlen(a);
		sizeb=strlen(b);
		for(int j=0;j<(sizea/2);j++)
		{
			char p;
			p=a[j];
			a[j]=a[sizea-j-1];
			a[sizea-j-1]=p;
		}
		for(int j=0;j<(sizeb/2);j++)
		{
			char p;
			p=b[j];
			b[j]=b[sizeb-j-1];
			b[sizeb-j-1]=p;
		}
        
        

		for(int j=0;j<4002;j++)
		{
			c[j]='0';
			c[j]=c[j]-'0';
		}
		
		for(int j=0;j<sizea;j++)
		{
			for(int m=0;m<sizeb;m++)
			{
			    
				(c[j+m])=(c[j+m])+(a[j]-48)*(b[m]-48);
				(c[j+m+1])=(c[j+m+1])+((c[j+m])/10);
				(c[j+m])=(c[j+m])%10;
			}
		}
		
		for(int j=sizea+sizeb-1;j>=0;j--)
		printf("%d",c[j]);
		printf("\n");
	    
	}
	return 0;
}
