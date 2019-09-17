#include <stdio.h>
#include <stdlib.h>


typedef struct _Node{
    int number;
    struct _Node* next;
    struct _Node* prev;
}Node;

Node* head;
Node *p, *temp;
int clock = 1;
Node* createList(int n)
{
    int i;
    Node *np, *nq;
    head = (Node*)malloc(sizeof(Node));
    p = head;
    np = head;
    nq = np;
    np->number = 1;
    for(i=2;i<=n;i++)
    {
        np->next = (Node*)malloc(sizeof(Node));
        np = np->next;
        np->number = i;
        np->prev = nq;
        nq = nq->next;
    }
    np->next = head;
    head->prev = np;

    return head;
}
void freeList()
{
    free(p);
}

int solveJosephus(int step)
{
    int i;
    while((p->next!=p)){
        if(clock==1){
            for(i=0;i<step;i++){
                p=p->next;
            }
            temp = p->prev;
            p->prev = temp->prev;
            temp->prev->next = p;
            //printf("%d\n",temp->number);
            free(temp);
            p = p->prev;
            clock = 0;
        }
        else{
            for(i=0;i<step;i++){
                p = p->prev;
            }
            temp = p->next;
            p->next = temp->next;
            temp->next->prev = p;
            //printf("%d\n",temp->number);
            free(temp);
            p = p->next;
            clock = 1;
        }
    }
    clock = 1;
    return p->number;
}
int main(){

    int n, m;

    while(scanf("%d%d", &n, &m)!=EOF){
        head = createList(n);
        printf("%d\n", solveJosephus(m));
        freeList();
    }

    return 0;
}

