#include <stdio.h>

void out(int);
void in(int);

int main()
{
    int n;

    scanf("%d",&n);
    out(n);

    return 0;
}

void out(int n)
{
    if(n < 1) return;

    out(n-2);

    printf("Move ring %d out\n", n);

    in(n-2);

    out(n-1);
}

void in (int n)
{
    if(n < 1) return;

    in(n-1);

    out(n-2);

    printf("Move ring %d in\n",n);

    in(n-2);
}
