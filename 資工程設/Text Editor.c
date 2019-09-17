#include <stdio.h>

#define MAX_SIZE 503

char content[MAX_SIZE];
char input[MAX_SIZE];

int main()
{
    int i=0,k=0,position=0,note[500],letter;
    fgets(input, MAX_SIZE, stdin);
    letter=strlen(input)-1;
    //printf("check input len : %d\n",letter);

    while(input[i]!=NULL)
    {
        if(input[i]=='/')
        {
            if(input[i+1]=='b')
            {
                if(position!=0)
                {
                    content[position-1]='\0';
                    position--;

                    for(k=position;k<500;k++)
                    {
                        content[k]=content[k+1];
                    }
                    content[500]='\0';
                }
                i+=10;
            }
            else if(input[i+1]=='l')
            {
                if(position!=0)
                {
                    position--;
                }
                i+=5;
            }
            else if(input[i+1]=='r')
            {
                if(position!=0&&position!=500&&content[position]!='\0')
                {
                    position++;
                }
                i+=6;
            }
            else if(input[i+1]=='n')
            {
                for(k=500;k>position;k--)
                {
                    content[k]=content[k-1];
                }
                content[position]='\n';
                position++;
                i+=8;
            }
        }
        else
        {
            for(k=500;k>position;k--)
            {
                content[k]=content[k-1];
            }
            content[position]=input[i];
            position++;
            i++;
        }
       // printf("%d, %s\n",position,content);
    }
    /* your code here */
    printf("%s", content);

    return 0;
}
