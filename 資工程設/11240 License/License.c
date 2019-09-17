/*http://acm.cs.nthu.edu.tw/problem/10850/*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void sort(char *);

int main() {
    char str[5];
    int HIT[10000] = {0};
    int N, i;

    scanf("%d", &N);

    while(N-->0) {
        scanf("%s", str);
        sort(str);
        HIT[atoi(str)]++;
    }

    for(i=0; i<10000; i++)
        if(HIT[i]>=2)
                printf("%d\n", i);

    return 0;
}

void sort(char *str) {
    int i, j;
    char temp;

    for(i=0; i<3; i++)
        for(j=0; j<3-i; j++)
            if(str[j]>str[j+1]) {
                temp = str[j];
                str[j] = str[j+1];
                str[j+1] = temp;
            }
}
