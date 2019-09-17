
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
char str[1000],out[1000]; 

int main(void)
{
	int n;
	scanf("%d",&n);
	for(int i=0;i<n;i++)
	{
		
		int length,a,b,max=0;
		scanf("%s",str);
		length=strlen(str);
		for(int j=0;j<length;j++)
		{
			for(int k=j+1;k<length;k++)
			{
				if(str[j]==str[k])
				{
					int t=0;
					a=j;
					b=k;
					//printf("%d%d",j,k);
					for(int w=0;w<=((b-a)/2);w++)
					{
						if(str[a+w]==str[b-w])
						{
						    t++;
						}
						else 
						{
						    break;
					    }
					}
					if(t==((b-a)/2+1)&&(b-a+1)>max)
					{
					    max=b-a+1;
					    for(int p=0;p<b-a+1;p++)
					    {
						    out[p]=str[a+p];						    
						}
					}
				}	
			}
		}
		
		if(max<2)
		{
			printf("%c\n",str[0]);
		}
		else
		{	
		    int letter;
			letter=strlen(out);
			for(int e=0;e<letter;e++)
			{
				printf("%c",out[e]);
			}
			memset(out,'\0',letter);
			printf("\n");		
		    /*for(int e=0;e<=(max-1)*2;e++)
		    {
			    printf("%c",out[e]);
		    }
		    printf("\n");*/
        }
    }
	
	return 0;
}
