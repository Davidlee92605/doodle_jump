#include <stdio.h>
#include <string.h>
const char table[26][5] = {
    "*-", //A
    "-***", //B
    "-*-*", //C
    "-**", //D
    "*", //E
    "**-*", //F
    "--*", //G
    "****", //H
    "**", //I
    "*---", //J
    "-*-", //K
    "*-**", //L
    "--", //M
    "-*", //N
    "---", //O
    "*--*", //P
    "--*-", //Q
    "*-*", //R
    "***", //S
    "-", //T
    "**-", //U
    "***-", //V
    "*--", //W
    "-**-", //X
    "-*--", //Y
    "--**" //Z
};

char tmp[400][60];
int main(void) {

    char map[27][30]={'\0'};

    for(int i = 0 ; i < 26 ; i++){
        int len = (int)strlen(table[i]);
        for( int j = 0; j < len ; j++){
            char c = table[i][j];

            if(c == '*'){
                strcat(map[i], "=.");
            }
            else{
                strcat(map[i], "===.");
            }
        }
        map[i][ (int)strlen(map[i])-1 ] = '\0';

    }
    strcpy(map[26], " ");


    int n;
    char input[1005];

    scanf("%d", &n);
    scanf("%s", input);
    int last = 0;
    int dot = 0;

    for(int i=0; input[i]; i++ ) {
        char c = input[i];
        if(c == '.')
            dot += 1;
        else
            dot = 0;


        tmp[last][ (int)strlen(tmp[last]) ] = c;

        if( dot == 3 ) {
            tmp[last][ (int) strlen(tmp[last])-3 ] = '\0';
            last++;
        }

        if( dot == 7 ) {
            strcpy(tmp[last], " ");
            last++;
        }
    }

    for(int i = 0 ; i <= last; i++) {
        for(int j = 0; j < 27 ; j++) {
            if( strcmp( tmp[i], map[j] ) == 0 ) {
                if(j == 26)
                    printf(" ");
                else
                    printf("%c",'A'+j);
            }
        }
    }
    printf("\n");

    return 0;
}
