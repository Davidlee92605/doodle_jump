
 #include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<math.h>
#include <string.h>
#define size 1000000

char str[size];

int main(void){
	int ans, n,i;
	char* s;
	const char space[2] = " ";

	while(gets(str)!=NULL)
    {
		ans = 0;
		s = strtok(str, space);
		while(s != NULL)
		{
			if(isdigit(*s))
            {
				//n = strlen(s);
				ans+=atoi(s);
			}

			s = strtok(NULL, space);
		}
		printf("%d\n", ans);
	}


	return 0;
}
