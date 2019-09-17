#include <stdio.h>
#include <string.h>

int main()
{
    char input[1000];
    int start,end,j;
    int max=0,a = 0,b=0;
    int i,num;
    scanf("%d",&num);
    for(i=0;i<num;i++){
    scanf("%s",input);
    for(start = 0; start < strlen(input); start++){
        for(end = start; end < strlen(input); end++){
            for(j=0;j<end;j++){
                if(input[start+j]!=input[end-j])
                    break;
                if(j==end-1-start){
                    if(end - start + 1> max){
                        max = end-start+1;
                        a = start;
                        b = max;
                    }
                    
                }
            }
        }
    }
    if(max<2)
        printf("%c\n",input[0]);
    else{
        for (int i=a; i<b+a; i++)
            printf("%c",input[i]);
        printf("\n");
    }
    max = 0;
    }
    return 0;
}
