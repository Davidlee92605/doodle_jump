#include<stdio.h>
int n,student[22],t[22];

int deliver(int i)
{
	int gift=t[i];
	int num=0;
	if(i==n)
	{
		return 1;
	}
	else
	{
		for(int j=1;j<=n;j++)
		{
			if(student[j]==0)
			{
				if(j<=gift)
				{
					student[j]=1;
					num+=deliver(i+1);
					student[j]=0;
					
				}
				else break;
			}
		}
	}
	return num;
}

void sort(int t[])
{
	int temp;
	for(int i=0;i<n-1;i++)
		for(int j=0;j<n-i-1;j++)
		{
			if(t[j]>t[j+1])
			{
				temp=t[j];
				t[j]=t[j+1];
				t[j+1]=temp;
			}
		}
}

int main(void)
{
	scanf("%d",&n);
	for(int i=0;i<n;i++)
		scanf("%d",&t[i]);
	sort(t);
	printf("%d",deliver(0));
}

