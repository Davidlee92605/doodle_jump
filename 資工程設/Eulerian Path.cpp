#include<stdio.h>
#include<stdlib.h>
#include<memory.h>
int v[10001]={0},n,m;

int main(void)
{
	for(int i=0;i<10;i++)
	{
		int odd=0,zero=0;
		if(scanf("%d%d",&n,&m)!=EOF)
		{
			for(int j=0;j<m;j++)
			{
				int a,b;
				scanf("%d%d",&a,&b);
				v[a]++;
				v[b]++;
			}
			for(int j=1;j<=n;j++)
			{
				if(v[j]%2==1)
				{
					odd++;
				}

			}
			printf("%s\n",(odd==0||odd==2)?"Yes":"No");
			memset(v,0,sizeof(v));
		}
		else{
			break;
		}

	}
}
